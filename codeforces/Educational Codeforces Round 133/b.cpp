#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
#define bit(x,i)(((x)>>(i))&1)
#define no {puts("No") ; return ;}
#define yes {puts("Yes") ; return ;}
using ll=long long;
using pii=pair<int,int>;
void solve(){
    int n;
    cin>>n;
    vector<int> vec(n);
    iota(vec.begin(),vec.end(),1);
    for(auto j:vec){
        cout<<j<<" ";
    }
    cout<<endl;
    for(int i=0;i<n-1;i++){
        int t=vec[i];
        vec[i]=vec[i+1];
        vec[i+1]=t;
        for(auto j:vec){
            cout<<j<<" ";
        }
        cout<<endl;
    }
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    int tt;cin>>tt;for(int i=0;i<tt;i++){solve();}
    return 0;
}
