#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    int a,b,c,d;
    cin>>a>>b>>c>>d;
    int arr[101];
    memset(arr,0,sizeof(arr));
    for(int i=a;i<=b;i++){
        arr[i]++;
    }
    for(int i=c;i<=d;i++){
        arr[i]++;
    }
    int ans=0;
    for(int i=0;i<=100;i++){
        if(arr[i]==2){
            ans++;
        }
    }
    cout<<max(0,ans-1)<<endl;
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    solve();
    return 0;
}
