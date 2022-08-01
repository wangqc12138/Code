#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
#define bit(x,i)(((x)>>(i))&1)
using ll=long long;
using pii=pair<int,int>;
void solve(){
    string target;
    int n;
    cin>>target>>n;
    // vector<int> temp(target.size());
    set<pii> st;
    map<pii,int> mp;
    for(int i=0;i<n;i++){
        string x;
        cin>>x;
        int k=target.find(x);
        while(k>=0){
            st.emplace(k,k+x.size());
            mp[pii(k,k+x.size())]=i;
            k=target.find(x,k+x.size());
        }
    }
    vector<pii> temp(st.begin(),st.end());
    int a=temp[0].first,b=temp[0].second;
    for(int i=1;i<temp.size();i++){
        if()
    }
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    int tt;cin>>tt;for(int i=0;i<tt;i++){solve();}
    return 0;
}
