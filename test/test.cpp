#include <bits/stdc++.h>
#include <sys/types.h> 
#include <dirent.h>
using namespace std;
class file{
public:
    file(string name,string dir,int size=0):name(name),dir(dir),size(size){};
    string name;
    string dir;
    int size;
};
class node{
public:
    node(string name){
        this->name=name;
        this->childdir.clear();
        this->childfile.clear();
    }
    string name;
    vector<node*> childdir;
    vector<string> childfile;
};
map<string,file*> mpfile;
set<string> visit;
int dfs(node* root,string dir){
    DIR *dDir;
	struct dirent *dp;
    if ((dDir = opendir (dir.c_str ())) == NULL) {
		return -1;
	}
	while((dp = readdir (dDir))){
		if (strcmp (dp->d_name, ".") == 0 || strcmp (dp->d_name, "..") == 0 ) {
			continue;
		}
		string temp=dir+"/"+dp->d_name;
        //文件
		if(dp->d_type==8){
			root->childfile.emplace_back(temp);
            mpfile[temp]=new file(dp->d_name,dir,0);
		}
		//目录
		if(dp->d_type==4){
            node *chdir=new node(temp);
			root->childdir.emplace_back(chdir);
            mpfile[temp]=new file(dp->d_name,dir,0);
            dfs(chdir,temp);
		}
        
	}
    return 0;
}
void printTree(node* root,int len=1){
    if(root==NULL){
        return;
    }
    printf("%*sd--%s\n",len,"-",mpfile[root->name]->name.c_str());
    for(auto chf:root->childfile){
        printf("%*sf--%s\n",len+2,"-",mpfile[chf]->name.c_str());
    }
    for(auto chd:root->childdir){
        printTree(chd,len+2);
    }
}
int main(){
    string dir="/home/wangqc/wangqichao/CppPracticeCode/test";
    mpfile["/home/wangqc/wangqichao/CppPracticeCode/test"]=new file("test",dir,0);
    node *root=new node(dir);
    if(dfs(root,dir) == 0){
        printTree(root);
    }
    return 0;
}

