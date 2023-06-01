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
    long long odd=0,even=0;
    for(int i=1;i<n-1;i++){
        if(arr[i]<=arr[i-1]){
            if(i%2){
                odd+=arr[i-1]+1-arr[i];
            }else{
                even+=arr[i-1]+1-arr[i];
            }
        }  
        if(arr[i]<=arr[i+1]){
            if(i%2){
                odd+=arr[i-1]+1-arr[i];
            }else{
                even+=arr[i-1]+1-arr[i];
            }
        }
    }
    if(n%2||odd>even){
        cout<<odd<<endl;
    }else{
        cout<<even<<endl;
    }
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    int tt;cin>>tt;for(int i=0;i<tt;i++){solve();}
    return 0;
}
