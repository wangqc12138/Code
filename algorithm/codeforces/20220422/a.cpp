#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
bool help(string& str){
    char c=str[0];
    int len=1;
    for(int i=1;i<str.size();i++){
        if(str[i]!=c){
            if(len==1){
                return false;
            }
            c=str[i];
            len=1;
        }else{
            len++;
        }
    }
    return len>1;
}
int main(){
    freopen("./test.txt","r",stdin);
    int m;
    cin>>m;
    for(int i=0;i<m;i++){
        string str;
        cin>>str;
        if(help(str)){
            cout<<"YES"<<endl;
        }else{
            cout<<"NO"<<endl;
        }
    }
    return 0;
}