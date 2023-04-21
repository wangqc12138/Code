# Linux网络编程基础API
## socket地址API
---
### 主机字节序和网络字节序
判断大小端字节序
```c++
#include <stdio.h>
int main() {
    union {
        short value;
        char union_bytes[sizeof(short)];
    } test;
    test.value = 0x0102;
    if (test.union_bytes[0] == 1 && test.union_bytes[1] == 2) {
        printf("big endian\n");
    } else if (test.union_bytes[0] == 2 && test.union_bytes[1] == 1) {
        printf("litter endian\n");
    } else {
        printf("unknow\n");
    }
    return 0;
}
```
- union 共用体 其中的data共享一个存储，修改其中一个其他的也会变化，上例中给value赋值后，unionbyte数组也随之赋值了，但是为什么是char数组，用int数组后，会输出unknow。是因为int是4个字节data就变成第一个元素了258
- 大端字节序：高位放低位存储，小端反之

转换函数
```c++
#include <arpa/inet.h>
// hostlong 主机字节序小端32位
// 传出大端字节序
uint32_t htonl(uint32_t hostlong);
// hostshort 主机字节序小端16位
// 传出大端字节序
uint16_t htons(uint16_t hostshort);
// netlong 网络字节序大端 32位
// 传出小端字节序
uint32_t ntohl(uint32_t netlong);
// netshort 网络字节序大端 16位
// 传出小端字节序
uint16_t ntohs(uint16_t netshort);
```
---
### 通用socket地址
通用socket地址是结构体sockaddr，定义如下
```c++
struct sockaddr {
    // 协议族，包括IPv4 IPv6 本地协议
    __SOCKADDR_COMMON(sa_); /* Common data: address family and length.  */
    // 地址信息 ip端口或者文件地址
    char sa_data[14];       /* Address data.  */
};
#define __SOCKADDR_COMMON(sa_prefix) \
    sa_family_t sa_prefix##family
```
- sa_family_t 是协议族，包含ipv4 ipv6 local
- sa_data 是具体地址，本地的是文件路径，ipv4是ip端口，ipv6是端口标识ip范围id
上面这个结构体会不够长，所以新的定义了一个
```c++
#define __ss_aligntype unsigned long int
#define _SS_PADSIZE \
    (_SS_SIZE - __SOCKADDR_COMMON_SIZE - sizeof(__ss_aligntype))
struct sockaddr_storage {
    // 协议族，包括IPv4 IPv6 本地协议
    __SOCKADDR_COMMON(ss_); /* Address family, etc.  */
    // 地址，更长
    char __ss_padding[_SS_PADSIZE];
    __ss_aligntype __ss_align; /* Force desired alignment.  */
};
```
---
### 专用socket地址
UNIX本地域协议族
```c++
struct sockaddr_un {
    // 协议族
    __SOCKADDR_COMMON(sun_);
    // 文件路径
    char sun_path[108]; /* Path name.  */
};
```
IPv4
```c++
typedef uint32_t in_addr_t;
struct in_addr {
    in_addr_t s_addr;
};
struct sockaddr_in {

    __SOCKADDR_COMMON(sin_);
    //端口
    in_port_t sin_port;      /* Port number.  */
    // 结构体，成员是网络字节序的IP
    struct in_addr sin_addr; /* Internet address.  */

    /* Pad to size of `struct sockaddr'.  */
    unsigned char sin_zero[sizeof(struct sockaddr) -
                           __SOCKADDR_COMMON_SIZE -
                           sizeof(in_port_t) -
                           sizeof(struct in_addr)];
};
```
IPv6
```c++
/* Ditto, for IPv6.  */
struct sockaddr_in6 {
    __SOCKADDR_COMMON(sin6_);
    in_port_t sin6_port;       /* Transport layer port # */
    uint32_t sin6_flowinfo;    /* IPv6 flow information */
    struct in6_addr sin6_addr; /* IPv6 address */
    uint32_t sin6_scope_id;    /* IPv6 scope-id */
};
/* IPv6 address */
struct in6_addr {
    union {
        uint8_t __u6_addr8[16];
        uint16_t __u6_addr16[8];
        uint32_t __u6_addr32[4];
    } __in6_u;
#define s6_addr __in6_u.__u6_addr8
#ifdef __USE_MISC
#define s6_addr16 __in6_u.__u6_addr16
#define s6_addr32 __in6_u.__u6_addr32
#endif
};
```
- 以上函数的IP应该是网络字节序的！
- 专用的地址需要强转成通用的来使用
---
### IP地址转换函数
点分十进制和网络字节序转换
IPv4
```c++
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
typedef uint32_t in_addr_t;
//点分十进制转结构体
// cp点分十进制的ip地址 inp传出的结构体，成员是大端字节序
int inet_aton(const char *cp, struct in_addr *inp);
//点分十进制转大端字节序
// cp点分十进制的ip地址，返回值是大端字节序
in_addr_t inet_addr(const char *cp);
// 结构体转点分十进制
// in in_addr结构体，传出点分十进制的ip
// 内部是静态变量，会覆盖
char *inet_ntoa(struct in_addr in);
```
- inet_ntoa内部是静态变量，重复调用会覆盖

IPv4和IPv6通用
```c++
#include <arpa/inet.h>
// af 协议族 src 传入的ip dst 传出的结构体
int inet_pton(int af, const char *src, void *dst);
// af 协议族 src 传入的结构体需要强转 dst传出的点分十进制 sized dst的长度
const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
```
---
## 创建socket
    在linux中，任何东西都是文件，socket也是一类文件，可读可写可控制可关闭的文件描述符
```c++
#include <sys/socket.h>
#include <sys/types.h>
// domin 协议族 IPv4-PF_NET IPv6-PF_NET6 local-PF_UNIX 
// type 服务类型 stream还是ugram 流类型还是报类型 对应TCP和UDP 
// type 还可以接受SOCK_NONBLOCK和SOCK_CLOEXEC。分别代指非阻塞和创建子进程时在子进程中关闭该socket
// protocol 协议类型 前两个参数几乎确定了协议类型是哪种，所以大多数时候都填0
// 成功返回socket文件描述符 失败返回-1 并设置errorno
extern int socket (int domain, int type, int protocol) __THROW;
```
---
## 命名socket（其实就是绑定）
    创建socket后我们只是给了协议类型和地址族，并没有实际给ip，对于服务端，我们需要绑定一个socket地址。客户端则是采用匿名模式，使用操作系统自动分配的socket地址
```c++
#include <sys/socket.h>
#include <sys/types.h>
struct sockaddr {
    // 协议族，包括IPv4 IPv6 本地协议
    __SOCKADDR_COMMON(sa_); /* Common data: address family and length.  */
    // 地址信息 ip端口或者文件地址
    char sa_data[14];       /* Address data.  */
};
# define __CONST_SOCKADDR_ARG	const struct sockaddr *
// fd 创建的socket描述符 addr地址结构体 len结构体长度
// 成功返回0 失败返回-1 常见errorno是EACCES被绑定的地址是受保护的（0-1023端口）
// 还有一个是EADDRINUSE 被绑定的地址还在使用，比如TIME_WAIT状态的ip端口
extern int bind (int fd, __CONST_SOCKADDR_ARG addr, socklen_t len)  
```
---
## 监听socket
    绑定地址后的socket，还不能马上就接受客户端的连接 需要创建一个监听队列来存放待处理的客户端连接
```c++
#include <sys/socket.h>
// fd 绑定地址的socket文件描述符 n内核监听队列的最大长度 监听长度如果超过n，那么不再接受客户连接
// 客户端会收到ECONNREFUSED的错误码
// 2.2之后是完全连接的socket上限，半连接状态由tcp_max_syn_backlog内核设置
// 典型值是5
// 成功返回0 失败返回-1
extern int listen (int __fd, int __n) __THROW;
```
---
## 接受连接
```c++
#include <sys/socket.h>
#include <sys/types.h>
// fd 执行过listen系统调用的监听socket
// addr 获取被接受连接的远端socket地址
// len 指出该sokcet地址的长度
// 执行成功返回一个socket 该socket唯一的标识了被接受的这个连接 
extern int accept (int __fd, __SOCKADDR_ARG __addr,  socklen_t *__restrict __addr_len);
```
    如果监听队列中处于ESTABLISHED状态的连接对应的客户端出现网络异常，或者提前退出，那么服务器这个
accept调用是否成功
```c++
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
    printf("local ip is %s,port is %d\n", ip.c_str(), port);
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
```
    断网--ESTABLISHED 提前关telnet程序--close_wait
    但是无论哪种情况accept都会从监听队列中取出连接
---
## 发起连接
```c++
// fd是调用返回一个socket
// addr是服务器监听的socket地址
// len是指定这个socket地址的长度
// 成功返回0
// 常见错误码 ECONNREFUSED 端口不存在 ETIMEDOUT 重连后还超时的
extern int connect (int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len);
```
---
## 关闭连接
```c++
#include <unistd.h>
// fd参数是待关闭的socket
int close(int fd);
```
    close系统的调用并非总是立即关闭一个连接，而是将fd的引用计数减一，只有引用计数位0，才真正关闭连接
    多进程程序中，一次fork系统调用默认将父进程中打开的socket引用计数加一，因此我们必须在父进程和子进程都对该socket执行close调用才能将连接关闭  
    如果需要立即终止连接，可以调用shutdown系统调用
```c++
#include <sys/socket.h>
// sockfd待关闭的socket howto 决定shutdown的行为
// SHUT_RD 关闭读的这一半，不能执行读操作，并且该socket接受缓冲区的数据都丢弃
// SHUT_WR 关闭写的这一半，不能执行写操作，并且该socket发送缓冲区的数据会在真正关闭连接前全发送出去，称为半关闭状态
// SHUT_RDWR 读写都关闭
int shutdown(int sockfd,int howto);
```
---
## 数据读写
--- 
### TCP数据读写
```c++
#include <sys/types.h>
#include <sys/socket.h>
// fd socket
// buf 缓冲区 n 缓冲区大小 flags 特殊参数 通常为0
// n有可能小于实际长度 需要多次调用才能读取完整。返回0意味对方已经关闭连接
extern ssize_t recv (int __fd, void *__buf, size_t __n, int __flags);
// fd socket
// buf 缓冲区 n缓冲区大小 flags 特殊参数
// 成功返回send实际长度
extern ssize_t send (int __fd, const void *__buf, size_t __n, int __flags);
```
    MSG_CONFIRM(SEND) 指示链路层持续监听对方的回应，直到得到回复。仅能用于SOCK_DGRAM和SOCK_RAW  
    MSG_DONTROUTE(SEND) 不查看路由表，直接将数据发送给本地局域网内的主机。这表示发送者确切知道目标主机实在本地网络  
    MSG_DONTWAIT(ALL) 对socket的此次操作时非阻塞的  
    MSG_MORE(SEND) 告诉内核应用程序还有更多数据要发送，内核将超时等待新数据写入TCP发送缓冲区一并发送  
    MSG_WAITALL(RECV) 读操作仅在读取到指定数量的字节后才返回  
    MSG_PEEK(RECV) 窥探读缓存中的数据，此次读操作不会导致这些数据被清除  
    MSG_OOB(ALL) 发送或接受紧急数据  
    MSG_NOSIGNAL(SEND) 往读端关闭的管道或者socket连接中写数据时不引发SICPIPE信号  
```c++
#ifndef __COMMON_H__
#define __COMMON_H__

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <string>
using namespace std;
#define BUF_SIZ 1024
int Sock(const string& ip, int port) {
    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);
    addr.sin_port = htons(port);
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    bind(sock, (sockaddr*)&addr, sizeof(addr));
    listen(sock, 5);
    return sock;
}
#endif
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
        ret = recv(connfd, buff, 1024 - 1, 0);
        printf("got %d bytes of oob data '%s'\n", ret, buff);

        memset(buff, '\0', 1024);
        ret = recv(connfd, buff, 1024 - 1, 0);
        printf("got %d bytes of normal data '%s'\n", ret, buff);
    }
    close(sock);
    return 0;
}
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
        const char* oob_data = "abc";
        const char* nor_data = "123";
        // sizeof是字节数 strlen是字符数不包括\0
        send(sockfd, nor_data, strlen(nor_data), 0);
        send(sockfd, oob_data, strlen(oob_data), 0);
        send(sockfd, nor_data, strlen(nor_data), 0);
    }
    close(sockfd);
    return 0;
}
```
---
### UDP数据读写
```c++
// sockfd sock地址 buf 接受缓冲区，len 缓冲区大小，flags 与上文的一样
// 由于UDP没有连接的概念，所以每次读取数据都需要获取发送端的socket地址，即sockaddr和长度
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
// 类似
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
```
    以上两个函数都可以用于stream连接的读写，最后两个参数设置为NULL即可

### 通用数据读写
```c++
struct iovec {                    /* Scatter/gather array items */
    void  *iov_base;              /* Starting address */
    size_t iov_len;               /* Number of bytes to transfer */
};
struct msghdr {
    void         *msg_name;       /* optional address */
    socklen_t     msg_namelen;    /* size of address */
    struct iovec *msg_iov;        /* scatter/gather array */
    size_t        msg_iovlen;     /* # elements in msg_iov */
    void         *msg_control;    /* ancillary data, see below */
    size_t        msg_controllen; /* ancillary data buffer len */
    int           msg_flags;      /* flags on received message */
};
// TCP中msgname和len设为NULL
// iov是存放数据的，iovlen是指有多少个。分散读，集中写
// control是辅助数据传输的
// flags会复制flags
ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);
ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);
```
---
## 带外标记
    我们通常无法预期带外数据什么时候来，有两种方式检测
    1、I/O复用产生的异常事件
    2、SICURG信号
    接收到通知后，需要知道带外数据在数据流中的具体位置
```c++
// 判断sockfd是否处于带外标记，即下一个被读取到的数据是否是带外数据
// 是返回1，不是返回0
int sockatmark(int sockfd);
```
---
## 地址信息函数
    用于查看连接的本端socket地址和远端socket地址
```c++
//获取本端socket地址，存储于addr参数的内存中 成功返回0 失败返回-1
int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
//获取远端socket地址，存储于addr参数的内存中 成功返回0 失败返回-1
int getpeername(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```
---
## socket选项
    fcntl是控制文件描述符属性的通用posix方法
    以下是控制socket文件描述符属性的方法
```c++
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
// sockfd 被操作的socket，level参数指定要操作哪个协议的选项，如IPv4\IPV6\TCP等
// optname指定选项的名字 optval指定选项的值 optlen指定选项的长度
int getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen);
int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
```
    部分socket选项只能在调用listen系统调用前针对监听socket才有效。这是因为连接socket只能有accept调用返回，而accept从监听队列中接受的连接至少已经完成了TCP前两个步骤（因为listen监听队列中的连接至少已经进入SYN_RCVD状态）这说明服务器已经往被接受连接上发送出了TCP同步报文段。但有的socket选项却应该在TCP同步报文段中设置，如TCP最大报文段选项。对于这种情况：对监听socket设置这些socket选项，那么accept返回的连接socket将自动继承这些选项。
- SO_RCVBUF和SO_SNDBUF
分别表示TCP接受缓冲区和发送缓冲区的大小，我们使用setsockopt来设置时，系统都会将其值加倍，并且不得小于某个最小值，接受缓冲区最小值为256字节，发送最小值为2048字节。系统这样做的目的，主要是确保一个TCP连接拥有足够的空闲缓冲区来处理拥塞（比如快速重传算法就期望TCP接受缓冲区至少容纳4个SMSS的TCP报文段）。此外可以直接修改内核参数来使没有最小值限制。

# I/O复用
---
## select系统调用
select系统调用的用途是：在一段指定时间内，监听用户感兴趣的文件描述符上的可读，可写和异常等时间。  
### select API
#### 调用原型
```c++
/* According to POSIX.1-2001, POSIX.1-2008 */
#include <sys/select.h>
/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
// nfds 指定被监听的文件描述符的总数。它通常被设置为select监听的所有文件描述符中的最大值+1，因为
// 因为文件描述符是从0开始计数的
// readfds writefds excepttfds分别指可读，可写，异常等事件对应的文件描述符集合
// 程序调用select函数时，通过这3个参数传入感兴趣的文件描述符
// 程序调用返回时，返回已就绪的文件描述符
// fd_set结构体包含一个整型数组 数组元素的每个位标记一个文件描述符 最大1024 
// timeout 超时时间，指针调用是返回时select等待了多久，但是这个值不可靠，select调用失败时不确定
// 微秒级定时 如果传递0，立即返回，如果传递NULL，一直阻塞，直到某个文件描述符就绪
// 成功返回已就绪的文件描述符数，超时返回0，失败返回-1，收到信号返回-1，errno置为EINTR
int select(int nfds, fd_set *readfds, fd_set *writefds,
    fd_set *exceptfds, struct timeval *timeout);
// 清除fd_set的位fd
void FD_CLR(int fd, fd_set *set);
// 测试fd_set的位fd是否设置
int  FD_ISSET(int fd, fd_set *set);
// 设置fd_set的位fd
void FD_SET(int fd, fd_set *set);
// 清除fd_set所有位
void FD_ZERO(fd_set *set);
#include <sys/select.h>
int pselect(int nfds, fd_set *readfds, fd_set *writefds,
    fd_set *exceptfds, const struct timespec *timeout,
    const sigset_t *sigmask);
```
---
#### 就绪条件
可读
    socket内核接收缓冲区中的字节数大于等于低水位标记SO_RCVLOWAT。此时我们可以无阻塞地读该socket，并且读操作返回的字节数大于0
    socket通信的对方关闭连接，此时对socket的读操作将返回0
    监听socket有新的连接请求
    socket上有未处理的错误。此时我们可以使用getsockopt来读取和清除该错误
可写
    socket内核发送缓冲区中的字节数大于等于低水位标记SO_SNDLOWAT。此时我们可以无阻塞地写该socket。并且写操作返回的字节数大于0
    sokcet的写操作被关闭。对写操作被关闭的socket执行写操作将触发SIGPIPE信号
    socket使用非阻塞connect连接成功或失败（超时）之后
    socket上有未处理的错误。此时我们可以使用getsockopt来读取和清除该错误
异常
    socket上接受到带外数据

### poll系统调用
```c++
#include <poll.h>
struct pollfd {
    int   fd;         // 文件描述符
    short events;     /* requested events 注册的事件*/
    short revents;    /* returned events 实际发生的事件，由内核填充*/
};
// fd指定文件描述符，events成员告诉poll监听fd上的那些时间，一系列事件的按位与
// revents 由内核修改，告诉应用程序fd上实际发生了那些事件
// fds参数时pollfd结构体，指定所有我们感兴趣的文件描述符上发生的可读，可写和异常的事件
// nfds指定被监听事件集合fds的大小。unsigned long int
// timeout指定poll超时值，单位毫秒，传入-1，永远阻塞，知道事件发生，传入0，立即返回
// 返回值就绪的事件数
int poll(struct pollfd *fds, nfds_t nfds, int timeout);
#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <signal.h>
#include <poll.h>
int ppoll(struct pollfd *fds, nfds_t nfds,
        const struct timespec *tmo_p, const sigset_t *sigmask);
```
### epoll系列系统调用
#### 内核事件表
