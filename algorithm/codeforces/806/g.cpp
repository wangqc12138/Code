#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    int n,k,m;
    cin>>n>>k;
    long long dp[n][n];
    memset(dp,0,sizeof(dp));
    long long ans=0;
    for(int i=0;i<n;i++){
        cin>>m;
        if(i==0){
            dp[0][0]=m-k;
            dp[0][1]=m/2;
            ans=max(m-k,m/2);
            continue;
        }
        for(int j=0;j<=i;j++){
            if(j==0){
                dp[i][j]=dp[i-1][j]+m-k;
            }
            for(int t=0;t<=j;t++){
                if(dp[i-1][t]+m/pow(2,t)>dp[i][j]){
                    dp[i][j]=dp[i-1][t]+m/pow(2,t);
                }
            }
            ans=max(dp[i][j],ans);
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
