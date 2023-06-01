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
    vector<int> arr(m);
    for(int i=0;i<m;i++){
        cin>>arr[i];
    }
    set<int> st;
    for(int i=1;i<m;i++){
        st.emplace(arr[i]-arr[i-1]);
    }
    st.emplace(arr[0]-1+n-arr[m-1]);
    int k=0,ans=0;
    for(auto i:st){
        if(i-k*2-1>0){
            ans+=i-k*2-1;
            k++;
        }else{
            continue;
        }
    }
    cout<<n-ans<<endl;
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    int tt;cin>>tt;for(int i=0;i<tt;i++){solve();}
    return 0;
}
