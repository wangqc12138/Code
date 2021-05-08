#ifndef SOCKET_H
#define SOCKET_H
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
using namespace std;
class Socket
{
private:
    int m_iHandle=-1;
    int m_iFamily=AF_INET;
    int Close(int fd);
public:
    int Connet(const string strIp,const int iPort);
    int Listen(const string strIp,const int iPort);
    int Accept(int iSockfd);
    int Write(const string strMsg);
    int Read(string &strMsg);
};

#endif
