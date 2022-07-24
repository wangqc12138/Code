#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    int n;
    cin>>n;
    vector<string> vstr(n);
    vector<int> result(n,0);
    map<string,int> mp;
    for(int i=0;i<n;i++){
        cin>>vstr[i];
        result[i]=mp[vstr[i]]++;
    }
    for(int i=0;i<n;i++){
        cout<<vstr[i];
        if(result[i]!=0){
            cout<<"("<<result[i]<<")\n";
        }else{
            cout<<"\n";
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
