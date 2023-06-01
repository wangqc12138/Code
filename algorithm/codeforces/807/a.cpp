#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    int n,x;
    cin>>n>>x;
    int arr[2*n];
    for(int i=0;i<2*n;i++){
        cin>>arr[i];
    }
    sort(arr,arr+2*n);
    for(int i=0;i<n;i++){
        if(arr[i]+x>arr[n+i]){
            cout<<"no\n";
        }
    }
    cout<<"yes\n";
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    int tt;cin>>tt;for(int i=0;i<tt;i++){solve();}
    return 0;
}
