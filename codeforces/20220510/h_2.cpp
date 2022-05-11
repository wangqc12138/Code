//这个问题可以用归并排序找逆序对
//这个问题还可以用树状数组来解决
//此处使用树状数组
#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        int N;
        cin>>N;
        int a[N];
        long long ans=0;
        for(int i=0;i<N;i++){
            cin>>a[i];
        }
        
        cout<<ans<<endl;
    }
    return 0;
}
