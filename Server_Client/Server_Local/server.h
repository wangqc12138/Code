#ifndef SERVER_H
#define SERVER_H
#include "socket.h"
class C_SERVER{
public:
    void init(string strFilename);
    void run();
    void stop();    
private:
	Socket m_sock;
	string m_strFilename;
};
#endif