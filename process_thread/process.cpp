#include "common.h"
using namespace std;
int main(){
	pid_t pid=fork();
	if(pid<0){//error
		perror("process create error!\n");
	}else if(pid==0){//child
		printf("my pid is %d,my parent's pid is %d\n",getpid(),getppid());
	}else{//parent
		printf("my pid is %d\n",getpid());
		sleep(1);
	}
	return 0;
}