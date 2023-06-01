#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    int n,m,t;
    cin>>n>>m;
    int arr[n],ext[n+1],dp[n][n+1];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    for(int i=1;i<=m;i++){
        cin>>t>>ext[t];
    }
    memset(dp,0,sizeof(dp));
    for(int i=0;i<n;i++){
        for(int j=1;j<=i;j++){
            dp[i][j]=dp[i-1][j-1]+ext[j]+arr[i];
        }
        for(int j=0;j<i;j++){
            dp[i][0]=max(dp[i][0],dp[i-1][j]);
        }
    }
    cout<<*max_element(dp[n],dp[n]+n+1)<<endl;
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    solve();
    return 0;
}
