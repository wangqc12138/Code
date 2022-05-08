#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int M;
    cin>>M;
    while(M--){
<<<<<<< HEAD
        int len;
        string str;
        cin>>len>>str;
        int le=1,ans=0;
        vector<int> vec;
        for(int i=1;i<len;i++){
            if(str[i]!=str[i-1]&&le%2){
                ans++;
                vec.emplace_back(le+1);
                le=0;
                continue;
            }
            le++;
        }
        int t=ans;
        int k=0;
        sort(vec.begin(),vec.end());
        for(auto i:vec){
            cout<<i<<" ";
            if(i<t){
                k++;
                t-=i;
=======
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
        long long k=0,ans=1;
        for(int i=0;i<N;i++){
            if(st.count(a[0][i])){
                continue;
            }else{
                k++;
                if(sp.count(pii(a[0][i],a[1][i]))){
                    ans=ans*2%1000000007;
                    k--;
                }
                sp.emplace(a[1][i],a[0][i]);
>>>>>>> 3d2f28ce9c15b0d0b6617a3a19a89489d20fc1fb
            }
            // else{
            //     break;
            // }
        }
<<<<<<< HEAD
        cout<<endl;
        cout<<ans<<" "<<vec.size()-k<<endl;
=======
        if(k*2>sp.size()){
            ans=ans*2%1000000007;
        }
        cout<<ans<<endl;
>>>>>>> 3d2f28ce9c15b0d0b6617a3a19a89489d20fc1fb
    }
    return 0;
}
