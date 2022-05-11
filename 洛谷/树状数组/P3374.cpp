#include <bits/stdc++.h>
using namespace std;
int N;
int tree[500001];
int lowbit(int x){
    return x&(-x);
}
int add(int x,int val){
    for(int i=x;i<=N;i+=lowbit(i)){
        tree[i]+=val;
    }
    return 0;
}
int qurry(int x){
    int res=0;
    for(int i=x;i>=1;i-=lowbit(i)){
        res+=tree[i];
    }
    return res;
}
int main(){
    freopen("./test.txt","r",stdin);
    int n,m;
    cin>>n>>m;
    N=n;
    for(int i=0;i<n;i++){
        int k;
        cin>>k;
        add(i+1,k);
    }
    for(int i=0;i<m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        if(a==1){
            add(b,c);
        }else{
            cout<<qurry(c)-qurry(b-1)<<endl;
        }
    }
    return 0;
}