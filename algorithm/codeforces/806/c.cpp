#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    int n;
    vector<int> arr(n);
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    for(int i=0;i<n;i++){
        int k;
        string str;
        cin>>k>>str;
        for(int j=0;j<k;j++){
            if(str[k]=='U'){
                if(--arr[i]==-1){
                    arr[i]=9;
                }
            }else{
                if(++arr[i]==10){
                    arr[i]=0;
                }
            }
        }
    }
    for(int i:arr){
        cout<<i;
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
