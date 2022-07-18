#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    int n,m;
    cin>>n>>m;
    string str(m,'B');
    for(int i=0;i<n;i++){
        int k;
        cin>>k;
        int a=min(k-1,m-k);
        int b=max(k-1,m-k);
        if(str[a]=='A'){
            str[b]='A';
        }else{
            str[a]='A';
        }
    }
    cout<<str<<endl;
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    int tt;cin>>tt;for(int i=0;i<tt;i++){solve();}
    return 0;
}
