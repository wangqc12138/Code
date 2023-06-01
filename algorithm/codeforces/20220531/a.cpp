#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int M,N;
    cin>>M;
    while(M--){
        cin>>N;
        int even=0,odd=0;
        for(int i=0;i<N;i++){
            int k;
            cin>>k;
            if(k%2){
                odd++;
            }else{
                even++;
            }
        }
        cout<<min(odd,even)<<endl;
    }
    return 0;
}
