#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    long long T;
    cin>>T;
    while(T--){
        long long M,N;
        cin>>M>>N;
        map<long long,long long> mp;
        for(long long i=0;i<M;i++){
            long long k;
            cin>>k;
            mp[k]++;
        }
        vector<long long> help;
        for(auto [x,y]:mp){
            if(y>=N){
                help.emplace_back(x);
            }
        }
        if(help.empty()){
            cout<<-1<<endl;
            continue;
        }
        sort(help.begin(),help.end());
        pair<long long,long long> ans={-1,-1};
        long long l=0,r=0,n=help.size(),len=0;
        for(;r<n;r++){
            if(r>0&&help[r]-help[r-1]!=1){
                if(r-1-l>=len){
                    len=r-1-l;
                    ans={help[l],help[r-1]};
                }
                l=r;
            }
        }
        if(r-1-l>=len){
            ans={help[l],help[r-1]};
        }
        cout<<ans.first<<" "<<ans.second<<endl;
    }
    return 0;
}
