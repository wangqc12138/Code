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
		int n=read(c_fd,buf,sizeof(buf));
		if (!strncmp(buf,"ls",2)){
			n=ls(buf);
		}
		if (!strncmp(buf,"pwd",3)){
			n=pwd(buf);
		}
		if (!strncmp(buf,"cd",2)){
			char target[256];
            bzero(target,sizeof(target));
			memcpy(target,buf+3,strlen(buf)-4);
			cd(target);
		}
		write(STDOUT_FILENO,buf,n);
		write(c_fd,buf,n);
		bzero(buf,sizeof(buf));
	}
}

void C_SERVER::stop(){

}