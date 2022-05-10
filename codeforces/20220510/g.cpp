#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    long long T;
    cin>>T;
    while(T--){
        int M;
        cin>>M;
        map<int,vector<int>> next;
        for(int i=0;i<M;i++){
            int p;
            cin>>p;
            next[p].emplace_back(i+2);
        }
        string str;
        cin>>str;
        int ans=0;
        auto dfs=[&](int root) -> pair<int,int>{
            int w=str[root+1]=='W',b=1-w;
            for(int i:next[root]){
                dfs(i);
                w+=dfs(i).first;
                b+=dfs(i).second;
            }
            if(w==b){
                ans++;
            }
            return {w,b}; 
        }
        dfs(1);
        cout<<ans<<endl;
    }
    return 0;
}
