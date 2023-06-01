#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        int n,sum=0;
        cin>>n;
        int a[n];
        for(int i=0;i<n;i++){
            cin>>a[i];
            sum+=a[i];
        }
        if(sum!=0){
            cout<<"NO"<<endl;
            continue;
        }
        if(n==1){
            cout<<"YES"<<endl;
            continue;
        }
        bool flag=false;
        int i=n-1;
        for(;i>=0;i--){
            if(a[i]<0){
                break;
            }else if(a[i]>0){
                flag=true;
                break;
            }
        }
        if(flag){
            cout<<"NO"<<endl;
            continue;
        }
        int k=0;
        for(;i>0;i--){
            k+=a[i];
            if(k>=0){
                flag=true;
                break;
            }
        }
        if(flag){
            cout<<"NO"<<endl;
        }else{
            cout<<"YES"<<endl;
        }
    }
    return 0;
}