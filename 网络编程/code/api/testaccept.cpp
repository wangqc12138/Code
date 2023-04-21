#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }
    string ip = argv[1];
    int port = stoi(argv[2]);
    sockaddr_in addr;
    // memset 每个字节置为val，除0 -1外均不可
    // fill 每个值置为val
    // bzero 每个字节置为0
    // fill(&addr, &addr + sizeof(addr), 0);
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip.c_str(), &(addr.sin_addr));
    addr.sin_port = htons(port);
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (bind(sock, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("error: ");
        return -1;
    }
    if (listen(sock, 5)) {
        perror("error: ");
        return -1;
    }
    sleep(20);
    sockaddr_in cli_addr;
    socklen_t cli_addr_len = sizeof(cli_addr);
    int connfd = accept(sock, (sockaddr*)&cli_addr, &cli_addr_len);
    if (connfd < 0) {
        perror("error: ");
    } else {
        char cli_ip[INET_ADDRSTRLEN];
        printf("IP is %s,port is %d\n", inet_ntop(AF_INET, &cli_addr.sin_addr, cli_ip, INET_ADDRSTRLEN), ntohs(cli_addr.sin_port));
    }
    close(sock);
    return 0;
}