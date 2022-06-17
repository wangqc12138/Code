#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        int a,b;
        cin>>a>>b;
        string ans;
        if(a>b){
            for(int i=0;i<b;i++){
                ans+="01";
            }
            for(int i=b;i<a;i++){
                ans+="0";
            }
        }else{
            for(int i=0;i<a;i++){
                ans+="10";
            }
            for(int i=a;i<b;i++){
                ans+="1";
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}