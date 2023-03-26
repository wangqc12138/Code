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
uint32_t htonl(uint32_thostlong);
uint16_t htons(uint16_thostshort);
uint32_t ntohl(uint32_tnetlong);
uint16_t ntohs(uint16_tnetshort);
```
---
### 通用socket地址
通用socket地址是结构体sockaddr，定义如下
```c++
struct sockaddr {
    __SOCKADDR_COMMON(sa_); /* Common data: address family and length.  */
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
    __SOCKADDR_COMMON(ss_); /* Address family, etc.  */
    char __ss_padding[_SS_PADSIZE];
    __ss_aligntype __ss_align; /* Force desired alignment.  */
};
```
---
### 专用socket地址
UNIX本地域协议族
```c++
struct sockaddr_un {
    __SOCKADDR_COMMON(sun_);
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
    in_port_t sin_port;      /* Port number.  */
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
int inet_aton(const char *cp, struct in_addr *inp);
//点分十进制转大端字节序
in_addr_t inet_addr(const char *cp);
//点分十进制转小端字节序
in_addr_t inet_network(const char *cp);
// 结构体转点分十进制
char *inet_ntoa(struct in_addr in);

struct in_addr inet_makeaddr(in_addr_t net, in_addr_t host);

in_addr_t inet_lnaof(struct in_addr in);

in_addr_t inet_netof(struct in_addr in);
```
- inet_ntoa内部是静态变量，重复调用会覆盖

IPv4和IPv6通用
```c++
#include <arpa/inet.h>

int inet_pton(int af, const char *src, void *dst);
const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
```