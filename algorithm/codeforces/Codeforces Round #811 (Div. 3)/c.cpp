#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
#define bit(x,i)(((x)>>(i))&1)
using ll=long long;
using pii=pair<int,int>;
void solve(){
    int n;
    cin>>n;
    string str="";
    int k=9;
    while(n){
        if(n<k){
            str+=n+'0';
        }
        str+=k+'0';
        k--;
    }
    reverse(str.begin(),str.end());
    cout<<str<<endl;
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    int tt;cin>>tt;for(int i=0;i<tt;i++){solve();}
    return 0;
}
