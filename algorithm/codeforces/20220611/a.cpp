#include <bits/stdc++.h>
using namespace std;
int main(){
    //freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        int n,m,k;
        cin>>n>>m>>k;
        int p1=0,p2=0;
        string str1,str2;
        cin>>str1>>str2;
        sort(str1.begin(),str1.end());
        sort(str2.begin(),str2.end());
        int a=0,b=0;
        string ans="";
        while(p1<n&&p2<m){
            if(a==k){
                ans+=str2[p2++];
                a=0;
                b=1;
                continue;
            }else if(b==k){
                ans+=str1[p1++];
                a=1;
                b=0;
                continue;
            }
            if(str1[p1]<str2[p2]){
                ans+=str1[p1++];
                a++;
                b=0;
            }else if(str1[p1]>str2[p2]){
                ans+=str2[p2++];
                b++;
                a=0;
            }else{
                if(a==0){
                    ans+=str1[p1++];
                    a++;
                    b=0;
                }else{
                    ans+=str2[p2++];
                    b++;
                    a=0;
                }
            }
            
        }
        cout<<ans<<endl;
    }
    return 0;
}