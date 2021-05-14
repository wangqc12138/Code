#ifndef COMMON_H
#define COMMON_H
#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>
//ls,pwd,cd的实现
#include <dirent.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
/* According to POSIX.1-2001, POSIX.1-2008 */
#include <sys/select.h>
/* for poll */
#include <poll.h>
/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

#define MAXSIZE 1024

#endif