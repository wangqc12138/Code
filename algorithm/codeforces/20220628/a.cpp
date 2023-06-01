#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        int arr[n];
        int sum=0;
        for(int i=0;i<n;i++){
            cin>>arr[i];
            sum^=arr[i];
        }
        int ans=0;
        for(int i=0;i<n;i++){
            if(sum^arr[i]==arr[i]){
                ans=arr[i];
                break;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}