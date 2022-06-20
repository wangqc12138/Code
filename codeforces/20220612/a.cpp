#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        int n,k,sum=0;
        cin>>n>>k;
        for(int i=0;i<n;i++){
            int x;
            cin>>x;
            sum+=x;
        }
        cout<<(sum-k>=0?sum-k:0)<<endl;
    }
    return 0;
}