#include "server.h"
void C_SERVER::init(string strIp,int iPort){
    m_strIp=strIp;
	m_iPort=iPort;
}

void C_SERVER::run(){
	char buf[BUFSIZ];
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
		int ret=select(max_fd+1,&lisset,0,0,0);
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
				if(Read(c_fd,buf,sizeof(buf))==0){
					Close(c_fd);
					c_fd=-1;
					FD_CLR(c_fd,&allset);
				}else{
					cmd(buf);
				}
				write(c_fd,buf,strlen(buf));
				memset(buf,0,strlen(buf));
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