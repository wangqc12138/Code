#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    int m;
    cin>>m;
    unordered_set<string> ust;
    vector<string> vstr(m);
    for(int i=0;i<m;i++){
        cin>>vstr[i];
        ust.emplace(vstr[i]);
    } 
    string ans;
    for(int i=0;i<m;i++){
        string str=vstr[i];
        bool flag=false;
        for(int j=1;j<str.size();j++){
            //cout<<str.substr(0,j)<<" "<<str.substr(j)<<endl;
            if(ust.count(str.substr(0,j))&&ust.count(str.substr(j))){
                flag=true;
                break;
            }
        }
        if(flag){
            ans+='1';
        }else{
            ans+='0';
        }
    }
    cout<<ans<<endl;;
    
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    int tt;cin>>tt;for(int i=0;i<tt;i++){solve();}
    return 0;
}
