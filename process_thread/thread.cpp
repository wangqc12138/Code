#include "common.h"
using namespace std;
void* customer(void* arg);
int main(){
	//int pthread_create(pthread_t *thread, const pthread_attr_t *attr,void *(*start_routine) (void *), void *arg);
	pthread_t tid;
	if(0!=pthread_create(&tid,NULL,customer,NULL)){
		perror("thread create error!\n");
	}
	pthread_join(tid,nullptr);
	return 0;
}
//customers
void* customer(void* arg){
	printf("i'm child thread,my tid is %ld\n",pthread_self());
	return NULL;
}
//producters
void* producter(void* arg){
	return NULL;
}