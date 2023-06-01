#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int m;
    cin>>m;
    for(int i=0;i<m;i++){
        int n;
        cin>>n;
        int begin,end;
        for(int j=0;j<n;j++){
            int k;
            cin>>k;
            if(j==0){
                begin=k;
            }
            if(j==n-1){
                end=k;
            }
        }
        if(end-begin<=n+1){
            cout<<"YES"<<endl;
        }else{
            cout<<"NO"<<endl;
        }
    }
    return 0;
}