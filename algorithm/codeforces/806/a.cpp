#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    string str;
    cin>>str;
    if((str[0]=='Y'||str[0]=='y')&&(str[1]=='e'||str[1]=='E')&&(str[2]=='s'||str[2]=='S')){
        cout<<"yes\n";
    }else{
        cout<<"no\n";
    }
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    int tt;cin>>tt;for(int i=0;i<tt;i++){solve();}
    return 0;
}
