#include <bits/stdc++.h>
using namespace std;
int main(){
    int N,A,B;
    cin>>N>>A>>B;
    for(int i=0;i<N;i++){
        for(int j=0;j<A;j++){
            for(int k=0;k<N;k++){
                if(k%2==0){
                    for(int l=0;l<B;l++){
                        cout<<'.';
                    }
                }else{
                    for(int l=0;l<B;l++){
                        cout<<'#';
                    }
                }
            }
            cout<<endl;
        }
    }
    return 0;
}