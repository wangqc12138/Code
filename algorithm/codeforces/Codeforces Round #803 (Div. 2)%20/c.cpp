#include <bits/stdc++.h>
using namespace std;
void solve(){
    int n;cin>>n;
    vector<int> arr;
    int positive=0,negative=0,zero=0;
    for(int i=0;i<n;i++){
        int x;cin>>x;
        if(x<0){negative++;}
        else if(x>0){positive++;}
        else{zero++;}
        if(x!=0||zero>1){arr.emplace_back(x);}
    }
    if(negative>2||positive>2){cout<<"no\n";return;}
    for(int i=0;i<arr.size();i++){
        for(int j=i+1;j<arr.size();j++){
            for(int k=j+1;k<arr.size();k++){
                bool flag=false;
                for(int l=0;l<arr.size();l++){
                    if(arr[i]+arr[j]+arr[k]==arr[l]){
                        flag=true;
                        break;
                    }
                }
                if(!flag){cout<<"no\n";return;}
            }
        }
    }
    cout<<"yes\n";
}
int main(){
    int tt;cin>>tt;
    for(int i=0;i<tt;i++){solve();}
    return 0;
}
