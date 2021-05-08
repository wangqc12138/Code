#include<iostream>
#include"socket.h"
using namespace std;
int main()
{
	Socket ser;
	int fd=ser.Listen("192.168.154.128",8888);
	ser.Accept(fd);
	return 0;
}
