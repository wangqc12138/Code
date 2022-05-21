#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    vector<vector<int>> m(10);
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        string temp;
        cin>>temp;
        int index=0;
        for(auto c:temp){
            m[c-'0'].emplace_back(++index);
        }
    }
    int ans=10*(n-1);
    for(int i=0;i<10;i++){
        int k[10];
        int t=0;
        for(int j:m[i]){
            t+=k[j]*10+j;
        }
        ans=min(t,ans);
    }
    cout<<ans<<endl;
    return 0;
}