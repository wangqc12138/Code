#include <bits/stdc++.h>
using namespace std;
unordered_map<int,int> ump,used;
int sum=0;
void dfs(vector<int> &nums,int index,int t){
    if(t==0){
        sum++;
        for(auto [i,j]:used){
            ump[i]++;
        }
        return;
    }
    if(t<0){
        return;
    }
    for(int i=index;i<nums.size();i++){
        used[nums[i]]++;
        dfs(nums,i,t-nums[i]);
        if(--used[nums[i]]==0){
            used.erase(nums[i]);
        }
    }
}
int main(){
    int n,t;
    cin>>n;
    cin>>t;
    vector<int> nums(n);
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }
    dfs(nums,0,t);
    for(int i=0;i<n;i++){
        cout<<sum-ump[nums[i]]<<endl;
    }
}
