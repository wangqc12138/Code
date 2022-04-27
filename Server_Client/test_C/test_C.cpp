#include<iostream>
#include "client.h"
using namespace std;
int main()
{
	C_CLIENT cli;
	cli.init("/home/wangqc/socket/11111");
	cli.run();
	cli.stop();
	return 0;
}