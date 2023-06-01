#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        int n;
        string s;
        cin>>n>>s;
        string ans=s;
        if(s[0]=='9'){
            string dest="";
            for(int i=0;i<n;i++){
                if(i==0){
                    ans[i]='1';
                }else{
                    ans[i]='0';
                }
                dest+='1';
            }
            dest+='1';
            string str="10"+s.substr(1);
            for(int i=n;i>=1;i--){
                if(dest[i]<str[i]){
                    dest[i-1]--;
                    ans[i-1]+=dest[i]-str[i]+10;
                }else{
                    ans[i-1]+=dest[i]-str[i];
                }
            }
        }else{
            string dest="";
            for(int i=0;i<n;i++){
                dest+='9';
            }
            string str=s;
            for(int i=n-1;i>=0;i--){
                if(dest[i]<str[i]){
                    dest[i-1]--;
                    ans[i]=10+dest[i]-str[i]+'0';
                }else{
                    ans[i]=dest[i]-str[i]+'0';
                }
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}