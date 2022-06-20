#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        int arr[n];
        for(int i=0;i<n;i++){
            cin>>arr[i];
        }
        long long k=0,m=arr[0];
        for(int i=1;i<n;i++){
            k+=abs(arr[i]-arr[i-1]);
            //当小于前一个元素时，前面的统一减小为这个元素，但是有可能这个元素在前面的某些操作里已经减小过了所以都按差值来计算，m只可能变得更小，。减小差值
            if(arr[i]<arr[i-1]){
                m+=arr[i]-arr[i-1];
            }
        }
        cout<<(long long)k+abs(m)<<endl;
    }
    return 0;
}