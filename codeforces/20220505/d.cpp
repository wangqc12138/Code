#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int m;
        cin>>m;
        int root;
        map<int,vector<int>> next;
        for(int j=0;j<m;j++){
            int k;
            cin>>k;
            if(k==j+1){
                root=k;
            }else{
                next[j+1].emplace_back(k);
            }
        }
        auto dfs=[](int)
    }
    return 0;
}
