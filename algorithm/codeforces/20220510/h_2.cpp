//这个问题可以用归并排序找逆序对
//这个问题还可以用树状数组来解决
//此处使用树状数组
#include <bits/stdc++.h>
using namespace std;
int tree[200002];
int N;
int lowbit(int x){
    return x&(-x);
}
void add(int x,int val){
    for(int i=x;i<=N;i+=lowbit(i)){
        tree[i]+=val;
    }
}
int query(int x){
    int res=0;
    for(int i=x;i>0;i-=lowbit(i)){
        res+=tree[i];
    }
    return res;
}
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        cin>>N;
        memset(tree,0,sizeof(tree));
        vector<int> a(N);
        long long ans=0;
        for(int i=0;i<N;i++){
            cin>>a[i];
        }
        auto temp=a;
        sort(temp.begin(),temp.end());
        for(int &i:a){
            i=lower_bound(temp.begin(),temp.end(),i)-temp.begin()+1;
        }
        for(int i=N-1;i>=0;i--){
            ans+=query(a[i]);
            add(a[i],1);
        }
        cout<<ans<<endl;
    }
    return 0;
}