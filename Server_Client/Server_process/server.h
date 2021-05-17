#ifndef SERVER_H
#define SERVER_H
#include "socket.h"
#include "cmd.h"
class C_SERVER{
public:
    void init(string strIp,int iPort);
    void run();
    void stop();    
private:
	int work(int child_fd);
	Socket m_sock;
	string m_strIp;
	int m_iPort;
};
#endif