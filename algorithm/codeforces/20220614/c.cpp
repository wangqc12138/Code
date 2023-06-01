#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        vector<string> vstr(8); 
        int flag=0;
        int I,J;
        for(int i=0;i<8;i++){
            cin>>vstr[i];
            int t=0,k=0;
            for(int j=0;j<8;j++){
                if(vstr[i][j]=='#'){
                    k=j;
                    t++;
                }
            }
            if(t==2&&flag==0){
                flag=1;
            }
            if(t==1&&flag==1){
                I=i+1;
                J=k+1;
                flag=2;
            }
        }
        cout<<I<<" "<<J<<endl;
    }
    return 0;
}