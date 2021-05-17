#include "server.h"
void C_SERVER::init(string strIp,int iPort){
    m_strIp=strIp;
	m_iPort=iPort;
}

void C_SERVER::run(){
	char buf[BUFSIZ];
	m_sock.Listen(m_strIp,m_iPort);
	int c_fd=m_sock.Accept();
	while(1){
		Read(c_fd,buf,sizeof(buf));
		if (!strncmp(buf,"ls",strlen(buf)-1)){
			ls(buf);
		}
		if (!strncmp(buf,"pwd",strlen(buf)-1)){
			pwd(buf);
		}
		if (!strncmp(buf,"cd ",3)){
			char target[256];
            bzero(target,sizeof(target));
			memcpy(target,buf+3,strlen(buf)-4);
			cd(target);
		}
		write(STDOUT_FILENO,buf,strlen(buf));
		write(c_fd,buf,strlen(buf));
		memset(buf,0,strlen(buf));
	}
}

void C_SERVER::stop(){
	Close(m_sock.m_iHandle);
}