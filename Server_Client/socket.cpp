#include "socket.h"
int Socket::Close(int fd){
    int ret=close(fd);
    if(-1==ret){
        perror("close fd error!");
        return -1;
    }
    return 0;
}
int Socket::Connet(const string strIp,const int iPort){
    int ret,family=AF_INET;
    if(strIp.find(':')!=string::npos){
        family=AF_INET6;
    }
    if(m_iHandle!=-1){
        Close(m_iHandle);
    }
    m_iHandle=socket(family,SOCK_STREAM,0);
    if(-1==m_iHandle){
        perror("create socket error!");
        return -1;
    }
    //int connect(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
    sockaddr_in sa;
    sa.sin_family=family;
    sa.sin_port=htons(iPort);
    inet_pton(family,strIp.c_str(),&sa.sin_addr.s_addr);
    ret=connect(m_iHandle,(const struct sockaddr*)&sa,sizeof(sa));
    if(ret==-1){
        perror("connet error!");
        return -1;
    }
    return 0;
}
int Socket::Listen(const string strIp,const int iPort){
    int ret,family=AF_INET;
    if(strIp.find(':')!=string::npos){
        family=AF_INET6;
    }
    //int socket(int domain, int type, int protocol);
    if(m_iHandle!=-1){
        Close(m_iHandle);
    }
    m_iHandle=socket(family,SOCK_STREAM,0);
    if(-1==m_iHandle){
        perror("create socket error!");
        return -1;
    }
    //int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
    sockaddr_in sa;
    sa.sin_family=family;
    sa.sin_port=htons(iPort);
    //int inet_pton(int af, const char *src, void *dst);
    inet_pton(family,strIp.c_str(),&sa.sin_addr.s_addr);
    ret=bind(m_iHandle,(const struct sockaddr*) &sa,sizeof(sa));
    if(-1==ret){
        perror("sock bind error!");
        return -1;
    }
    //int listen(int sockfd, int backlog);
    ret=listen(m_iHandle,10);
    if(-1==ret){
        perror("sock listen error!");
        return -1;
    }
    return m_iHandle;
}
int Socket::Accept(int iSockfd){
    int ret;
    // int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    struct sockaddr_in c_sa;
    int salen=sizeof(c_sa);
    ret=accept(iSockfd,(struct sockaddr*) &c_sa,(socklen_t *)&salen);
    if(-1==ret){
        perror("accept error!");
        return -1;
    }
    char cip[50];
    int cport;
    inet_ntop(m_iFamily,&c_sa.sin_addr.s_addr,cip,salen);
    cport=ntohs(c_sa.sin_port);
    printf("client ip is %s,port is %d\n",cip,cport);
    return ret;
}
int Socket::Write(const string strMsg){
    return 0;
}
int Socket::Read(string &strMsg){
    return 0;
}