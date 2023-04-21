#include "../common.h"
#define USER_LIMIT 5
#define BUFFER_SIZE 64
#define FD_LIMIT 65535
struct client_data {
    sockaddr_in address;
    char* write_buf;
    char buf[BUFFER_SIZE];
};
int setnonblocking(int fd) {
    int old_option = fcntl(fd, F_GETFD);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, new_option);
    return old_option;
}
int main(int argc, char* argv[]) {
    if (argc <= 2) {
        return 1;
    }
    const char* ip = argv[1];
    int port = stoi(argv[2]);
    int ret;
    sockaddr_in addr;
    // memset 每个字节置为val，除0 -1外均不可
    // fill 每个值置为val
    // bzero 每个字节置为0
    // fill(&addr, &addr + sizeof(addr), 0);
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &(addr.sin_addr));
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
    client_data* users = new client_data[FD_LIMIT];
    pollfd fds[USER_LIMIT + 1];
    int user_counter = 0;
    for (int i = 1; i <= USER_LIMIT; i++) {
        fds[i].fd = -1;
        fds[i].events = 0;
    }
    fds[0].fd = listenfd;
    fds[0].events = POLLIN | POLLERR;
    fds[0].revents = 0;
    while (1) {
        ret = poll(fds, user_counter + 1, -1);
        if (ret < 0) {
            printf("poll failure\n");
        }
        for (int i = 0; i < user_counter + 1; i++) {
            if (fds[i].fd == listenfd && (fds[i].revents & POLLIN)) {
                sockaddr_in client_address;
                socklen_t client_address_len = sizeof(client_address);
                int connfd = accept(listenfd, (sockaddr*)&client_address, &client_address_len);
                if (connfd < 0) {
                    printf("error no is %d\n", errno);
                    continue;
                }
                if (user_counter >= USER_LIMIT) {
                    const char* info = "too many user\n";
                    printf("%s", info);
                    send(connfd, info, strlen(info), 0);
                    close(connfd);
                    continue;
                }
                user_counter++;
                users[connfd].address = client_address;
                setnonblocking(connfd);
                fds[user_counter].fd = connfd;
                fds[user_counter].events = POLLIN | POLLHUP | POLLERR;
                fds[user_counter].revents = 0;
                printf("come a new user,now have %d users\n", user_counter);
            } else if (fds[i].revents & POLLERR) {
                printf("get an error from %d\n", fds[i].fd);
                char errors[100];
                memset(errors, '\0', 100);
                socklen_t len = sizeof(errors);
                if (getsockopt(fds[i].fd, SOL_SOCKET, SO_ERROR, &errors, &len) < 0) {
                    printf("get socket option error failed\n");
                }
                continue;
            } else if (fds[i].revents & POLLHUP) {
                users[fds[i].fd] = users[fds[user_counter].fd];
                close(fds[i].fd);
                fds[i] = fds[user_counter];
                i--;
                user_counter--;
                printf("a client left\n");
            } else if (fds[i].revents & POLLIN) {
                int connfd = fds[i].fd;
                memset(users[connfd].buf, '\0', BUFFER_SIZE);
                ret = recv(connfd, users[connfd].buf, BUFFER_SIZE, 0);
                printf("get %d bytes of client data %s from %d\n", ret, users[connfd].buf, connfd);
                if (ret < 0) {
                    if (errno != EAGAIN) {
                        users[fds[i].fd] = users[fds[user_counter].fd];
                        close(fds[i].fd);
                        fds[i] = fds[user_counter];
                        i--;
                        user_counter--;
                    }
                } else if (ret == 0) {
                    //
                } else {
                    for (int j = 1; j <= user_counter; j++) {
                        if (fds[j].fd == connfd) {
                            continue;
                        }
                        // ~代表取反
                        fds[j].events |= ~POLLIN;
                        fds[j].events |= POLLOUT;
                        users[fds[j].fd].write_buf = users[connfd].buf;
                    }
                }
            } else if (fds[i].revents & POLLOUT) {
                int connfd = fds[i].fd;
                if (users[connfd].write_buf == nullptr) {
                    continue;
                }
                ret = send(connfd, users[connfd].write_buf, strlen(users[connfd].write_buf), 0);
                users[connfd].write_buf = nullptr;
                fds[i].events |= ~POLLOUT;
                fds[i].events |= POLLIN;
            }
        }
    }
    delete[] users;
    close(listenfd);
    return 0;
}