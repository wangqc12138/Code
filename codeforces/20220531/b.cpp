#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int M,N;
    cin>>M;
    while(M--){
        cin>>N;
        map<int,int> mp;
        for(int i=0;i<N;i++){
            int k;
            cin>>k;
            mp[k]++;
        }
        vector<int> ans(N);
        int k=1;
        for(auto [x,y]:mp){
            if(y==1){
                ans.clear();
                break;
            }else{
                for(int i=k;i<k+y-1;i++){
                    ans[i-1]=i;
                }
                ans[k+y-1]=k;
            }
            k+=y;
        }
        if(ans.empty()){
            cout<<-1<<endl;
        }else{
            for(int i=0;i<N;i++){
                cout<<i<<(i==N-1)?"\n":" ";
            }
        }
    }
    return 0;
}
