#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        string str;
        cin>>str;
        int zero=str.find('0');
        int one=str.rfind('1');
        if(zero<0&&one<0){
            cout<<str.size()<<endl;
        }else if(zero<0){
            cout<<str.size()-one<<endl;
        }else if(one<0){
            cout<<zero+1<<endl;
        }else if(zero<one){
            cout<<"2"<<endl;
        }else{
            cout<<zero-one+1<<endl;
        }
    }
    return 0;
}
