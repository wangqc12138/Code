#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    int m,n,k;
    cin>>m>>n>>k;
    int arr[k];
    int sum=0;
    priority_queue<int> mpq;
    for(int i=0;i<k;i++){
        cin>>arr[i];
        mpq.emplace(arr[i]);
        sum+=arr[i];
    }
    if(sum<m*n){
        cout<<"no\n";
        return;
    }
    int M=min(m,n);
    int N=max(m,n);
    while(!mpq.empty()&&N){
        int f=mpq.top();
        mpq.pop();
        if(f<2*M){
            continue;
        }
        if(N==3&&f<3*M){
            continue;
        }
        if(N==3||N==2){
            cout<<"yes\n";
            return;
        }
        f-=2*M;
        N-=2;
        mpq.emplace(f);
    }
    cout<<"no\n";
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    int tt;cin>>tt;for(int i=0;i<tt;i++){solve();}
    return 0;
}
