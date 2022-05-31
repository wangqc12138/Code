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
map<string,vector<file>> mpfile;
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
            mpfile[temp].emplace_back(new file(dp->d_name,dir));
		}
		//目录
		if(dp->d_type==4){
            root->childfile.emplace_back(dp->d_name);
            node *chdir=new node(temp);
			root->childdir.emplace_back(chdir);
            dfs(chdir,temp);
		}
        
	}
    return 0;
}
int printTree();
int main(){
    string dir="./test";
    node *root=new node(dir);
    if(dfs(root,dir) == 0){
        //bfs(root);
    }
    return 0;
}

