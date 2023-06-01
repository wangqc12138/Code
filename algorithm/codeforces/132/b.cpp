#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    int n,m;
    cin>>n>>m;
    long long a[n],b[n],c[n],d[n],e[n];
    for(int i=0;i<n;i++){
        cin>>a[i];
        if(i==0){
            b[i]=0;
            c[i]=0;
        }else{
            if(a[i-1]-a[i]>0){
                b[i]=a[i-1]-a[i];
            }else{
                b[i]=0;
            }
            c[i]=c[i-1]+b[i];
        }
    }
    d[n-1]=0;
    e[n-1]=0;
    for(int i=n-2;i>=0;i--){
        if(a[i+1]-a[i]>0){
            d[i]=a[i+1]-a[i];
        }else{
            d[i]=0;
        }
        e[i]=e[i+1]+d[i];
    }
    for(int i=0;i<m;i++){
        int s,t;
        cin>>s>>t;
        if(t>=s){
            cout<<c[t-1]-c[s-1]<<endl;;
        }else{
            cout<<e[t-1]-e[s-1]<<endl;;
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