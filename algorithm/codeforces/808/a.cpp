#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    for(int i=1;i<n;i++){
        if(arr[i]%arr[i-1]==0){
            arr[i]=arr[i-1];
        }else{
            cout<<"no\n";
            return;
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
