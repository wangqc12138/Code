#include<iostream>
#include "server.h"
using namespace std;
int main()
{
	C_SERVER ser;
	ser.init("192.168.154.128",23333);
	ser.run();
	ser.stop();
	return 0;
}
