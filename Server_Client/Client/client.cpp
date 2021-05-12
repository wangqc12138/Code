#include "client.h"
void C_CLIENT::init(string strIp,int iPort){
    m_strIp=strIp;
	m_iPort=iPort;
}

void C_CLIENT::run(){
	char buf[BUFSIZ];
	m_sock.Connet(m_strIp,m_iPort);
	while (1){
		printf("input some words:\n");
        int n=read(STDIN_FILENO, buf, sizeof(buf));
        if (!strncmp(buf,"quit",4)){
            break;
        }
		write(m_sock.m_iHandle,buf,n);
        n=read(m_sock.m_iHandle,buf,sizeof(buf));
		printf("return data:\n");
        write(STDOUT_FILENO,buf,n);
    }
}

void C_CLIENT::stop(){

}