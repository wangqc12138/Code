#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;

    long long zeroFilledSubarray(vector<int>& nums) {
        int len=0;
        long long res=0;
        for(int i=0;i<nums.size();i++){
            if(nums[i]==0){
                len++;
            }else{
                res+=(long long)len*(len+1)/2;
                len=0;
            }
        }
        if(len!=0){
            res+=(long long)len*(len+1)/2;
        }
        return res;
    }
void solve(){
    int a;
    vector<int> nums;
    for(;cin>>a;){
        nums.emplace_back(a);
    }
    for(int i:nums){
        cout<<i<<" ";
    }
    cout<<endl;
    cout<<zeroFilledSubarray(nums)<<endl;;
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    solve();    
    return 0;
}
