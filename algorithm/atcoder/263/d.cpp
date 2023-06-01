#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
#define bit(x,i)(((x)>>(i))&1)
using ll=long long;
using pii=pair<int,int>;
void solve(){
    int n,l,r;
    cin>>n>>l>>r;
    vector<int> vec(n);
    vector<ll> sum(n);
    for(int i=0;i<n;i++){
        cin>>vec[i];
        if(i==0){
            sum[i]=vec[i];
        }else{
            sum[i]=sum[i-1]+vec[i];
        }
    }
    ll ans=sum[n-1];
    int k=min(l,r);
    if(ans>(ll)k*n){
        ans=(ll)k*n;
    }
    for(int i=0;i<n-1;i++){
        for(int j=1;j<n;j++){
            if(j<=i){
                continue;
            }
            ll temp=sum[j-1]-sum[i];
            temp+=ll(i+1)*l+ll(n-j)*r;
            if(ans>temp){
                ans=temp;
            }
        }
    }
    cout<<ans<<endl;
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    solve();
    return 0;
}
