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
        Read(STDIN_FILENO, buf, sizeof(buf));
        if (!strncmp(buf,"quit",strlen(buf))){
            break;
        }
		Write(m_sock.m_iHandle,buf,strlen(buf));
        Read(m_sock.m_iHandle,buf,sizeof(buf));
		printf("return data:\n");
        Write(STDOUT_FILENO,buf,strlen(buf));
		bzero(buf,sizeof(buf));
    }
}

void C_CLIENT::stop(){
	Close(m_sock.m_iHandle);
}