#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
#define bit(x,i)(((x)>>(i))&1)
using ll=long long;
using pii=pair<int,int>;
void solve(){
    int m,n;
    cin>>n>>m;
    map<int,set<int>> ms;
    int u,v;
    for(int i=0;i<m;i++){
        cin>>u>>v;
        ms[u].emplace(v);
        ms[v].emplace(u);
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(!ms[i].count(j)){
                continue;
            }
            for(int k=j+1;k<=n;k++){
                if(!ms[j].count(k)||!ms[i].count(k)){
                    continue;
                }
                ans++;
            }
        }
    }
    cout<<ans<<endl;;
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    solve();
    return 0;
}
