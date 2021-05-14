#include "server.h"
void C_SERVER::init(string strIp,int iPort){
    m_strIp=strIp;
	m_iPort=iPort;
}

void C_SERVER::run(){
	char recv_buf[BUFSIZ],send_buf[BUFSIZ];
	int max_fd,max_i=-1;
	fd_set lisset,allset;
	m_sock.Listen(m_strIp,m_iPort);
	/* int select(int nfds, fd_set *readfds, fd_set *writefds,fd_set *exceptfds, struct timeval *timeout); */
	vector<int> clifd(FD_SETSIZE,-1);
	FD_ZERO(&lisset);
	FD_SET(m_sock.m_iHandle,&allset);
	max_fd=m_sock.m_iHandle;
	while(1){
		lisset=allset;
		bzero(recv_buf,strlen(recv_buf));
		bzero(send_buf,strlen(send_buf));
		/* 
		memset(recv_buf,0,sizeof(recv_buf));
		memset(send_buf,0,sizeof(send_buf));
		 */
		int ret=select(max_fd+1,&lisset,0,0,NULL);
		if(ret<0){
			perror("select fd error!");
			break;
		}
		if(FD_ISSET(m_sock.m_iHandle,&lisset)){
			int c_fd=m_sock.Accept();
			for(int i=0;i<1024;i++){
				if(clifd[i]==-1){
					clifd[i]=c_fd;
					FD_SET(c_fd,&allset);
					max_fd=max(max_fd,c_fd);
					max_i=max(max_i,i);
					break;
				}
				if(i==1023){
					perror("connect client more than 1024!!");
					return;
				}
			}
			if(ret==1){
				continue;
			}
		}
		for(int i=0;i<=max_i;i++){
			if(clifd[i]==-1){
				continue;
			}
			int c_fd=clifd[i];
			if(FD_ISSET(c_fd,&lisset)){
				int n=Read(c_fd,recv_buf,sizeof(recv_buf));
				if(n==0){
					//printf("client close\n");
					Close(c_fd);
					FD_CLR(c_fd,&allset);
					clifd[i]=-1;
				}else{
					if(recv_buf[n-1]=='\n'){
						recv_buf[n-1]=0;
					}
					memcpy(send_buf,recv_buf,strlen(recv_buf));
					cmd(recv_buf,send_buf);
					write(c_fd,send_buf,strlen(send_buf));
				}
				/* for(;;){
					bzero(send_buf,strlen(send_buf));
					memcpy(send_buf,"just test\n",strlen("just test\n"));
					write(c_fd,send_buf,strlen(send_buf));
				} */
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