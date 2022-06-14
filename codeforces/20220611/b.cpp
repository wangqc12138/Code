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
        for(;i<n-3;i+=2){
            if(a[i]==b[i]){
                ans.emplace_back(a[i+1]);
                ans.emplace_back(a[i]);
            }
        }
        if(n%2==1){
            if(a[i]==b[i]){
                ans.emplace_back(a[i+1]);
                if(a[i+1]==b[i+1]){
                    ans.emplace_back(a[i+2]);
                    ans.emplace_back(a[i]);
                }else{
                    ans.emplace_back(a[i]);
                    ans.emplace_back(a[i+2]);
                }
            }else{
                if(b[i]>b[i+1]&&b[i+1]<b[i+2]||b[i]>b[i+1]&&b[i+1]>b[i+2]){
                    ans.emplace_back(a[i]);
                    ans.emplace_back(a[i+2]);
                    ans.emplace_back(a[i+1]);
                }else{
                    ans.emplace_back(a[i]);
                    ans.emplace_back(a[i+1]);
                    ans.emplace_back(a[i+2]);
                }
            }
        }
        if(n%2){
            if(a[n-2]==b[n-2]){
                ans.emplace_back(a[n-1]);
                ans.emplace_back(a[n-2]);
            }else{
                ans.emplace_back(a[n-2]);
                ans.emplace_back(a[n-1]);
            }
        }
        for(auto i:ans){
            cout<<i<<" ";
        }
        cout<<endl;
    }
    return 0;
}