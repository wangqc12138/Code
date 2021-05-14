#include "server.h"
void C_SERVER::init(string strIp,int iPort){
    m_strIp=strIp;
	m_iPort=iPort;
}

void C_SERVER::run(){
	char recv_buf[BUFSIZ],send_buf[BUFSIZ];
	int max_i=-1;
	fd_set lisset,allset;
	m_sock.Listen(m_strIp,m_iPort);
	struct pollfd pfd_set[MAXSIZE];
	for(int i=0;i<MAXSIZE;i++){
		pfd_set[i].fd=i==0?m_sock.m_iHandle:-1;
		pfd_set[i].events=POLLRDNORM;
	}
	while(1){
		/* int poll(struct pollfd *fds, nfds_t nfds, int timeout);*/
		bzero(recv_buf,strlen(recv_buf));
		bzero(send_buf,strlen(send_buf));
		int ret=poll(pfd_set,MAXSIZE,0);
		if(ret<0){
			perror("server poll error!");
			return;
		}
		if(pfd_set[0].revents&POLLRDNORM){
			int c_fd=m_sock.Accept();
			for(int i=1;i<MAXSIZE;i++){
				if(pfd_set[i].fd==-1){
					pfd_set[i].fd=c_fd;
					max_i=max(max_i,i);
					break;
				}
				if(i==MAXSIZE-1){
					printf("too much client connect!\n");
				}
			}
			if(--ret==0){
				continue;
			}
		}
		for(int i=1;i<=max_i;i++){
			int c_fd=pfd_set[i].fd;
			if(c_fd==-1){
				continue;
			}
			if(pfd_set[i].revents&(POLLRDNORM|POLLERR)){
				int n=Read(c_fd,recv_buf,sizeof(recv_buf));
				if(n==0){
					// printf("client close!\n");
					pfd_set[i].fd=-1;
					Close(c_fd);
				}else{
					if(recv_buf[n-1]=='\n'){
						recv_buf[n-1]=0;
					}
					memcpy(send_buf,recv_buf,strlen(recv_buf));
					cmd(recv_buf,send_buf);
					write(c_fd,send_buf,strlen(send_buf));
				}
				if(--ret==0){
					break;
				}
			}
		}
	}
	
	
}

void C_SERVER::stop(){
	Close(m_sock.m_iHandle);
}