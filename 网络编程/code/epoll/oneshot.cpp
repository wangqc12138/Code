#include "../common.h"
using namespace std;
#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 1024
struct fds {
    int epollfd;
    int sockfd;
};

int setnonblocking(int fd) {
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}
void addfd(int epollfd, int fd, bool oneshot) {
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    if (oneshot) {
        event.events |= EPOLLONESHOT;
    }
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    setnonblocking(fd);
}
void reset_oneshot(int epollfd, int fd) {
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event);
}
void* work(void* arg) {
    int sockfd = ((fds*)arg)->sockfd;
    int epollfd = ((fds*)arg)->epollfd;
    char buf[BUFFER_SIZE];
    // memset(buf, '\0', BUFFER_SIZE);
    printf("start new thread %lld to receive data on fd: %d\n", pthread_self(), sockfd);
    while (1) {
        memset(buf, '\0', BUFFER_SIZE);
        int ret = recv(sockfd, buf, BUFFER_SIZE, 0);
        if (ret < 0) {
            if (errno == EAGAIN) {
                reset_oneshot(epollfd, sockfd);
                printf("read later\n");
                break;
            }
            close(sockfd);
            break;
        } else if (ret == 0) {
            close(sockfd);
            printf("foreiner closed the connection\n");
            break;
        } else {
            printf("get %d bytes of content: %s\n", ret, buf);
            sleep(5);
        }
    }
    printf("end new thread %lld to receive data on fd: %d\n", pthread_self(), sockfd);
    return NULL;
}
int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }
    string ip = argv[1];
    int port = stoi(argv[2]);
    // bool flag = ((string)argv[3] == "ET");
    // if (flag) {
    //     printf("ET\n");
    // } else {
    //     printf("LT\n");
    // }
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
    addfd(epollfd, listenfd, false);
    while (1) {
        int ret = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
        if (ret < 0) {
            printf("epoll failure\n");
            break;
        }
        for (int i = 0; i < ret; i++) {
            int sockfd = events[i].data.fd;
            if (sockfd == listenfd) {
                sockaddr_in client_address;
                socklen_t client_len = sizeof(client_address);
                int connfd = accept(listenfd, (sockaddr*)&client_address, &client_len);
                addfd(epollfd, connfd, true);
            } else if (events[i].events & EPOLLIN) {
                pthread_t thread;
                fds fds_for_new_worker;
                fds_for_new_worker.epollfd = epollfd;
                fds_for_new_worker.sockfd = sockfd;
                pthread_create(&thread, NULL, work, (void*)&fds_for_new_worker);
            } else {
                printf("something else happened\n");
            }
        }
    }
    close(listenfd);
    return 0;
}