#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
#define bit(x,i)(((x)>>(i))&1)
using ll=long long;
using pii=pair<int,int>;
void solve(){
    int n,sh,sm;
    cin>>n>>sh>>sm;
    int target=sh*60+sm;
    set<int> st; 
    for(int i=0;i<n;i++){
        int x,y;
        cin>>x>>y;
        st.emplace(x*60+y);
    }
    if(st.count(target)){
        cout<<0<<0<<endl;
        return;
    }
    if(target>*st.end()){
        int t=*st.begin()+24*60-target;
        cout<<t/60<<" "<<t%60<<endl;
        return;
    }
    int t;
    for(auto i:st){
        if(i>target){
            break;
        }else{
            t=i-target;
        }
    }
    cout<<t/60<<" "<<t%60<<endl;
    return;
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    int tt;cin>>tt;for(int i=0;i<tt;i++){solve();}
    return 0;
}
