#include <bits/stdc++.h>
#include <sys/types.h> 
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
using namespace std;
class fileinfo{
public:
    fileinfo(string name,string dir,time_t time,int size=0,bool isfile=true):name(name),dir(dir),time(time),size(size),isfile(isfile){};
    string name;
    string dir;
    int size;
    time_t time;
    bool isfile;
};
class node{
public:
    node(string name){
        this->name=name;
        this->child.clear();
    }
    string name;
    vector<node*> child;
};
map<string,fileinfo*> mpfile;
set<string> visit;
int getFileSizeAndTime(string file,int &size,time_t &time){
    struct stat *s;
    if(-1 == stat(file.c_str(),s)){
        return -1;
    }
    size = s->st_size;
    time = s->st_mtim.tv_sec;
    return 0;
}
long long dfs(node* root,string dir){
    DIR *dDir;
	struct dirent *dp;
    if ((dDir = opendir (dir.c_str ())) == NULL) {
		return -1;
	}
    long long sumSize = 0;
	while((dp = readdir (dDir))){
		if (strcmp (dp->d_name, ".") == 0 || strcmp (dp->d_name, "..") == 0 ) {
			continue;
		}
		string temp=dir+"/"+dp->d_name;
		if(dp->d_type==8){
            node *chnode=new node(temp);
			root->child.emplace_back(chnode);
            int size=0;
            time_t time=0;
            if(-1 == getFileSizeAndTime(temp,size,time)){
                return -1;
            }
            mpfile[temp]=new fileinfo(dp->d_name,dir,time,size,true);
            sumSize+=size;
		}
		if(dp->d_type==4){
            node *chnode=new node(temp);
			root->child.emplace_back(chnode);
            int size=0;
            time_t time=0;
            if(-1 == getFileSizeAndTime(temp,size,time)){
                return -1;
            }
            size=dfs(chnode,temp);
            mpfile[temp]=new fileinfo(dp->d_name,dir,time,size,false);
            sumSize+=size;
		}
        
	}
    return sumSize;
}
void printTree(node* root,int len=1){

}
void getDirandFile(string &dir,string &file){
    if(dir.back()=='/'){
        dir.pop_back();
    }
    file=dir.substr(dir.rfind('/'));
    dir=dir.substr(0,dir.rfind('/')+1);
}
int main(){
    string dir="/home/wangqc/wangqichao/CppPracticeCode/test",file;
    getDirandFile(dir,file);
    node *root=new node(dir+file);
    long long size;
    time_t time=0; = dfs(root,dir);
    mpfile[dir]=new fileinfo(file,dir,size,);
    
    if(dfs(root,dir) == 0){
        printTree(root);
    }
    return 0;
}

