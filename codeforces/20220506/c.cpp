#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int M;
    cin>>M;
    while(M--){
        int N;
        cin>>N;
        int a[3][N];
        int b[3][N];
        for(int i=0;i<3;i++)
        for(int j=0;j<N;j++){
            cin>>a[i][j];
            b[i][a[i][j]]=j;
        }
        int visit[N];
        memset(visit,0,sizeof(visit));
        for(int i=0;i<N;i++){
            if(a[2][i]!=0&&visit[i]==0){
                int k=a[2][i];
                int index=i;
                while(k>0&&visit[index]==0){
                    visit[index]=1;
                    if(a[0][index]==a[1][index]){
                        break;
                    }
                    if(a[1][index]==k){
                        int t=b[1][k];
                        a[2][t]=a[1][t];
                        k=a[1][t];
                        index=t;
                    }
                    if(a[0][index]==k){
                        int t=b[0][k];
                        a[2][t]=a[0][t];
                        k=a[0][t];
                        index=t;
                    }
                }
            }
        }
        set<pair<int,int>> st;
        int ans=2;
        for(int i=0;i<N;i++){
            if(a[2][i]==0){
                if(st.count(pair<int,int>(a[1][i],a[0][i]))){
                    ans*=2;
                }
                st.emplace(a[0][i],a[1][i]);
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}