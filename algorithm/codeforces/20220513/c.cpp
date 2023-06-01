#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int M;
    cin>>M;
    while(M--){
       string str;
       cin>>str;
       int N=str.size();
       int a[N][2],b[N][2];
       int m=0,n=0;
       for(int i=0;i<N;i++){
           if(str[i]=='1'){
               m++;
           }else{
               n++;
           }
       }
       int c=0,d=0;
       for(int i=0;i<N;i++){
           if(str[i]=='1'){
               c++;
           }else{
               d++;
           }
           a[i][0]=n-d;
           a[i][1]=c;
       }
       c=0,d=0;
       for(int i=N-1;i>=0;i--){
           if(str[i]=='1'){
               c++;
           }else{
               d++;
           }
           b[i][0]=n-d;
           b[i][1]=c;
       }
       int c=m,d=n;
       int ans=m+n;
       for(int i=0;i<N;i++){
           int c=min(c,a[i][0]);
           int d=min(d,a[i][1]);
           for(int j=i+1;j<n;j++){
               ans=min(max(c,b[i][0]),ans);
               ans=min(max(d,b[i][1]),ans);
           }
       }
       cout<<ans<<endl;
    }
    return 0;
}
