#include "head.h"
class Solution {
public:
    long long waysToBuyPensPencils(int total, int cost1, int cost2) {
       long long res=0;
       for(int i=0;i<=total/cost1;i++){
           int e=total-i*cost1;
           res+=e/cost2;
       }
       return res; 
    }
};
/* 
一个 ATM 机器，存有 5 种面值的钞票：20 ，50 ，100 ，200 和 500 美元。初始时，ATM 机是空的。用户可以用它存或者取任意数目的钱。

取款时，机器会优先取 较大 数额的钱。

    比方说，你想取 $300 ，并且机器里有 2 张 $50 的钞票，1 张 $100 的钞票和1 张 $200 的钞票，那么机器会取出 $100 和 $200 的钞票。
    但是，如果你想取 $600 ，机器里有 3 张 $200 的钞票和1 张 $500 的钞票，那么取款请求会被拒绝，因为机器会先取出 $500 的钞票，然后无法取出剩余的 $100 。
    注意，因为有 $500 钞票的存在，机器 不能 取 $200 的钞票。

请你实现 ATM 类：

    ATM() 初始化 ATM 对象。
    void deposit(int[] banknotesCount) 分别存入 $20 ，$50，$100，$200 和 $500 钞票的数目。
    int[] withdraw(int amount) 返回一个长度为 5 的数组，分别表示 $20 ，$50，$100 ，$200 和 $500 钞票的数目，并且更新 ATM 机里取款后钞票的剩余数量。
    如果无法取出指定数额的钱，请返回 [-1] （这种情况下 不 取出任何钞票）。

 */
class ATM {
public:
    ATM() {
        money=vector<long long>(5,0);
        mp[4]=500;
        mp[3]=200;
        mp[2]=100;
        mp[1]=50;
        mp[0]=20;
    }
    
    void deposit(vector<int> banknotesCount) {
        for(int i=0;i<5;i++){
            money[i]+=banknotesCount[i];
        }
    }
    
    vector<int> withdraw(int amount) {
        vector<int> res(5,0);
        int i=4;
        for(;i>=0;i--){
            if(money[i]){
                if(amount>=mp[i]){
                    amount-=mp[i];
                    money[i]--;
                    res[i]++;
                }
                break;
            }
        }
        if(i==-1){
            return {-1};
        }
        for(;i>=0&&amount;i--){
            if(money[i]==0||amount<mp[i]){
                continue;
            }
            int k=min(amount/mp[i],money[i]);
            amount-=k*mp[i];
            money[i]-=k;
            res[i]+=k;
        }
        if(amount!=0){
            for(int i=0;i<5;i++){
                money[i]+=res[i];
            }
            return {-1};
        }
        // for(int i:money){
        //     cout<<i<<" ";
        // }
        // cout<<endl;
        return res;
    }
private:
    vector<long long> money;
    map<long long,long long> mp;
};
class Solution {
public:
    int maximumScore(vector<int>& scores, vector<vector<int>>& edges) {
        map<int,vector<int>> next;
        for(auto vec:edges){
            next[vec[0]].emplace_back(vec[1]);
            next[vec[1]].emplace_back(vec[0]);
        }
        int n=scores.size();
        queue<int> mq;
        for(int i=0;i<n;i++){
            mq.emplace(i);
        }
    }
};