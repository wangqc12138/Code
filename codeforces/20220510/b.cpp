#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int M;
    cin>>M;
    while(M--){
        int N;
        cin>>N;
        int a[N];
        int minn=10000001;
        for(int i=0;i<N;i++){
            cin>>a[i];
            minn=min(a[i],minn);
        }
        int ans=0;
        for(int i=0;i<N;i++){
            ans+=a[i]-minn;
        }
        cout<<ans<<endl;
    }
    return 0;
}
