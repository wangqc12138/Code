#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int n;
    cin>>n;
    map<int,int> mp;
    for(int i=0;i<n;i++){
        int k;
        cin>>k;
        mp[k]+=k;
    }
    int m1=0,m2=0;
    for(int i=1;i<=100000;i++){
        int m=max(mp[i]+m1,m2);
        m1=m2;
        m2=m;
    }
    cout<<m2<<endl;;
    return 0;
}