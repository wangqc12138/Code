#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
#define bit(x,i)(((x)>>(i))&1)
using ll=long long;
using pii=pair<int,int>;
int solve(){
    int n,c;
    cin>>n>>c;
    vector<pii> vp(n);
    for(int i=0;i<n;i++){
        cin>>vp[i].first>>vp[i].second;
    }
    for(int i=0;i<32;i++){
        int k=bit(c,i);
        for(int j=0;j<n;j++){
            int x=bit(vp[i].second,i);
            if(vp[i].first==1){
                
            }else if(vp[i].first==2){

            }else{

            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    solve();
    return 0;
}
