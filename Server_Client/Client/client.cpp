#include "client.h"
#include <string.h>
void C_CLIENT::init(string strIp,int iPort){
    m_strIp=strIp;
	m_iPort=iPort;
}

void C_CLIENT::run(){
	char scin[BUFSIZ];
	char scout[BUFSIZ];
	m_sock.Connet(m_strIp,m_iPort);
	while (1){
		printf("input some words:\n");
        int n=read(STDIN_FILENO, scin, sizeof(scin));
        if (!strncmp(scin,"quit",4)){
            break;
        }
        m_sock.Write(scin, n);
        m_sock.Read(scout);
        printf("return data is %s\n",scout);
    }
}

void C_CLIENT::stop(){

}