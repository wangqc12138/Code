#ifndef __COMMON_H__
#define __COMMON_H__

#include <arpa/inet.h>
#include <assert.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
using namespace std;
#define BUF_SIZ 1024
int Sock(const string& ip, int port) {
    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);
    addr.sin_port = htons(port);
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    bind(sock, (sockaddr*)&addr, sizeof(addr));
    listen(sock, 5);
    return sock;
}
#endif