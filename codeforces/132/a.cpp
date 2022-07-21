#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    int k;
    cin>>k;
    int arr[3];
    for(int i=0;i<3;i++){
        cin>>arr[i];
    }
    if(arr[k-1]==0){
        cout<<"no\n";return;
    }else{
        k=arr[k-1];
        if(arr[k-1]==0){
            cout<<"no\n";return;
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
