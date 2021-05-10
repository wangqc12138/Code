#子目录的Makefile直接读取其子目录就行
CFLAGS=-I ../Sock/ -I ../include -I ../Server
#以下同根目录下的makefile的相同代码的解释
CUR_SOURCE=${wildcard *.cpp}
CUR_OBJS=${patsubst %.cpp, %.o, $(CUR_SOURCE)}
all:$(CUR_OBJS) $(ROOT_DIR)/$(BIN_DIR)/$(BIN)
$(CUR_OBJS):%.o:%.cpp
	$(CC) $(CFLAGS) -c $^ -o $(ROOT_DIR)/$(OBJS_DIR)/$@
OBJS=*.o
ODIR=build
$(ROOT_DIR)/$(BIN_DIR)/$(BIN):$(ODIR)/$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^