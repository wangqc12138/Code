#include "common.h"
using namespace std;
int main(int argc, char* argv[]) {
    string ip = argv[1];
    int port = stoi(argv[2]);
    int sock = Sock(ip, port);
    sockaddr_in cli_addr;
    socklen_t cli_addr_len = sizeof(cli_addr);
    int connfd = accept(sock, (sockaddr*)&cli_addr, &cli_addr_len);
    if (connfd < 0) {
        perror("connect error: ");
    } else {
        char buff[1024];
        int ret;
        memset(buff, '\0', 1024);
        ret = recv(connfd, buff, 1024 - 1, 0);
        printf("got %d bytes of normal data '%s'\n", ret, buff);

        memset(buff, '\0', 1024);
        ret = recv(connfd, buff, 1024 - 1, MSG_OOB);
        printf("got %d bytes of oob data '%s'\n", ret, buff);

        memset(buff, '\0', 1024);
        ret = recv(connfd, buff, 1024 - 1, 0);
        printf("got %d bytes of normal data '%s'\n", ret, buff);
    }
    close(sock);
    return 0;
}
