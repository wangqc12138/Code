#include<iostream>
#include "server.h"
using namespace std;
int main()
{
	C_SERVER ser;
	ser.init("192.168.154.128",8888);
	ser.run();
	return 0;
}
