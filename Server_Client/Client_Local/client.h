#ifndef CLIENT_H
#define CLIENT_H
#include "socket.h"
#include "common.h"
class C_CLIENT{
public:
    void init(string strFilename);
    void run();
    void stop();    
private:
	Socket m_sock;
	string m_strFilename;
};
#endif