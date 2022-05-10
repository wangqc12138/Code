#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int M;
    cin>>M;
    while(M--){
        int N,L;
        cin>>N>>L;
        vector<string> temp;
        int ans=L*26;
        for(int i=0;i<N;i++){
            string str;
            cin>>str;
            for(auto s:temp){
                int k=0;
                for(int j=0;j<L;j++){
                    k+=abs(str[j]-s[j]);
                }
                ans=min(ans,k);
            }
            temp.emplace_back(str);
        }
        cout<<ans<<endl;
    }
    return 0;
}
