#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
#define bit(x,i)(((x)>>(i))&1)
using ll=long long;
using pii=pair<int,int>;
void solve(){
    int n,k=0,ans=0;
    map<int,int> mp;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        if(x==i){
            k++;
        }else if(mp.count(x)&&mp[x]==i){
            ans++;
        }
    }
    ans+=k*(k-1)/2;
    cout<<ans<<endl;
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    solve();
    return 0;
}
