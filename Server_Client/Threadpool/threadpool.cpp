#include "threadpool.h"
// thread_queue::thread_queue(){
// 	this->size=10;
//     this->fd=vector<int>(10,-1);
//     this->front=0;
// 	this->back=0;
//     pthread_mutex_init(&this->mutex, NULL);
//     pthread_cond_init(&this->cond, NULL);
// }
thread_queue::thread_queue(int num){
	this->size=num;
    this->fd=vector<int>(num,-1);
    this->front=0;
	this->back=0;
    pthread_mutex_init(&this->mutex, NULL);
    pthread_cond_init(&this->cond, NULL);
}
thread_queue::~thread_queue(){
	this->fd.clear();
	pthread_mutex_destroy(&this->mutex);
	pthread_cond_destroy(&this->cond);
}
int thread_queue::push(int c_fd){
	pthread_mutex_lock(&this->mutex);
	if((this->back+1)%this->size==this->front){
		printf("thread_queue is full!\n");
		return -1;
	}
    this->fd[this->back++]=c_fd;
    this->back%=this->size;
    printf("push fd %d\n",c_fd);
    pthread_cond_signal(&this->cond);
    pthread_mutex_unlock(&this->mutex);
	return 0;
}
int thread_queue::pop(){
	pthread_mutex_lock(&this->mutex);
    while (this->front==this->back){
		pthread_cond_wait(&this->cond,&this->mutex);
	}  
    int c_fd=this->fd[this->front++];
    this->front%=this->size;
    printf("pop fd %d\n",c_fd);
    pthread_mutex_unlock(&this->mutex);
    return c_fd;
}