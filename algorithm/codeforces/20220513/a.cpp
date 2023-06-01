#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int M;
    cin>>M;
    while(M--){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        if(a<c){
            if(b<c){
                cout<<a+c<<endl;
            }else{
                cout<<2*c<<endl;
            }
        }else{
            if(d<a){
                cout<<a+c<<endl;
            }else{
                cout<<2*a<<endl;
            }
        }
    }
    return 0;
}
