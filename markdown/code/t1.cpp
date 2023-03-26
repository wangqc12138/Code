#include <arpa/inet.h>
#include <bits/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <iostream>
using namespace std;

int main() {
    char ip[32] = "1.1.1.1";
    int adr;
    inet_pton(AF_INET, ip, &adr);
    cout << adr << endl;
    // char str[INET_ADDRSTRLEN];
    // cout << inet_ntop(AF_INET, &adr, str, sizeof(str)) << endl;
    // cout << str << endl;
    for (int i = 16; i >= 0; i--) {
        cout << "i:" << i << endl;
        char s[i];
        cout << inet_ntop(AF_INET, &adr, s, i) << endl;
        cout << s << endl;
    }

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