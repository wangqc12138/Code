#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        int a[n+1];
        int p[n+1];
        int visit[n+1];
        int k[n+1][2];
        memset(p,0,sizeof(p));
        memset(a,0,sizeof(a));
        memset(visit,0,sizeof(visit));
        memset(k,0,sizeof(k));
        for(int i=2;i<=n;i++){
            cin>>a[i];
            p[a[i]]=1;
        }
        set<int> child;
        for(int i=1;i<=n;i++){
            cin>>k[i][0]>>k[i][1];
            if(p[i]==0){
                child.emplace(i);
            }
        }
        int ans=0;
        for(auto i:child){
            int need=k[i][1];
            while(i!=0){
                if(visit[i]==1){
                    break;
                }
                visit[i]=1;
                int f=a[i];
                if(k[f][0]>need){
                    ans++;
                    need=k[f][1];
                }   
            }
            ans++;
        }
        cout<<ans<<endl;
    }
    return 0;
}