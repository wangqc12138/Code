#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    int n,a,b,m=INT_MAX,ans=INT_MIN;
    cin>>n>>a>>b;
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
        m=min(m,arr[i]);
    }
    for(int i=0;i<n;i++){
        ans=max(ans,arr[i]-((arr[i]-m)/(a+b)*b));
    }
    cout<<ans<<endl;
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    //freopen("./test.txt","r",stdin);
    solve();
    return 0;
}
