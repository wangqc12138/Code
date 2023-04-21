#include <arpa/inet.h>
#include <bits/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#include <iostream>
using namespace std;

namespace T2 {
static bool stop = false;
static void handle_term(int sig) {
    stop = true;
}
void test() {
    signal(SIGTERM, handle_term);
    char ip[16] = "127.0.0.1";
    int port = 8888;
    int backlog = 5;
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    sockaddr_in add;
    inet_pton(AF_INET, ip, &add.sin_addr);
    add.sin_family = AF_INET;
    add.sin_port = htons(port);
    int ret = bind(sock, (sockaddr*)&add, sizeof(add));
    ret = listen(sock, backlog);
    while (!stop) {
        sleep(1);
    }
    close(sock);
}
}  // namespace T2

int main() {
        T2::test();
    return 0;
    char ip1[16] = "255.255.255.244";
    char ip2[128] = "2c26:3fd5:ffff:fff4:3130:3032:3a30:3033";
    in_addr add1, add2;
    // inet_aton(ip1, &add1);
    // inet_aton(ip2, &add2);
    // char* o1 = inet_ntoa(add1);
    // cout << o1 << endl;
    // char* o2 = inet_ntoa(add2);
    // cout << o1 << endl;
    // cout << o2 << endl;
    inet_pton(AF_INET, ip1, &add1);
    cout << inet_ntoa(add1) << endl;
    inet_pton(AF_INET6, ip2, &add2);
    char ip3[128];
    cout << inet_ntop(AF_INET6, (void*)&add2, ip3, sizeof(ip3)) << endl;
    cout << ip3 << endl;
    char ip4[16];
    cout << inet_ntop(AF_INET, (void*)&add1, ip4, sizeof(ip4)) << endl;
    return 0;
    union {
        short value;
        char union_bytes[sizeof(short)];
        int iunion_bytes[sizeof(short)];
    } test;
    test.value = 0x0102;
    for (auto i : test.iunion_bytes) {
        cout << i << " ";
    }
    cout << endl;
    cout << sizeof(test) << endl;
    if (test.union_bytes[0] == 1 && test.union_bytes[1] == 2) {
        printf("big endian\n");
    } else if (test.union_bytes[0] == 2 && test.union_bytes[1] == 1) {
        printf("litter endian\n");
    } else {
        printf("unknow\n");
    }
    return 0;
}