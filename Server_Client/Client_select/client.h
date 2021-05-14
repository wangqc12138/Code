#ifndef CLIENT_H
#define CLIENT_H
#include "socket.h"
#include "common.h"
class C_CLIENT{
public:
    void init(string strIp,int iPort);
    void run();
    void stop();    
private:
	Socket m_sock;
	string m_strIp;
	int m_iPort;
};
#endif