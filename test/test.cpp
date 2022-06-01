#include <bits/stdc++.h>
#include <sys/types.h> 
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
using namespace std;
using ll=long long;
class fileinfo{
public:
    fileinfo(string name,string dir,time_t time,ll size=0,bool isfile=true):name(name),dir(dir),time(time),size(size),isfile(isfile){};
    string name;
    string dir;
    ll size;
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
int getFileSizeAndTime(string file,ll &size,time_t &time){
    struct stat *s;
    if(-1 == stat(file.c_str(),s)){
        return -1;
    }
    size = s->st_size;
    time = s->st_mtim.tv_sec;
    return 0;
}
ll dfs(node* root,string dir){
    cout<<dir<<endl;
    DIR *dDir;
	struct dirent *dp;
    if ((dDir = opendir (dir.c_str ())) == NULL) {
		return -1;
	}
    ll sumSize = 0;
	while((dp = readdir (dDir))){
		if (strcmp (dp->d_name, ".") == 0 || strcmp (dp->d_name, "..") == 0 ) {
			continue;
		}
		string temp=dir+"/"+dp->d_name;
        cout<<"  "<<temp<<endl;
		if(dp->d_type==8){
            node *chnode=new node(temp);
			root->child.emplace_back(chnode);
            ll size=0;
            time_t time=0;
            if(-1 == getFileSizeAndTime(temp,size,time)){
                return -1;
            }
            fileinfo *tf=new fileinfo(dp->d_name,dir,time,size);
            mpfile[temp]=tf;
            sumSize+=size;
		}
		if(dp->d_type==4){
            node *chnode=new node(temp);
			root->child.emplace_back(chnode);
            ll size=0;
            time_t time=0;
            if(-1 == getFileSizeAndTime(temp,size,time)){
                return -1;
            }
            size=dfs(chnode,temp);
            mpfile[temp]=new fileinfo(dp->d_name,dir,time,size,false);
            sumSize+=size;
		}
        
	}
    cout<<sumSize<<endl;
    return sumSize;
}
void printTree(node* root,int len=1){
    for(int i=0;i<len;i++){
        cout<<"-";
    }
    cout<<mpfile[root->name]->name<<endl;
    for(auto node:root->child){
        printTree(node,len+1);
    }
}
void getDirandFile(string dname,string &dir,string &file){
    if(dname.back()=='/'){
        dname.pop_back();
    }
    file=dname.substr(dname.rfind('/')+1);
    dir=dname.substr(0,dname.rfind('/')+1);
}
int main(){
    string Dname="/home/wangqc/CppPracticeCode/test";
    string dir,file;
    getDirandFile(Dname,dir,file);
    node *root=new node(Dname);
    ll size;
    time_t time=0;
    getFileSizeAndTime(Dname,size,time);
    size = dfs(root,Dname);
    cout<<size<<endl;
    mpfile[Dname]=new fileinfo(file,dir,time,size,false);
    printTree(root);
    return 0;
}

