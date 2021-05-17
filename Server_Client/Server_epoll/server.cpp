#include "server.h"
void C_SERVER::init(string strIp,int iPort){
    m_strIp=strIp;
	m_iPort=iPort;
}

void C_SERVER::run(){
	char recv_buf[BUFSIZ],send_buf[BUFSIZ];
}

void C_SERVER::stop(){
	Close(m_sock.m_iHandle);
}