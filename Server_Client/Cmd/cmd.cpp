#include "cmd.h"
int cd(const char* dir){
	int ret=chdir(dir);
	printf("change %s\n",dir);
	if(-1==ret){
		char buf[BUFSIZ];
		snprintf(buf,BUFSIZ,"change %s error!",dir);
		perror(buf);
	}
	return 0;
}
int ls(char* buf){
	int n=0;
	struct dirent *rent;//struct
	DIR *dir=opendir(".");
	//利用dirent中的readdir来获取文件
	while(rent=readdir(dir)){
		if(rent->d_name[0]!='.'){
			strcpy(buf+n,rent->d_name);
			n+=strlen(rent->d_name);
			strcpy(buf+n,"\n");
			n+=strlen("\n");
		}
	}
	return n;
}
int pwd(char* buf){
	getcwd(buf,BUFSIZ);
	int n=strlen(buf);
	strcpy(buf+n,"\n");
	return n+1;
}
int cmd(const char* buf_in,char* buf_out){
	if (!strncmp(buf_in,"ls",strlen(buf_in))){
		ls(buf_out);
	}
	if (!strncmp(buf_in,"pwd",strlen(buf_in))){
		pwd(buf_out);
	}
	if (!strncmp(buf_in,"cd ",3)){
		char target[256];
        bzero(target,sizeof(target));
		memcpy(target,buf_in+3,strlen(buf_in)-3);
		cd(target);
	}
	return 0;
}