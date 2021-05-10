#include<iostream>
#include "client.h"
using namespace std;
int main()
{
	C_CLIENT cli;
	cli.init("192.168.154.128",8888);
	cli.run();
	return 0;
}