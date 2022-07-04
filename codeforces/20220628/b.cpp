#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        int m,n;
        cin>>m>>n;
        int arr[m];
        for(int i=0;i<m;i++){
            cin>>arr[i];
        }
        int ans=0;
        for(int i=1;i<m-1;i++){
            if(arr[i]>arr[i-1]+arr[i+1]){
                ans++;
            }
        }
        if(n==1){
            cout<<(m-1)/2<<endl;
        }else{
            cout<<ans<<endl;
        }
    }
    return 0;
}