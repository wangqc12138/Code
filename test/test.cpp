#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>
using namespace std;
char* getString(){
    char* res=getenv("AAA");
    return res;
}
int main(){
    //freopen("./test.txt","r",stdin);
    char path[108];
    strcpy(path,"aaa/bbb/ccc/12345");
    string str=path;
    int port=stoi(str.substr(str.rfind('/')+1));
    //sscanf(path,"aaa/bbb/ccc/%d",&port);
    char buf[255];
	snprintf(buf,sizeof(buf),"%d",123545);
    string s= (string)getString()+buf;
    cout<<s<<endl;
    return 0;
}
