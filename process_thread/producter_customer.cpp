#include "common.h"
using namespace std;
void* customer(void* arg);
void* producter(void* arg);
queue<int> dataqueue;
int main(){
	//int pthread_create(pthread_t *thread, const pthread_attr_t *attr,void *(*start_routine) (void *), void *arg);
	vector<pthread_t> c_tid(3);
	pthread_t ctid,ptid;
	for(int i=0;i<3;i++){
		if(0!=pthread_create(&c_tid[i],NULL,customer,NULL)){
			perror("thread create error!\n");
		}
	}
	if(0!=pthread_create(&ptid,NULL,producter,NULL)){
		perror("thread create error!\n");
	}
	for(int i=0;i<3;i++){
		pthread_join(c_tid[i],nullptr);
	}
	pthread_join(ptid,nullptr);
	return 0;
}
//customers
void* customer(void* arg){
	while(1){
		if(!dataqueue.empty()){
			printf("custom data is %d\n",dataqueue.front());
			dataqueue.pop();
		}
	}
	return NULL;
}
//producters
void* producter(void* arg){
	while(1){
		srand(time(0));
		int k=rand()%100;
		printf("product data is %d\n",k);
		dataqueue.emplace(k);
	}
	return NULL;
}