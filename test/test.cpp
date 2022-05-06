#include <bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
int main(){
    freopen("./test.txt","r",stdin);
    int N;
    cin>>N;
    while(N--){
        int M;
        cin>>M;
        int son[M+1],parent[M+1],visit[M+1];
        memset(son,1,sizeof(int)*(M+1));
        memset(visit,0,sizeof(int)*(M+1));
        int index=0; 
        for(int i=0;i<M;i++){
            int K;
            cin>>K;
            if(son[K]){
                index++;
            }
            son[K]=0;
            parent[i+1]=K;
        }
        if(M==1){
            cout<<1<<endl<<1<<endl<<1<<endl<<endl;;
            continue;
        }
        cout<<M-index<<endl;
        for(int i=0;i<M;i++){
            if(son[i+1]==0){
                continue;
            }
            int k=i+1;
            vector<int> ans;
            while(!visit[k]){
                ans.emplace_back(k);
                visit[k]=1;
                k=parent[k];
            }
            cout<<ans.size()<<endl;
            for(int j=ans.size()-1;j>=0;j--){
                if(j==0){
                    cout<<ans[j]<<endl;
                }else{
                    cout<<ans[j]<<" ";
                }
            }
        }
        cout<<endl;
    }
    return 0;
}