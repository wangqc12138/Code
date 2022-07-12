#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    int n;
    cin>>n;
    vector<int> arr;
    long long ans=0;
    for(int i=0;i<n;i++){
        int j;
        cin>>j;
        if(j<i+1){
            int t=lower_bound(arr.begin(),arr.end(),j)-arr.begin();
            ans+=t;
            arr.emplace_back(i+1);
            cout<<i+1<<" ";
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
