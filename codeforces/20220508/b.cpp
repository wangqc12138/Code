#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int M;
    cin>>M;
    while(M--){
        int len;
        string str;
        cin>>len>>str;
        int le=1,ans=0;
        vector<int> vec;
        for(int i=1;i<len;i++){
            if(str[i]!=str[i-1]&&le%2){
                ans++;
                vec.emplace_back(le);
                le=0;
                continue;
            }
            le++;
        }
        int t=ans;
        int k=0;
        sort(vec.begin(),vec.end());
        for(auto i:vec){
            if(i<t){
                k++;
                t-=i;
            }else{
                break;
            }
        }
        cout<<ans<<" "<<vec.size()-k<<endl;
    }
    return 0;
}
