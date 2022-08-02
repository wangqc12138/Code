#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
#define bit(x,i)(((x)>>(i))&1)
using ll=long long;
using pii=pair<int,int>;
void solve(){
    int n,x;
    cin>>n>>x;
    vector<pii> vp;
    for(int i=0;i<n;i++){
        int k;
        cin>>k;
        vp.emplace_back(k-x,k+x);
    }
    pii tp=vp[0];
    int ans=0;
    for(int i=1;i<n;i++){
        if(vp[i].second<tp.first||vp[i].first>tp.second){
            ans++;
            tp=vp[i];
        }else{
            tp.first=max(tp.first,vp[i].first);
            tp.second=min(tp.second,vp[i].second);
        }
    }
    cout<<ans<<endl;
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    int tt;cin>>tt;for(int i=0;i<tt;i++){solve();}
    return 0;
}
