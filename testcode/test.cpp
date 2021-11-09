#include <iostream>
#include <stdarg.h>
#include <unordered_set>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
using namespace std;
class A{
	int val;
};
int getfilenum(const string& dir,int iThreshold){
	queue<string> qDir;
	qDir.emplace(dir);
	DIR *dDir;
	struct dirent *dp;
	int iFileNum=0;
	while(!qDir.empty()){
		string wd=qDir.front();
		qDir.pop();
		if ((dDir = opendir (wd.c_str ())) == NULL) {
			printf("open dir %s error!\n",wd.c_str());
			return -1;
		}
		while((dp = readdir (dDir))){
			if (strcmp (dp->d_name, ".") == 0 || strcmp (dp->d_name, "..") == 0 ) {
				continue;
			}
			if( iFileNum >= iThreshold ){
				closedir (dDir);
				return iThreshold;
			}
			//文件
			if(dp->d_type==8){
				cout<<wd+"/"+dp->d_name<<endl;
				iFileNum++;
			}
			//目录
			if(dp->d_type==4){
				qDir.emplace(wd+"/"+dp->d_name);
			}
		}
	}
	closedir (dDir);
	return iFileNum;
}
static map<int,int> mmp;
int main(){
	//string dir="/home/wangqc/wqc_code/CppPracticeCode";
	//cout<<getfilenum(dir.c_str(),1000)<<endl;
	mmp[0]=1;
	for(int i=0;i<10000;i++){
		mmp.clear();
	}
	mmp.clear();
	mmp.clear();
	auto itr=mmp.begin();
	for(;itr!=mmp.end();itr++){
		cout<<"111"<<endl;
	}
	cout<<"end"<<endl;
	return 0;
}