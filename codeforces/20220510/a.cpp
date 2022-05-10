#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int M;
    cin>>M;
    while(M--){
        string str;
        cin>>str;
        int flag=0;
        for(int i=0;i<6;i++){
            if(i<3){
                flag+=str[i]-'0';
            }else{
                flag-=str[i]-'0';
            }
        }
        if(flag==0){
            cout<<"YES"<<endl;
        }else{
            cout<<"NO"<<endl;
        }
    }
    return 0;
}
