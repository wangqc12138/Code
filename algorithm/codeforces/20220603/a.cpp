#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int t;
    cin>>t;
    while(t--){
        int m;
        cin>>m;
        int i=1;
        for(;i<INT_MAX;i++){
            if(m&i>0&&m^i>0){
                break;
            }
        }
        cout<<i<<endl;
    }
    return 0;
}
