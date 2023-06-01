#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int m,n;
    cin>>m>>n;
    int arr[m];
    for(int i=0;i<m;i++){
        cin>>arr[i];
    }
    sort(arr,arr+m);
    while(n--){
        int p,q;
        cin>>p>>q;
        int ans=0;
        for(int i=p-1;i>=0&&i>p-1-q;i--){
            ans+=arr[i];
        }
        cout<<ans<<endl;
    }
    return 0;
}