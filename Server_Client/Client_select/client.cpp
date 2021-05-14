#include "client.h"
void C_CLIENT::init(string strIp,int iPort){
    m_strIp=strIp;
	m_iPort=iPort;
}

void C_CLIENT::run(){
	char recv_buf[BUFSIZ],send_buf[BUFSIZ];
	m_sock.Connet(m_strIp,m_iPort);
	int maxfd=m_sock.m_iHandle,n;
	fd_set allset,lisset;
	FD_ZERO(&allset);
	FD_ZERO(&lisset);
	FD_SET(m_sock.m_iHandle,&allset);
	FD_SET(STDIN_FILENO,&allset);
	while (1){
		lisset=allset;
		bzero(recv_buf,strlen(recv_buf));
		bzero(send_buf,strlen(send_buf));
		/* 
		memset(recv_buf,0,sizeof(recv_buf));
		memset(send_buf,0,sizeof(send_buf));
		 */
		int ret=select(maxfd+1,&lisset,0,0,NULL);
		if(ret<0){
			perror("client select error!");
			return;
		}
		if(FD_ISSET(m_sock.m_iHandle,&lisset)){
			n=Read(m_sock.m_iHandle,recv_buf,sizeof(recv_buf));
			if(n==0){
				printf("server %s close\n",m_strIp.c_str());
				return;
			}
			printf("server send data:\n");
        	Write(STDOUT_FILENO,recv_buf,strlen(recv_buf));
			if(ret==1){
				continue;
			}
		}
		if(FD_ISSET(STDIN_FILENO,&lisset)){
			n=Read(STDIN_FILENO, send_buf, sizeof(send_buf));
			if(send_buf[n-1]=='\n'){
				send_buf[n-1]=0;
			}
        	if (!strncmp(send_buf,"quit",strlen(send_buf))){
				
            	break;
        	}
			Write(m_sock.m_iHandle,send_buf,strlen(send_buf));
		}
    }
}

void C_CLIENT::stop(){
	Close(m_sock.m_iHandle);
}