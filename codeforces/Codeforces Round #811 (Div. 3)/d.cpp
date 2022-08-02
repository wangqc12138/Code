#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
#define bit(x,i)(((x)>>(i))&1)
using ll=long long;
using pii=pair<int,int>;
void solve(){
    string target="";
    int n;
    cin>>target>>n;
    // vector<int> temp(target.size());
    vector<pii> vec;
    map<pii,int> mp;
    for(int i=1;i<=n;i++){
        string x;
        cin>>x;
        int k=target.find(x);
        while(k>=0){
            vec.emplace_back(k,k+x.size()-1);
            mp[pii(k,k+x.size()-1)]=i;
            k=target.find(x,k+1);
        }
    }
    auto cmp=[](pii a,pii b){return a.first<b.first||a.first==b.first&&a.second>b.second;};
    sort(vec.begin(),vec.end(),cmp);
    int r=-1,i=0,len=vec.size(),R=target.size()-1;
    vector<pii> ans;
    while(r<R&&i<len){
        if(vec[i].first>r+1){
            break;
        }
        int m=r;
        pii temp;
        while(i<len&&vec[i].first<=r+1){
            if(m<vec[i].second){
                temp.first=mp[vec[i]];
                temp.second=vec[i].first+1;
                m=vec[i].second;
            }
            i++;
        }
        ans.emplace_back(temp);
        r=m;
    }
    if(r<R){
        cout<<-1<<endl;return;
    }
    cout<<ans.size()<<endl;
    for(auto [x,y]:ans){
        cout<<x<<" "<<y<<endl;
    }
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    int tt;cin>>tt;for(int i=0;i<tt;i++){solve();}
    return 0;
}
