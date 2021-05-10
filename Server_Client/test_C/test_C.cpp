#include<iostream>
#include "client.h"
using namespace std;
int main()
{
	C_CLIENT cli;
	cli.init("192.168.239.132",23333);
	cli.run();
	return 0;
}