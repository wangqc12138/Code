#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    string s1,s2;
    cin>>s1>>s2;
    string s="";
    for(int i=0;i<3;i++){
        int k1=s1[i]-'0';
        int k2=s2[i]-'0';
        s+=to_string((k1+k2)%3);
    }
    cout<<s<<endl;
    return 0;
}
