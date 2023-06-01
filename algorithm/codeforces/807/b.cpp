#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    int n;
    cin>>n;
    int arr[n];
    queue<int> next;
    int b=-1,z=0,sum=0;
    for(int i=0;i<n;i++){
        cin>>arr[i];
        if(arr[i]!=0&&b==-1){
            b=i;
        }
        if(arr[i]==0&&b!=-1){
            next.emplace(i);
        }
    }
    int ans=0;
    for(int i=b;i<n-1;i++){
        if(next.empty()){
            ans+=arr[i];
        }else{
            int k=next.front();
            arr[k]+=arr[i];
            ans+=arr[i];
            next.pop();
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
