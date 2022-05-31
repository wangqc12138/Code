#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int M;
    cin>>M;
    while(M--){
        int m,n;
        cin>>m>>n;
        string str;
        cin>>str;
        int len=str.size();
        int p=str.rfind('1');
        if(p==-1){
            cout<<0<<endl;
            continue;
        }
        if(len-1-p!=0&&len-1-p<=n){
            n-=len-1-p;
            str[len-1]='1';
            str[p]='0';
        }
        p=str.find('1');
        if(p!=0&&p!=len-1&&p<=n){
            n-=p;
            str[0]='1';
            str[p]='0';
        }
        int ans=0;
        for(int i=0;i<len-1;i++){
            ans+=stoi(str.substr(i,2));
        }
        cout<<ans<<endl;
    }
    return 0;
}
