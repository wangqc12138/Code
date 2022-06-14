#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    while(T--){
        int n;
        vector<int> vec(n);
        for(int i=0;i<n;i++){
            cin>>vec[i];
            vec[i]%=10;
        }
        sort(vec.begin(),vec.end());
        int flag=false;
        for(int i=0;i<n-2;i++){
            int target=3;
            for(int j=0;j<3;j++,target+=10){
                if(j==0&&vec[i]>3){
                    continue;
                }
                int l=i+1,r=n-1;
                if(vec[i]+vec[l]>target){
                    continue;
                }
                while(l<r){
                    if(vec[l]+vec[r]==target-vec[i]){
                        flag=true;
                        break;
                    }else if(vec[l]+vec[r]<target-vec[i]){
                        l++;
                    }else{
                        r--;
                    }
                }
                if(flag){
                    break;
                }
            }
            if(flag){
                break;
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