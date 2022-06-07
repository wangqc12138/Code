#include <bits/stdc++.h>
using namespace std;
unordered_map<int,int> ump;
unordered_set<int> ust;
int sum=0;
void dfs(vector<int> &nums,int index,int t){
    if(t==0){
        sum++;
        for(auto i:ust){
            ump[i]++;
        }
        return;
    }
    if(t<0){
        return;
    }
    for(int i=index;i<nums.size();i++){
        auto temp=ust;
        ust.emplace(nums[i]);
        dfs(nums,i,t-nums[i]);
        ust=temp;
    }
}
int main(){
    int n,t;
    cin>>n>>t;
    vector<int> nums(n);
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }
    auto temp=nums;
    sort(temp.begin(),temp.end());
    dfs(temp,0,t);
    for(int i=0;i<n;i++){
        cout<<sum-ump[nums[i]]<<endl;
    }
}
