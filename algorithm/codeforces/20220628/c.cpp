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
        set<int> st,st1,st2;
        bool flag=false,zero=false;;
        for(int i=0;i<n;i++){
            cin>>arr[i];
            st.emplace(arr[i]);
            if(st.count(-arr[i])){
                flag=true;
            }
            if(arr[i]==0){
                zero=true;
            }
        }
        if(flag){
            cout<<"YES\n";
            continue;
        }
        sort(arr,arr+n);
        
        for(int i=0;i<n;i++){
            if(i>0&&arr[i]==arr[i-1]){
                continue;
            }
            int j=i+1;
            for(;j<n;j++){
                if(j>i+1&&arr[j]==arr[j-1]){
                    continue;
                }
                st1.emplace(arr[i]+arr[j]);
                st2.emplace(arr[i]-arr[j]);
                st2.emplace(arr[j]-arr[i]);
                if(zero&&st.count(arr[i]+arr[j])){
                    flag=true;
                    break;
                }
                if(!zero&&st2.count(arr[i]+arr[j])){
                    flag=true;
                    break;
                }
            }
            if(flag){
                break;
            }
        }
        if(flag){
            cout<<"YES\n";
        }else{
            cout<<"NO\n";
        }

    }
    return 0;
}