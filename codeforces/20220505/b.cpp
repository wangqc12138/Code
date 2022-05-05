#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int m;
        cin>>m;
        int a[m];
        for(int i=0;i<m;i++){
            cin>>a[i];
        }
        int p=a[m-1];
        bool flag=true;
        int res=0;
        for(int i=m-2;i>=0;i--){
            while(a[i]>=p){
                res++;
                a[i]/=2;
                if(a[i]==0&&p==0){
                    break;
                }
            }
            if(p==a[i]){
                flag=false;
                break;
            }
            p=a[i];
        }
        if(flag){
            cout<<res<<endl;
        }else{
            cout<<"-1"<<endl;
        }
    }
    return 0;
}
