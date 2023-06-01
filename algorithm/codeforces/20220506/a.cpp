#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int M;
    cin>>M;
    while(M--){
        int N;
        cin>>N;
        int a[N];
        int index=0;
        for(int i=0;i<N;i++){
            cin>>a[i];
            if(a[i]<0){
                index++;
                a[i]=-a[i];
            }
        }
        for(int i=0;i<index;i++){
            a[i]=-a[i];
        }
        bool flag=true;
        for(int i=1;i<N;i++){
            if(a[i]<a[i-1]){
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
    return 0;
}
