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
        map<int,int> mp;
        int t=0,k=0;
        for(int j:m[i]){
            t=max(t,j+mp[j]);
            k=max(k,mp[j+mp[j]]++);
        }
        cout<<
        ans=min(k*10+t-1,ans);
    }
    cout<<ans<<endl;
    return 0;
}