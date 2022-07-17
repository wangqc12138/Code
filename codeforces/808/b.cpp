#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    int n,l,r;
    cin>>n>>l>>r;
    vector<int> vec(n+1,-1);

    for(int i=(n+2)/2;i<=n;i++){
        int a=l/i,b=r/i;
        if(a==b&&a*i<l){
            cout<<"no\n";return;
        }
        vec[i]=b*i;    
    }
    for(int i=n;i>=1;i--){
        if(vec[i]==-1){
            vec[i]=vec[2*i];
        }
    }
    cout<<"yes\n";
    for(int i=1;i<=n;i++){
        cout<<vec[i]<<" ";
    }
    cout<<endl;
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    int tt;cin>>tt;for(int i=0;i<tt;i++){solve();}
    return 0;
}
