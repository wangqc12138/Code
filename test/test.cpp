#include <bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
int main(){
    freopen("./test.txt","r",stdin);
    int M;
    cin>>M;
    while(M--){
        int N;
        cin>>N;
        int a[3][N];
        int b[3][N+1];
        for(int i=0;i<3;i++)
        for(int j=0;j<N;j++){
            cin>>a[i][j];
        }
        set<int> st;
        for(int i=0;i<N;i++){
            if(st.count(a[1][i])||st.count(a[0][i])||a[2][i]!=0){
                st.emplace(a[0][i]);
                st.emplace(a[2][i]);
            }
            if(a[1][i]==a[0][i]){
                st.emplace(a[0][i]);
            }
        }
        set<pii> sp;
        int k=0,ans=2;
        for(int i=0;i<N;i++){
            if(st.count(a[0][i])){
                continue;
            }else{
                k++;
                if(sp.count(pii(a[0][i],a[1][i]))){
                    ans*=2;
                    k--;
                }
                sp.emplace(a[1][i],a[0][i]);
            }
        }
        if(k==sp.size()/2){
            ans/=2;
        }
        cout<<ans<<endl;
    }
    return 0;
}