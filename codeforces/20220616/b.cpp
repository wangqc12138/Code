#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        string str;
        cin>>str;
        int ans=n;
        for(int i=0;i<n;i++){
            if(str[i]=='0'){
                for(int j=i-1;i>=0;i--){
                    if(str[j]=='0'){
                        break;
                    }else{
                        ans++;
                    }
                }
            }else{
                for(int j=i-1;i>=0;i--){
                    if(str[j]=='1'){
                        break;
                    }else{
                        ans++;
                    }
                }
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}