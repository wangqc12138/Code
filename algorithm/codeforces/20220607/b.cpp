#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        int a[n],b[n];
        for(int i=0;i<n;i++){
            cin>>a[i];
        }
        for(int i=0;i<n;i++){
            cin>>b[i];
        }
        int k=0;
        int i=0;
        for(;i<n;i++){
            if(b[i]!=0){
                k=a[i]-b[i];
                break;
            }
        }
        if(i==n){
            cout<<"YES"<<endl;
            continue;
        }
        if(k<0){
            cout<<"NO"<<endl;
            continue;
        }
        auto c=a;
        for(int i=0;i<n;i++){
            c[i]-=k;
            if(c[i]<0){
                c[i]=0;
            }
        }
        bool flag=true;
        for(int i=0;i<n;i++){
            if(c[i]!=b[i]){
                flag=false;
                break;
            }
        }
        if(flag){
            cout<<"YES"<<endl;
        }else{
            cout<<"NO"<<endl;
        }
    }
}