#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        int m,k;
        cin>>m>>k;
        int a[m];
        set<int> st;
        for(int i=0;i<m;i++){
            cin>>a[i];
            if(i!=0&&a[i]*2<=a[i-1]){
                st.emplace(i);
            }
        }
        int begin=0,ans=0;
        for(int i:st){
            if(i-begin>k){
                ans+=i-begin-k;
            }
            begin=i;
        }
        if(m-1-begin>k){
            ans+=m-1-begin-k;
        }
        cout<<ans<<endl;
    }
    return 0;
}