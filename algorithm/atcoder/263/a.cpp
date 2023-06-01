#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
#define bit(x,i)(((x)>>(i))&1)
using ll=long long;
using pii=pair<int,int>;
void solve(){
    map<int,int> mp;
    for(int i=0;i<5;i++){
        int x;
        cin>>x;
        mp[x]++;
    }
    if(mp.size()!=2){
        cout<<"no\n";
        return;
    }
    for(auto [i,j]:mp){
        if(j!=2&&j!=3){
            cout<<"no\n";
            return;
        }
    }
    cout<<"yes\n";
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    solve();
    return 0;
}
