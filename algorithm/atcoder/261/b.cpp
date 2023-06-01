#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    int n;
    cin>>n;
    vector<string> vstr;
    for(int i=0;i<n;i++){
        cin>>vstr[i];
    }
    for(int i=0,j=0;i<n;i++,j++){
        for(int a=i+1,b=j+1;a<n;a++,b++){
            if(vstr[a][j]=='W'&&vstr[i][b]!='L'){
                cout<<"incorrect\n";return;
            }
            if(vstr[a][j]=='L'&&vstr[i][b]!='W'){
                cout<<"incorrect\n";return;
            }
            if(vstr[a][j]=='D'&&vstr[i][b]!='D'){
                cout<<"incorrect\n";return;
            }
        }
    }
    cout<<"correct\n";
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    solve();
    return 0;
}
