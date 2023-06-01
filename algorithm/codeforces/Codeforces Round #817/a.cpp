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
    int m,n;
    cin>>m>>n;
    string str;
    cin>>str;
    sort(str.begin(),str.end());
    for(int i=0;i<m;i++){
        string temp;
        cin>>temp;
        sort(temp.begin(),temp.end());
        if(temp==str){
            cout<<"yes\n";
        }else{
            cout<<"no\n";
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
