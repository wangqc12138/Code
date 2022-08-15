#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
#define bit(x,i)(((x)>>(i))&1)
#define no {puts("No") ; return ;}
#define yes {puts("Yes") ; return ;}
using ll=long long;
using pii=pair<int,int>;
void solve(){
    int n;
    cin>>n;
    if(n%3==0){
        cout<<n/3<<endl;return;
    }
    if(n==1){
        cout<<1<<endl;return;
    }
    if(n<10){
        cout<<(n+2)/3<<endl;return;
    }
    if(n%3==2){
        cout<<n/3+1<<endl;return;
    }
    cout<<n/3+2<<endl;;
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    int tt;cin>>tt;for(int i=0;i<tt;i++){solve();}
    return 0;
}
