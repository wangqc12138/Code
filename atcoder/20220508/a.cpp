#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    // int M;
    // cin>>M;
    // while(M--){

    // }
    int H,W,R,C;
    cin>>H>>W>>R>>C;
    int ans=4;
    if(R==1){
        ans--;
    }
    if(R==H){
        ans--;
    }
    if(C==1){
        ans--;
    }
    if(C==W){
        ans--;
    }
    cout<<ans;
    return 0;
}