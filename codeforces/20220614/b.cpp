#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        int n;
        int a[n];
        map<int,int> mp;
        for(int i=0;i<n;i++){
            cin>>a[i];
            mp[a[i]]++;
        }
        int i1=0,i2=0;
        for(auto [x,y]:mp){
            if(y%2==1){
                i1++;
            }else{
                i2++;
            }
        }
        if(i2%2==0){
            cout<<i1+i2<<endl;
        }else{
            cout<<i1+i2-1<<endl;
        }
    }
    return 0;
}