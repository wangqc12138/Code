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
    if(*min_element(vec.begin(),vec.end())>=max(l,r)){
        cout<<ans<<endl;return;
    }
    if(l>r){
        reverse(vec.begin(),vec.end());
    }
    int L,R;
    ll t=ans;
    for(int i=1;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(sum[j]-sum[i-1]<=min(l,r)*(j-i+1)){
                if(sum[j]-sum[i-1]<t){
                    L=i;
                    R=j;
                    t=sum[j]-sum[i-1];
                }
            }else{
                i=j+1;
                break;
            }
        }
    }
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(j<=i){
                continue;
            }
            ll temp=sum[j-1]-sum[i];
            temp+=ll(i+1)*l+ll(n-j)*r;
            if(ans>temp){
                i=j+1;
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
