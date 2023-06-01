#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
#define bit(x,i)(((x)>>(i))&1)
using ll=long long;
using pii=pair<int,int>;
void solve(){
    int n;
    string str;
    cin>>n>>str;
    int left=0,right=n-1;
    while(left<right){
        char L=str[left],R=str[right];
        if(L==R){
            continue;
        }else if(L=='A'||R=='B'){
            cout<<"No\n";
            return;
        }else{
            str[left+1]='B';
        }
        left++;
        right++;
    }
    cout<<"Yes\n";
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    solve();
    return 0;
}