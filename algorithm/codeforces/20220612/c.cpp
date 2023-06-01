#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        string str1,str2;
        cin>>str1>>str2;
        bool flag=true;
        for(int i=0;i<n;i++){
            if(str1[i]==str2[i]){
                continue;
            }else if(i==n-1){
                flag=false;
                break;
            }else{
                if(str1[i]=='a'||str1[i]=='b'){
                    int j=i+1;
                    for(;j<n;j++){
                        if(str1[j]==str1[i]+1){
                            swap(str1[i],str1[j]);
                            break;
                        }else if(str1[j]!=str1[i]){
                            flag=false;
                            break;
                        }
                    }
                    if(!flag||j==n){
                        flag=false;
                        break;
                    }
                }else{
                    flag=false;
                    break;
                }
            }
        }
        if(flag){
            cout<<"YES"<<endl;
        }else{
            cout<<"NO"<<endl;
        }
    }
    return 0;
}