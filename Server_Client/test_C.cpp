#include<iostream>
#include"socket.h"
using namespace std;
int main()
{
	Socket cli;
    cli.Connet("192.168.154.128",8888);
	return 0;
}