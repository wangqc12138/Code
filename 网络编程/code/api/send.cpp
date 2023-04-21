#include "common.h"
using namespace std;
int main(int argc, char* argv[]) {
    string ip = argv[1];
    int port = stoi(argv[2]);
    sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr);
    serv_addr.sin_port = htons(port);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect error: ");
    } else {
        // string 带/0 所以输出是空
        // string oob_data = "abc";

        const char* oob_data = "c";
        const char* nor_data = "123";
        // sizeof是字节数 strlen是字符数不包括\0
        // send(sockfd, nor_data, strlen(nor_data), 0);
        send(sockfd, oob_data, strlen(oob_data), MSG_OOB);
        // send(sockfd, nor_data, strlen(nor_data), 0);
    }
    sleep(1000);
    close(sockfd);
    return 0;
}
