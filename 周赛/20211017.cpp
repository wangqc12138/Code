#include "head.h"
/* 

 */
class Bank {
public:
    Bank(vector<long long>& balance) {
        ump.clear();
        int index=1;
        for(auto i:balance){
            ump[index++]=i;
        }
    }
    
    bool transfer(int account1, int account2, long long money) {
        if(ump[account1]<money){
            return false;
        }
        ump[account1]-=money;
        ump[account2]+=money;
    }
    
    bool deposit(int account, long long money) {
        ump[account]+=money;
    }
    
    bool withdraw(int account, long long money) {
        if(ump[account]<money){
            return false;
        }
        ump[account]-=money;
    }
private:
    unordered_map<int,int> ump;
};


class Solution {
public:
    unordered_map<int,int> ump;
    int temp=0,maxn=-1;
    int countMaxOrSubsets(vector<int>& nums) {
        dfs(nums,0);
        return ump[maxn];
    }
    void dfs(vector<int>& nums,int index){
        if(index==nums.size()){
            ump[temp]++;
            maxn=max(maxn,temp);
            return;
        }
        int k=temp;
        temp=temp||nums[index];
        dfs(nums,index+1);
        temp=k;
        dfs(nums,index+1);
    }
};