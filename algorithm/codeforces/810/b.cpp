#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    int n,k;
    cin>>n;
    map<int,vector<int>> mp;
    map<int,int> ans,pre;
    for(int i=0;i<n;i++){
        cin>>k;
        if(pre.count(k)){
            if((i-pre[k])%2){
                ans[k]++;
            }
        }else{
            ans[k]=1;
        }
        pre[k]=i;        
    }
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<" ";
    }
    cout<<endl;
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    int tt;cin>>tt;for(int i=0;i<tt;i++){solve();}
    return 0;
}
