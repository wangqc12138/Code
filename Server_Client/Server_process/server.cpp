#include "server.h"
void C_SERVER::init(string strIp,int iPort){
    m_strIp=strIp;
	m_iPort=iPort;
	printf("this is server by process\n");
}
void sigchld_handler(int sig){
    while(waitpid(-1,0,WNOHANG)>0);
    return;
}
int C_SERVER::work(int child_fd){
	char send_buf[BUFSIZ],recv_buf[BUFSIZ];
	while(1){
		bzero(send_buf,strlen(send_buf));
		bzero(recv_buf,strlen(recv_buf));
		int n=Read(child_fd,recv_buf,sizeof(recv_buf));
		if(n==0){
			Close(child_fd);
			return -1;
		}else{
			memcpy(send_buf,recv_buf,strlen(recv_buf));
			if(recv_buf[n-1]=='\n'){
				recv_buf[n-1]=0;
			}
			cmd(recv_buf,send_buf);
			write(child_fd,send_buf,strlen(send_buf));
		}
	}
	return 0;
}
void do_sigchild(int num)
{
	while (waitpid(0, NULL, WNOHANG) > 0)
		;
}

void C_SERVER::run(){
	signal(SIGCHLD,sigchld_handler);
	// struct sigaction newact;
	// newact.sa_handler = do_sigchild;
	// sigemptyset(&newact.sa_mask);
	// newact.sa_flags = 0;
	// sigaction(SIGCHLD, &newact, NULL);

	m_sock.Listen(m_strIp,m_iPort);
	while(1){
		int c_fd=m_sock.Accept();
		int pid=fork();
		if(pid<0){
			perror("fork error!");
		}else if(pid==0){//子进程
			Close(m_sock.m_iHandle);
			if(-1==work(c_fd)){
				printf("cilent close!\n");
			}
			exit(0);
		}else if(pid>0){//父进程
			Close(c_fd);
		}
	}
}

void C_SERVER::stop(){
	Close(m_sock.m_iHandle);
}