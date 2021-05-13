#ifndef CMD_H
#define CMD_H
#include "common.h"
int cd(const char* dir);
int ls(char* buf);
int pwd(char* workdir);
int cmd(char* buf);
#endif