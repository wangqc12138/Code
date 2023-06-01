#include <bits/stdc++.h>
using namespace std;
int main(){
    //freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        int M,N;
        cin>>M>>N;
        int a[M];
        for(int i=0;i<M;i++){
            cin>>a[i];
        }
        sort(a,a+M,greater<int>());
        for(int i=0;i<M;i++){
            if(i!=0){
                a[i]+=a[i-1];
            }
        }
        for(int i=0;i<N;i++){
            int k=0;
            cin>>k;
            if(k>a[M-1]){
                cout<<"-1"<<endl;
                continue;
            }
            int len=lower_bound(a,a+M-1,k)-a;
            cout<<len+1<<endl;
        }
    }
    return 0;
}
