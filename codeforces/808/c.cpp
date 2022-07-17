#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    int n,q;
    cin>>n>>q;
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    string ans;
    for(int i=0;i<n;i++){
        if(arr[i]>q&&n-i+1<=q){
            q--;
            ans+='1';
        }else if(arr[i]<=q){
            ans+='1';
        }else{
            ans+='0';
        }
    }
    for(int i=n-1;i>=0&&q;i--){
        if(ans[i]=='0'){
            ans[i]='1';
            q--;
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
