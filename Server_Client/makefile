#设置编译器
CC=g++
CFLAGS=-I ../Sock/ -I ../include -I ../Client -I ../Server
#debug文件夹里的makefile文件需要最后执行，所以这里需要执行的子目录要排除debug文件夹，这里使用awk排除了debug文件夹，读取剩下的文件夹
#SUBDIRS=$(shell ls -l | grep ^d | awk '{if($$9 != "test_S" && $$9 != "include" && $$9 != "test_C") print $$9}')
SUBDIRS= Sock Cmd Client Server test_C test_S 
#无需下一行的注释代码，因为我们已经知道debug里的makefile是最后执行的，所以最后直接去debug目录下执行指定的makefile文件就行，具体下面有注释
#DEBUG=$(shell ls -l | grep ^d | awk '{if($$9 == "debug") print $$9}')
#记住当前工程的根目录路径
ROOT_DIR=$(shell pwd)
#最终bin文件的名字，可以更改为自己需要的
SER_DEST=server
CLI_DEST=client
#目标文件所在的目录
BUILD_DIR=$(ROOT_DIR)/build
#bin文件所在的目录
BIN_DIR=$(ROOT_DIR)/bin
#获取当前目录下的c文件集，放在变量CUR_SOURCE中
#CUR_SOURCE=${wildcard *.c}
#将对应的c文件名转为o文件后放在下面的CUR_OBJS变量中
#CUR_OBJS=${patsubst %.c, %.o, $(CUR_SOURCE)}
#将以下变量导出到子shell中，本次相当于导出到子目录下的makefile中
export CC SER_DEST CLI_DEST BUILD_DIR BIN_DIR ROOT_DIR CFLAGS
#注意这里的顺序，需要先执行SUBDIRS最后才能是DEBUG
all:$(SUBDIRS)  server client ECHO #$(CUR_OBJS)
#递归执行子目录下的makefile文件，这是递归执行的关键
$(SUBDIRS):ECHO
	make -C $@
OBJS=$(shell find ./build -name "*.o"|grep -v "test_C.o"|grep -v "client.o")
server:
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $(OBJS)
OBJC=$(shell find ./build -name "*.o"|grep -v "test_S.o"|grep -v "server.o")
client:
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $(OBJC)
ECHO:
	@echo $(SUBDIRS)
#将c文件编译为o文件，并放在指定放置目标文件的目录中即OBJS_DIR
#$(CUR_OBJS):%.o:%.c
#	$(CC) -c $^ -o $(ROOT_DIR)/$(OBJS_DIR)/$@
clean:
	@find . -name "*.o"|xargs rm
	@rm ./bin/*
