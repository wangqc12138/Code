#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        int m,n;
        cin>>m>>n;
        long long ans=0;
        for(int i=1;i<=n;i++){
            ans+=i;
        }
        for(int i=2*n;i<=m*n;i+=n){
            ans+=i;
        }
        cout<<ans<<endl;;
    }
    return 0;
}