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
    int n,k;
    cin>>n>>k;
    if(k%2==1){
        cout<<'yes\n';
        for(int i=1;i<=n;i+=2){
            cout<<i<<" "<<i+1<<endl;
        }
    }else{
        for(int i=2;i<=n;i++){
            if((i+k)%4!=0){
                cout<<"no\n";return;
            }
        }
        cout<<'yes\n';
        for(int i=1;i<=n;i+=2){
            cout<<i<<" "<<i+1<<endl;
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    int tt;cin>>tt;for(int i=0;i<tt;i++){solve();}
    return 0;
}
