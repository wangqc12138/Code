#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        map<int,vector<int>> mp;
        for(int i=0;i<n;i++){
            int k;
            cin>>k;
            mp[k].emplace_back(i);
        }
        int ans=1;
        int maxn=-1,r=-1,p=-1,l=-1;
        for(auto &[x,y]:mp){
            int k=1;
            if(maxn==-1){
                maxn=x;
                r=y[0];
                l=y[0];
            }
            p=y[0];
            for(int i=0;i<y.size();i++){
                if(i>0){
                    k=max(1,k-(y[i]-y[i-1]-1)+1);
                    if(k==1){
                        p=y[i];
                    }
                    if(k>ans){
                        l=p;
                        ans=k;
                        r=y[i];
                        maxn=x;
                    }
                }
            }
        }
        cout<<maxn<<" "<<l+1<<" "<<r+1<<endl;;
    }
    return 0;
}