#子目录的Makefile直接读取其子目录就行
CFLAGS=-I ../Sock/ -I ../include -I ../Server_thread -I ../Cmd  -pthread 
# SUBDIRS=$(shell ls -l | grep ^d | awk '{print $$9}')
OBJS_DIR=$(shell pwd)/build
#以下同根目录下的makefile的相同代码的解释
CUR_SOURCE=${wildcard *.cpp}
CUR_OBJS=${patsubst %.cpp, %.o, $(CUR_SOURCE)}
all:$(SUBDIRS) MKDIR $(CUR_OBJS)
$(SUBDIRS):ECHO
	make -C $@
MKDIR:
	@mkdir -p build
$(CUR_OBJS):%.o:%.cpp
	$(CC) $(CFLAGS) -c $^ -o $(OBJS_DIR)/$@
	@cp -rfp $(OBJS_DIR)/*.o $(BUILD_DIR)
ECHO:
	@echo $(SUBDIRS)
clean:
	@rm build/* 