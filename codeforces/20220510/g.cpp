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
        for(int i=0;i<M-1;i++){
            int p;
            cin>>p;
            next[p].emplace_back(i+2);
        }
        string str;
        cin>>str;
        int ans=0;
        function<pair<int,int>(int)> dfs=[&](int root) -> pair<int,int>{
            int w=str[root-1]=='W',b=1-w;
            for(int i:next[root]){
                auto p=dfs(i);
                w+=p.first;
                b+=p.second;
            }
            if(w==b){
                //cout<<root<<":"<<w<<" "<<b<<endl;
                ans++;
            }
            return {w,b}; 
        };
        dfs(1);
        cout<<ans<<endl;
    }
    return 0;
}
