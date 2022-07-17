#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    int n;
    cin>>n;
    int m=2*n;
    cout<<m<<endl;
    string ans="";
    for(int i=0;i<n/4&&n;i++){
        if(n>=4){
            ans+='4';
            n-=4;
        }else{
            ans+=n+'0';
            n=0;
        }
    }
    reverse(ans.begin(),ans.end());
    cout<<ans<<endl;
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    solve();
    return 0;
}
