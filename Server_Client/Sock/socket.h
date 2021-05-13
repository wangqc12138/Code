#ifndef SOCKET_H
#define SOCKET_H
#include "common.h"
using namespace std;
class Socket
{
private:
public:
	Socket(){
		m_iFamily=AF_INET;
		m_iHandle=-1;
	}
    int Connet(const string strIp,const int iPort);
    int Listen(const string strIp,const int iPort);
    int Accept();
public:
	int m_iHandle;
	int m_iFamily;
};
int Read(int fd,char* buf,int len);
int Write(int fd,char* buf,int len);	
int Close(int fd);
#endif
