#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
#define bit(x,i)(((x)>>(i))&1)
using ll=long long;
using pii=pair<int,int>;
void solve(){
    int n;
    cin>>n;
    map<int,int> mp;
    mp[1]=0;
    for(int i=2;i<=n;i++){
        int x;
        cin>>x;
        mp[i]=mp[x]+1;
    }
    cout<<mp[n]<<endl;
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    solve();
    return 0;
}
