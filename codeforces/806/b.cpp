#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    int len;
    cin>>len;
    string str;
    cin>>str;
    int arr[26];
    int ans=0;
    memset(arr,0,sizeof(arr));
    for(int i=0;i<len;i++){
        if(arr[str[i]-'a']==0){
            ans+=2;
        }else{
            ans++;
        }
        arr[arr[i]-'a']=1;
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
