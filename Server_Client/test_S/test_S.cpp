#include<iostream>
#include "server.h"
//#include "Readcfg.h"
using namespace std;
int main()
{

	C_SERVER ser;
	ser.init("./socket.txt");
	ser.run();
	ser.stop();
	return 0;
}
