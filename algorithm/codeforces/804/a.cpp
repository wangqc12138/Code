#include <bits/stdc++.h>
using namespace std;
void solve(){
    int n;
    cin>>n;
    int a=0,b=0,c=0;
    if(n&1){
        cout<<"-1\n";
    }
    int arr[32];
    for(int i=0;i<32;i++){
        int k=(n>>i)&1;
        arr[i]=k;
    }
    for(int i=0;i<31;i++){
        if(arr[i]==0&&arr[i+1]==1){
            a+=(1>>i);
            b+=(0>>i);
            c+=(0>>i);
        }else{
            a+=(0>>i);
            b+=(0>>i);
            c+=(0>>i);
        }
    }
    cout<<a<<" "<<b<<" "<<c<<endl;
}
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        
    }
    return 0;
}