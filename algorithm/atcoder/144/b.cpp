#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    int n,a,b,sum=0;
    cin>>n>>a>>b;
    vector<int> arr(n);
    for(int i=0;i<n;i++){
        cin>>arr[i];
        sum+=arr[i];
    }
    int L=0,R=sum/n;
    auto check=[=](int m){
        int c=0,d=0;
        for(auto i:arr){
            if(i>m){
                d+=(i-m)/b;
            }else{
                c+=(m-i+a-1)/a;
            }
        }
        return d>=c;
    };
    while(L<R){
        int mid=(L+R)>>1;
        if(check(mid)){
            L=mid;
        }else{
            R=mid-1;
        }
    }
    cout<<L<<endl;
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    //freopen("./test.txt","r",stdin);
    solve();
    return 0;
}
