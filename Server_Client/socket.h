#ifndef SOCKET_H
#define SOCKET_H
#include<iostream>
#include<string>
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;
class Socket
{
private:
    int m_iHandle;
public:
    int Connet(const string strIp,const int iPort);
    int Listen(const string strIp,const int iPort);
    int Accept(int iSockfd);
    int Write(const string strMsg);
    int Read(string &strMsg);
};

#endif
