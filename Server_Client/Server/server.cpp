#include "server.h"
void C_SERVER::init(string strIp,int iPort){
    m_strIp=strIp;
	m_iPort=iPort;
}

void C_SERVER::run(){
	char rbuf[BUFSIZ];
	m_sock.Listen(m_strIp,m_iPort);
	while(1){
		int c_fd=m_sock.Accept();
		read(c_fd,rbuf,sizeof(rbuf));
		write(c_fd,rbuf,sizeof(rbuf));
	}
}

void C_SERVER::stop(){

}