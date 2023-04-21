#include "../common.h"
using namespace std;
#define BUFFER_SIZE 64
int main(int argc, char* argv[]) {
    if (argc <= 2) {
        return 1;
    }
    const char* ip = argv[1];
    int port = stoi(argv[2]);
    int ret;
    sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);
    ret = connect(sockfd, (sockaddr*)&address, sizeof(address));
    pollfd fds[2];
    fds[0].fd = 0;
    fds[0].events = POLLIN;
    fds[0].revents = 0;
    fds[1].fd = sockfd;
    fds[1].events = POLLIN | POLLRDHUP;
    fds[1].revents = 0;
    char read_buf[BUFFER_SIZE];
    int pipefd[2];
    ret = pipe(pipefd);
    while (1) {
        ret = poll(fds, 2, -1);
        if (ret < 0) {
            printf("poll failure\n");
        }
        if (fds[1].revents & POLLHUP) {
            printf("server close the connection\n");
            break;
        } else if (fds[1].revents & POLLIN) {
            memset(read_buf, '\0', sizeof(read_buf));
            ret = recv(fds[1].fd, read_buf, BUFFER_SIZE, 0);
            printf("%s\n", read_buf);
        }
        if (fds[0].revents & POLLIN) {
            ret = splice(0, NULL, pipefd[1], NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE);
            ret = splice(pipefd[0], NULL, sockfd, NULL, 32768, SPLICE_F_MORE | SPLICE_F_MOVE);
        }
    }
    close(sockfd);
    return 0;
}