#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        map<int,vector<int>> mp;
        for(int i=0;i<n;i++){
            int k;
            cin>>k;
            mp[k].emplace_back(i);
        }
        int ans=1;
        for(auto &[x,y]:mp){
            int k=1;
            for(int i=0;i<y.size();i++){
                if(i>0){
                    k=max(1,k-(y[i]-y[i-1]+1));
                    ans=max(k,ans);
                }
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}