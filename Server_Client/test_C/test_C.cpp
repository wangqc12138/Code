#include<iostream>
#include "client.h"
using namespace std;
int main()
{
	C_CLIENT cli;
	cli.init("./socket.txt");
	cli.run();
	cli.stop();
	return 0;
}