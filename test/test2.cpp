#include <map>
#include <set>
#include <iostream>
using namespace std;
void print(int ans[],int index,int maxn){
    cout<<index<<endl<<maxn<<endl;
    for(int i=0;i<index;i++){
        cout<<ans[i]<<" ";
    }
    cout<<endl;
}
void help1(int arr[],int m,int n){
    set<int> st;
    int temp[n];
    int ans[m];
    int maxn=0,index=0;
    for(int i=0;i<m;i++){
        if(st.count(arr[i])){
            maxn=max(maxn,++temp[arr[i]]);
        }else{
            maxn=max(maxn,temp[arr[i]]=1);
        }
        st.emplace(arr[i]);
    }
    for(auto i:st){
        if(temp[i]==maxn){
            ans[index++]=i;
        }
    }
    print(ans,index,maxn);
}
void help2(int arr[],int m,int n){
    map<int,int> mp;
    int maxn=0,index=0;
    for(int i=0;i<m;i++){
        maxn=max(maxn,++mp[arr[i]]);
    }
    int ans[m];
    for(auto [x,y]:mp){
        if(y==maxn){
            ans[index++]=x;
        }
    }
    print(ans,index,maxn);
}
int main(){
    int m=15,n=10;
    int arr[m];
    for(int i=0;i<m;i++){
        arr[i]=i%n;
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    help1(arr,m,n);
    help2(arr,m,n);
    return 0;
}
