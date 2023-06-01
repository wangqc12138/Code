#include <bits/stdc++.h>
using namespace std;
int main(){
    int T;
    cin>>T;
    while(T--){
        int k;
        cin>>k;
        int t=k%3;
        int n=k/3;
        cout<<k<<" "<<t<<" "<<n<<endl;
        if(t==0){
            printf("%d %d %d\n",n,n+1,n-1);
        }else if(t==1){
            printf("%d %d %d\n",n,n+2,n-1);
        }else if(t==1){
            printf("%d %d %d\n",n+1,n+2,n-1);
        }
    }
    return 0;
}