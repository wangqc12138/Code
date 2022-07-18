#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    long long n;
    cin>>n;
    long long arr[n];
    for(long long i=0;i<n;i++){
        cin>>arr[i];
    }
    vector<long long> temp(n);
    for(long long i=1;i<n-1;i++){
        long long m=max(arr[i-1],arr[i+1]);
        if(m>=arr[i]){
            if(i==1||i==2){
                temp[i]=m+1-arr[i];
            }else{
                temp[i]=temp[i-2]+m+1-arr[i];
            }
        }
        else{
            if(i==1||i==2){
                temp[i]=0;
            }else{
                temp[i]=temp[i-2];
            }
        }   
    }
    if(n%2){
        cout<<temp[n-2]<<endl;
    }else{
        long long m=temp[n-2];
        for(long long i=1;i<n-2;i+=2){
            long long k=temp[n-2]-temp[i+1]+temp[i];
            if(m>k){
                m=k;
            }
        }
        cout<<m<<endl;
    }
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    int tt;cin>>tt;for(int i=0;i<tt;i++){solve();}
    return 0;
}
