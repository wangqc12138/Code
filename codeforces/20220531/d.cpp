#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int M;
    cin>>M;
    while(M--){
        int N;
        vector<int> vec(N);
        for(int i=0;i<N;i++){
            cin>>vec[i];
        }
        int i=0;
        while(vec[i]==0){
            i++;
        }
        if(vec[i]>0){
            i++;
        }
        bool flag=true;
        for(;i<N;i++){
            if(vec[i]>0){
                flag=false;
                break;
            }
            if(i-1>=0&&i+1<N){
                if(abs(vec[i])<min(vec[i-1],vec[i+1])){
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
