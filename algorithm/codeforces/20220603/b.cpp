#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int t;
    cin>>t;
    while(t--){
        int m;
        cin>>m;
        int index=100,n=0;
        for(int i=0;i<m;i++){
            int k;
            cin>>k;
            if(k%2==0){
                n++;
                int t=0;
                while(k%2==0&&t<=index){
                    t++;
                    k/=2;
                }
                index=min(index,t);
            }
        }
        if(n==0){
            cout<<0<<endl;
        }else if(m!=n){
            cout<<n<<endl;
        }else{
            cout<<index+n-1<<endl;
        }
        
    }
    return 0;
}
