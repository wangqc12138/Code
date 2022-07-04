#include <bits/stdc++.h>
using namespace std;
void solve(){
    int M,N;
    cin>>M>>N;
    int m=max(M,N);
    int n=min(M,N);
    int arr[m][n];
    for(int j=0;j<n;j++){
        arr[0][j]=j%2;
    }
    for(int i=1;i<m;i++){
        for(int j=0;j<n;j++){
            if(j==0||j==n-1){
                arr[i][j]=(arr[i-1][j]+1)%2;
            }else{
                int k=0;
                if(i>1){
                    k+=arr[i-2][j]!=arr[i-1][j];
                }
                k+=arr[i-1][j-1]!=arr[i-1][j];
                k+=arr[i-1][j+1]!=arr[i-1][j];
                if(k==2){
                    arr[i][j]=(arr[i-1][j]+1)%2;
                }else{
                    arr[i][j]=arr[i-1][j];
                }
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
        
    }
    return 0;
}