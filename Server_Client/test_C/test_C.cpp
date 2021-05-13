#include<iostream>
#include "client.h"
using namespace std;
int main()
{
	C_CLIENT cli;
	cli.init("192.168.154.128",23333);
	cli.run();
	cli.stop();
	return 0;
}