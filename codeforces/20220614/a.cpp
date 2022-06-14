#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        int ans=0;
        if(b>a){
            ans++;
        }
        if(c>a){
            ans++;
        }
        if(d>a){
            ans++;
        }
        cout<<ans<<endl;
    }
    return 0;
}