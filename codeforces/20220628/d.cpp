#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int n;
    cin>>n;
    int sum=0,minn=0;
    for(int i=1;i<=n;i++){
        int v;
        cin>>v;
        sum+=v;
        minn=max(minn,(sum+i-1)/i);
    }
    int q;
    cin>>q;
    while(q--){
        int t;
        cin>>t;
        if(t<minn){
            cout<<"-1"<<endl;
        }else{
            cout<<(sum+t-1)/t<<endl;
        }
    }
    return 0;
}