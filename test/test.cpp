#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        if(n==1){
            cout<<-1<<endl;
            continue;
        }
        vector<int> a(n);
        for(int i=0;i<n;i++){
            cin>>a[i];
        }
        auto b=a;
        sort(a.begin(),a.end());
        vector<int> ans;
        int i=0;
        for(;i<n-1;i++){
            if(a[i]==b[i]){
                ans.emplace_back(a[i+1]);
                ans.emplace_back(a[i]);
                i++;
            }else{
                ans.emplace_back(a[i]);
            }
        }
        ans.emplace_back(a[n-1]);
        if(b[n-1]==ans[n-1]){
            int t=ans[n-1];
            ans[n-1]=ans[n-2];
            ans[n-2]=t;
        }
        for(auto i:ans){
            cout<<i<<" ";
        }
        cout<<endl;
    }
    return 0;
}