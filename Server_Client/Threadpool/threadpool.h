#ifndef THREAD_QUEUE_H
#define THREAD_QUEUE_H
#include "common.h"
class thread_queue
{
private:
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	int size;
	int front;
	int back;
	vector<int> fd;
public:
	thread_queue(int num=10);
	// thread_queue();
	~thread_queue();
	int push(int c_fd);
	int pop();
};
#endif