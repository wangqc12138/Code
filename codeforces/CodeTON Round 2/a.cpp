#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
#define bit(x,i)(((x)>>(i))&1)
using ll=long long;
using pii=pair<int,int>;
void solve(){
    int m,n;
    cin>>m>>n;
    string s1,s2;
    cin>>s1>>s2;
    int arr[2]={0,0};
    for(int i=0;i<=m-n;i++){
        if(s1[i]=='0'){
            arr[0]=1;
        }else{
            arr[1]=1;
        }
    }
    string s3=s1.substr(m-n+1);
    string s4(s2,2);
    if(arr[s2[0]-'0']==0||s3!=s4){
        cout<<"no\n";return;
    }
    cout<<"yes\n";
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    int tt;cin>>tt;for(int i=0;i<tt;i++){solve();}
    return 0;
}
