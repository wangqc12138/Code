#include "../common.h"
using namespace std;
#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 10
int setnonblocking(int fd) {
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}
void addfd(int epollfd, int fd, bool enable_et) {
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    if (enable_et) {
        event.events |= EPOLLET;
    }
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    setnonblocking(fd);
}
void lt(epoll_event* events, int number, int epollfd, int listenfd) {
    printf("function lt(...) in\n");
    char buf[BUFFER_SIZE];
    for (int i = 0; i < number; i++) {
        int sockfd = events[i].data.fd;
        if (sockfd == listenfd) {
            printf("event accept trigger once\n");
            sockaddr_in client_address;
            socklen_t client_len = sizeof(client_address);
            int connfd = accept(listenfd, (sockaddr*)&client_address, &client_len);
            addfd(epollfd, connfd, false);
        } else if (events[i].events & EPOLLIN) {
            printf("event recv trigger once\n");
            memset(buf, '\0', BUFFER_SIZE);
            int ret = recv(sockfd, buf, BUFFER_SIZE, 0);
            if (ret <= 0) {
                close(sockfd);
                continue;
            }
            printf("get %d bytes of content: %s\n", ret, buf);
            // while (1) {
            //     memset(buf, '\0', BUFFER_SIZE);
            //     int ret = recv(sockfd, buf, BUFFER_SIZE, 0);
            //     if (ret < 0) {
            //         if (errno == EAGAIN || errno == EWOULDBLOCK) {
            //             printf("read later\n");
            //             break;
            //         }
            //         close(sockfd);
            //         break;
            //     } else if (ret == 0) {
            //         close(sockfd);
            //     } else {
            //         printf("get %d bytes of content: %s\n", ret, buf);
            //     }
            // }
        } else {
            printf("something else happened\n");
        }
    }
}
void et(epoll_event* events, int number, int epollfd, int listenfd) {
    printf("function et(...) in\n");
    char buf[BUFFER_SIZE];
    for (int i = 0; i < number; i++) {
        int sockfd = events[i].data.fd;
        if (sockfd == listenfd) {
            printf("event accept trigger once\n");
            sockaddr_in client_address;
            socklen_t client_len = sizeof(client_address);
            int connfd = accept(listenfd, (sockaddr*)&client_address, &client_len);
            addfd(epollfd, connfd, true);
        } else if (events[i].events & EPOLLIN) {
            printf("event recv trigger once\n");
            memset(buf, '\0', BUFFER_SIZE);
            int ret = recv(sockfd, buf, BUFFER_SIZE, 0);
            if (ret <= 0) {
                close(sockfd);
                continue;
            }
            printf("get %d bytes of content: %s\n", ret, buf);
            // while (1) {
            //     memset(buf, '\0', BUFFER_SIZE);
            //     int ret = recv(sockfd, buf, BUFFER_SIZE, 0);
            //     if (ret < 0) {
            //         if (errno == EAGAIN || errno == EWOULDBLOCK) {
            //             printf("read later\n");
            //             break;
            //         }
            //         close(sockfd);
            //         break;
            //     } else if (ret == 0) {
            //         close(sockfd);
            //     } else {
            //         printf("get %d bytes of content: %s\n", ret, buf);
            //     }
            // }
        } else {
            printf("something else happened\n");
        }
    }
}
int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }
    string ip = argv[1];
    int port = stoi(argv[2]);
    bool flag = false;
    if (argc >= 4) {
        flag = ((string)argv[3] == "ET");
    }
    if (flag) {
        printf("ET\n");
    } else {
        printf("LT\n");
    }
    sockaddr_in addr;
    // memset 每个字节置为val，除0 -1外均不可
    // fill 每个值置为val
    // bzero 每个字节置为0
    // fill(&addr, &addr + sizeof(addr), 0);
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip.c_str(), &(addr.sin_addr));
    addr.sin_port = htons(port);
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (bind(listenfd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("error: ");
        return -1;
    }
    if (listen(listenfd, 5)) {
        perror("error: ");
        return -1;
    }
    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd = epoll_create(5);
    assert(epollfd != -1);
    addfd(epollfd, listenfd, true);
    while (1) {
        int ret = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
        if (ret < 0) {
            printf("epoll failure\n");
            break;
        }
        if (flag) {
            et(events, ret, epollfd, listenfd);
        } else {
            lt(events, ret, epollfd, listenfd);
        }
    }
    close(listenfd);
    return 0;
}