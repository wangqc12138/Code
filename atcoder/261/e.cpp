#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    int n,c;
    cin>>n>>c;
    int ans[n+1];
    ans[0]=c;
    for(int i=1;i<=n;i++){
        int k,t;
        cin>>k>>t;
        if(k==1){
            ans[i]=ans[i-1]&t;
        }else if(k==2){
            ans[i]=ans[i-1]|t;
        }else{
            ans[i]=ans[i-1]^t;
        }
        cout<<ans[i]<<endl;
    }
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    solve();
    return 0;
}
