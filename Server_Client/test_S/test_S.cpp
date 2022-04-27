#include<iostream>
#include "server.h"
//#include "Readcfg.h"
using namespace std;
int main()
{

	C_SERVER ser;
	ser.init("/home/wangqc/socket/11111");
	ser.run();
	ser.stop();
	return 0;
}
