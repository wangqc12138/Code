#include "common.h"
// select API
#include <sys/select.h>

#include <iostream>
using namespace std;
int main(int argc, char* argv[]) {
    if (argc <= 2) {
        return 1;
    }
    const char* ip = argv[1];
    int port = stoi(argv[2]);
    int ret = 0;
    sockaddr_in address, client;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(listenfd, (sockaddr*)(&address), sizeof(address));
    listen(listenfd, 10);
    socklen_t client_len = sizeof(client);
    int connfd = accept(listenfd, (sockaddr*)&client, &client_len);
    char buf[1024];
    fd_set read_fds;
    fd_set exception_fds;
    FD_ZERO(&read_fds);
    FD_ZERO(&exception_fds);
    while (1) {
        // memset(buf, '\0', sizeof(buf));
        FD_SET(connfd, &read_fds);
        FD_SET(connfd, &exception_fds);
        ret = select(connfd + 1, &read_fds, NULL, &exception_fds, NULL);
        if (FD_ISSET(connfd, &read_fds)) {
            memset(buf, '\0', sizeof(buf));
            ret = recv(connfd, buf, sizeof(buf) - 1, 0);
            if (ret <= 0) {
                break;
            }
            printf("get %d bytes of normal data:%s\n", ret, buf);
        } else if (FD_ISSET(connfd, &exception_fds)) {
            // 如果带外数据不止1个字节，那将随后触发读事件
            memset(buf, '\0', sizeof(buf));
            ret = recv(connfd, buf, sizeof(buf) - 1, MSG_OOB);
            if (ret <= 0) {
                break;
            }
            printf("get %d bytes of oob data:%s\n", ret, buf);
        }
    }
    close(connfd);
    close(listenfd);
    return 0;
}