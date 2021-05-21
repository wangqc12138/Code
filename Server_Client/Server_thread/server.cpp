#include "server.h"
void C_SERVER::init(string strIp,int iPort){
    m_strIp=strIp;
	m_iPort=iPort;
	printf("this is server by thred\n");
}
/* void* work(void* arg){
	pthread_detach(pthread_self());
	intptr_t c_fd=(intptr_t)arg;
	char send_buf[BUFSIZ],recv_buf[BUFSIZ];
	while(1){
		bzero(send_buf,strlen(send_buf));
		bzero(recv_buf,strlen(recv_buf));
		int n=Read(c_fd,recv_buf,sizeof(recv_buf));
		if(n==0){
			Close(c_fd);
			break;
		}else{
			memcpy(send_buf,recv_buf,strlen(recv_buf));
			if(recv_buf[n-1]=='\n'){
				recv_buf[n-1]=0;
			}
			cmd(recv_buf,send_buf);
			write(c_fd,send_buf,strlen(send_buf));
		}
	}
	return nullptr;
}  
void C_SERVER::run(){
	char buf[BUFSIZ];
	pthread_t tid;
	m_sock.Listen(m_strIp,m_iPort);
	while(1){
		intptr_t c_fd=m_sock.Accept();
		pthread_create(&tid,NULL,&work,(void*)c_fd);
	}
} */
void work(int c_fd){
	char send_buf[BUFSIZ],recv_buf[BUFSIZ];
	while(1){
		bzero(send_buf,strlen(send_buf));
		bzero(recv_buf,strlen(recv_buf));
		int n=Read(c_fd,recv_buf,sizeof(recv_buf));
		if(n==0){
			Close(c_fd);
			break;
		}else{
			memcpy(send_buf,recv_buf,strlen(recv_buf));
			if(recv_buf[n-1]=='\n'){
				recv_buf[n-1]=0;
			}
			cmd(recv_buf,send_buf);
			write(c_fd,send_buf,strlen(send_buf));
		}
	}
}
void* thread_run(void *arg) {
    pthread_t tid=pthread_self();
    pthread_detach(tid);
    thread_queue *tq=(thread_queue *) arg;
    while (1) {
        int c_fd=tq->pop();
        printf("get fd in thread, fd==%d, tid==%d",c_fd,(int)tid);
        work(c_fd);
    }
}

void C_SERVER::run(){
	char buf[BUFSIZ];
	vector<pthread_t> t_set(10);
	m_sock.Listen(m_strIp,m_iPort);
	for(auto tid:t_set){
		pthread_create(&tid,NULL,&thread_run,(void *)&m_tqueue);
	}
	while(1){
		int c_fd=m_sock.Accept();
		m_tqueue.push(c_fd);
	}
}
void C_SERVER::stop(){
	Close(m_sock.m_iHandle);
}