#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
#define bit(x,i)(((x)>>(i))&1)
using ll=long long;
using pii=pair<int,int>;
void solve(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m-n+1;i++){
        vector<int> arr;
        arr.emplace_back(i);
        while(arr.size()<n){
            for(int k=2;k<=m;k++){
                if(arr.back()<k){
                    arr.emplace_back(k);break;
                }
            }
        }
        if(arr.size()==n){
            for(auto i:arr){
                cout<<i<<" ";
            }
            cout<<endl;
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    solve();
    return 0;
}
