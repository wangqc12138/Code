#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        int m,n,sum=0;
        cin>>m>>n;
        int a[m];
        for(int i=0;i<m;i++){
            cin>>a[i];
            sum+=a[i];
        }
        if(sum<n){
            cout<<-1<<endl;
            continue;
        }
        if(sum==n){
            cout<<0<<endl;
            continue;
        }
        map<int,int> mpl,mpr;
        int index=0;
        mpl[0]=0,mpr[0]=0;
        for(int i=0;i<m;i++){
            if(a[i]==1){
                mpl[++index]=i+1;
            }
        }
        index=0;
        for(int i=m-1;i>=0;i--){
            if(a[i]==1){
                mpr[++index]=m-i;
            }
        }
        int ans=m;
        for(int i=0;i<=sum-n;i++){
            ans=min(ans,mpl[i]+mpl[sum-n-i]);
        }
        cout<<ans<<endl;
    }
    return 0;
}