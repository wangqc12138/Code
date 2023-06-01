#include <bits/stdc++.h>
using namespace std;
int win(string str,int k){
    int L=0,R=0,n=str.size();
    int res=INT_MAX,w=0;
    while(R-L<k){
        w+=str[R++]=='W';
    }
    res=min(res,w);
    if(res==0){return 0;}
    while(R<n){
        w+=str[R++]=='W';
        w-=str[L++]=='W';
        res=min(res,w);
        if(res==0){return 0;}
    }
    return res;
}
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        int n,k;
        cin>>n>>k;
        string str;
        cin>>str;
        cout<<win(str,k)<<endl;;
    }
}