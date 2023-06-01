#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        int M,N;
        cin>>M>>N;
        int m[M][N];
        map<int,int> a,b,c,d;
        for(int i=0;i<M;i++){
            int s=0;
            for(int j=0;j<N;j++){
                cin>>m[i][j];
                s+=m[i][j];
            }
            a[i]=s;
        }
        for(int j=0;j<N;j++){
            for(int i=0;i<M;i++){
                b[j]+=m[i][j];
            }
        }
        for(int I=0;I<M;I++){
            for(int i=I,j=0;i<M&&j<N;i++,j++){
                c[-I]+=m[i][j];
            }
            for(int i=I,j=0;i>=0&&j<N;i--,j++){
                d[I]+=m[i][j];
            }
        }
        for(int J=1;J<N;J++){
            for(int i=0,j=J;i<M&&j<N;i++,j++){
                c[J]+=m[i][j];
            }
            for(int i=M-1,j=J;i>=0&&j<N;i--,j++){
                d[M-1+J]+=m[i][j];
            }
        }
        int ans=0;
        for(int i=0;i<M;i++){
            for(int j=0;j<N;j++){
                ans=max(ans,a[i]+b[j]+c[j-i]+d[j+i]-m[i][j]*3);
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
