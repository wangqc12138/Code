#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int M;
    cin>>M;
    while(M--){
        int m,n;
        cin>>m>>n;
        vector<string> vstr(m);
        for(int i=0;i<m;i++){
            cin>>vstr[i];
        }
        int a=-1,b=-1;
        for(int j=0;j<n;j++){
            for(int i=0;i<m;i++){
                if(vstr[i][j]=='R'){
                    a=i,b=j;
                    break;
                }
            }
            if(a!=-1&&j!=-1){
                break;
            }
        }
        for(int i=a-1;i>=0;i--){
            for(int j=b;j<n;j++){
                if(vstr[i][j]=='R'){
                    cout<<"NO"<<endl;
                    a=-1,b=-1;
                    break;
                }
            }
            if(a==-1&&b==-1){
                break;
            }
        }
        if(a!=-1&&b!=-1){
            cout<<"YES"<<endl;
        }
    }
    return 0;
}
