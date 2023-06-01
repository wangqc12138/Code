#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        long long a,b,c,x,y;
        cin>>a>>b>>c>>x>>y;
        if(x+y>a+b+c){
            cout<<"NO"<<endl;
            continue;
        }
        c-=x-a>0?x-a:0;
        c-=y-b>0?y-b:0;
        if(c<0){
            cout<<"NO"<<endl;
        }else{
            cout<<"YES"<<endl;
        }
    }
    return 0;
}
