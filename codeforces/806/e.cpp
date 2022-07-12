#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    int n;
    cin>>n;
    vector<string> vstr(n);
    for(int i=0;i<n;i++){
        cin>>vstr[i];
    }
    int a=0,b=0,c=n-1,d=n-1;
    int ans=0;
    while(a<c&&b<d){
        int i=a,j=b;
        vector<int> arr(c-a,0);
        for(int index=0;j<d;j++){
            arr[index++]+=vstr[i][j]-'0';
        }  
        for(int index=0;i<c;i++){
            arr[index++]+=vstr[i][j]-'0';
        } 
        for(int index=0;j>b;j++){
            arr[index++]+=vstr[i][j]-'0';
        }
        for(int index=0;i>a;i++){
            arr[index++]+=vstr[i][j]-'0';
        }
        a++,b++,c--,d--;
        for(int k:arr){
            ans+=min(4-k,k);
        }
    }
    cout<<ans<<endl;
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    int tt;cin>>tt;for(int i=0;i<tt;i++){solve();}
    return 0;
}
