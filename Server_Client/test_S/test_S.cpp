#include<iostream>
#include "server.h"
using namespace std;
int main()
{
	C_SERVER ser;
	ser.init("192.168.239.132",23333);
	ser.run();
	return 0;
}
