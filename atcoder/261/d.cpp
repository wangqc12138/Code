#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    int n,m;
    cin>>n>>m;
    int arr[n];
    int ext[n+1];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    for(int i=1;i<=m;i++){
        int t;
        cin>>t;
        cin>>ext[t];
    }
    int dp[n][n+1];
    dp[0][0]=0,dp[0][1]=arr[0];
    int ans=arr[0];
    for(int i=1;i<n;i++){
        dp[i][0]=ans;
        for(int j=1;j<=i+1;j++){
            dp[i][j]=dp[i-1][j-1]+ext[j]+arr[i];
            ans=max(ans,dp[i][j]);
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
