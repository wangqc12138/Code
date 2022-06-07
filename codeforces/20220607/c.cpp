#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        int m;
        int a[m],b[m];
        for(int i=0;i<m;i++){
            cin>>a[i];
        }
        for(int i=0;i<m;i++){
            cin>>b[i];
        }
        for(int i=0;i<m;i++){
            if(i==0){
                cout<<b[i]-a[i]<<endl;;
            }else{
                if(a[i]>=b[i-1]){
                    cout<<b[i]-a[i]<<endl;
                }else{
                    cout<<b[i]-b[i-1]<<endl;;
                }
            }
        }
    }
}