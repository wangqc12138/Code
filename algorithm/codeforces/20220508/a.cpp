#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int M;
    cin>>M;
    while(M--){
        int N;
        cin>>N;
        set<int> st;
        int f1=0,f2=0;
        for(int i=0;i<N;i++){
            int k;
            cin>>k;
            if(k==0){
                f1++;
            }
            if(st.count(k)){
                f2++;
            }
            st.emplace(k);
        }
        //cout<<N<<" "<<f1<<" "<<f2<<" ";
        if(f1){
            cout<<N-f1<<endl;
        }else if(f2){
            cout<<N<<endl;
        }else{
            cout<<N+1<<endl;
        }
    }
    return 0;
}
