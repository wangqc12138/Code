#include <bits/stdc++.h>
using namespace std;
void solve(){
    int M,N;
    cin>>M>>N;
    int m=max(M,N);
    int n=min(M,N);
    int arr[m][n];
    arr[0][0]=1;
    arr[0][1]=0;
    int k=0;
    for(int j=2;j<n;j+=2){
        arr[0][j]=arr[0][j-1];
        arr[0][j+1]=arr[0][j-2];
    }
    for(int i=1;i<m;i++){
        for(int j=0;j<n;j++){
            int k=0;
            if(i>1){
                k+=arr[i-2][j]!=arr[i-1][j];
            }
            if(j!=0){
                k+=arr[i-1][j-1]!=arr[i-1][j];
            }
            if(j!=n-1){
                k+=arr[i-1][j+1]!=arr[i-1][j];
            }
            if(k==2){
                arr[i][j]=arr[i-1][j];
            }else{
                arr[i][j]=(arr[i-1][j]+1)%2;
            }
        }
    }
    if(M>=N){
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                cout<<arr[i][j]<<" ";
            }
            cout<<endl;
        }
    }else{
        for(int j=0;j<n;j++){
            for(int i=0;i<m;i++){
                cout<<arr[i][j]<<" ";
            }
            cout<<endl;
        }
    }
}
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}