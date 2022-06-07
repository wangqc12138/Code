#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        int n,k;
        cin>>n>>k;
        map<int,int> mp;
        int ans=0;
        for(int i=0;i<n;i++){
            int t;
            cin>>t;
            mp[t%k]++;
            ans+=t/k;
        }
        for(auto [x,y]:mp){
            for(auto [c,d]:mp){
                if(c+x>=k){
                    if(c==x&&mp[c]==1){
                        continue;
                    }
                    if(--mp[x]==0){
                            mp.erase(x);
                        }
                        if(--mp[c]==0){
                            mp.erase(c);
                        }
                    ans++;
                }
            }
        }
        cout<<ans<<endl;
    }
}