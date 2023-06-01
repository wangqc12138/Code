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
                if(c+x>=k&&d>0){
                    if(c==x){
                        if(y==1){
                            continue;
                        }else{
                            ans+=y/2;
                            mp[x]=mp[x]%2;
                        }
                    }else{
                        if(y>=d){
                            mp[x]=y-d;
                            mp[c]=0;
                            ans+=y-d;
                        }else{
                            mp[x]=0;
                            mp[c]=d-y;
                            ans+=d-y;
                            break;
                        }
                    }
                }
            }
        }
        cout<<ans<<endl;
    }
}