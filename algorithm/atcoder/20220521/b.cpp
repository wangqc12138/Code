#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int N,K;
    cin>>N>>K;
    set<int> st;
    int maxn=0;
    for(int i=0;i<N;i++){
        int k;
        cin>>k;
        if(maxn<k){
            maxn=k;
            st.clear();
            st.emplace(i);
        }else if(maxn==k){
            st.emplace(i);
        }
    }
    bool flag=false;
    for(int i=0;i<K;i++){
        int k;
        cin>>k;
        if(st.count(k)){
            flag=true;
        }
    }
    if(flag){
        cout<<"YES"<<endl;
    }else{
        cout<<"NO"<<endl;
    }
    return 0;
}