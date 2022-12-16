#include "head.h"
class Solution {
public:
    int findMiddleIndex(vector<int>& nums) {
        int n=nums.size();
        vector<int> sum(n+1,0);
        for(int i=1;i<=n;i++){
            sum[i]=sum[i-1]+nums[i-1];
        }
        for(int i=0;i<n;i++){
            if(sum[n]-sum[i+1]==sum[i]){
                return i;
            }
        }
        return -1;
    }
};
class Solution {
public:
    vector<vector<int>> findFarmland(vector<vector<int>>& land) {
        vector<vector<int>> res;
        int m=land.size(),n=land[0].size();
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(land[i][j]==1){
                    vector<int> temp={i,j};
                    vector<int> ret=dfs(land,i,j);
                    temp.emplace_back(ret[0]);
                    temp.emplace_back(ret[1]);
                    res.emplace_back(temp);
                }
            }
        }
        return res;
    }
    vector<pair<int,int>> dir={{0,-1},{0,1},{-1,0},{1,0}};
    vector<int> dfs(vector<vector<int>>& land,int i,int j){
         int m=land.size(),n=land[0].size();
         if(i<0||j<0||i>=m||j>=n||land[i][j]!=1){
             return {-1,-1};
         }
         land[i][j]=2;
         int m1=0,m2=0;
        for(auto [x,y]:dir){
            vector<int> temp=dfs(land,i+x,y+j);
            m1=max(temp[0],m1);
            m2=max(temp[1],m2);
        }
        return {m1,m2};
    }
};
class LockingTree {
public:
    //[[[-1, 0, 0, 1, 1, 2, 2]], [2, 2], [2, 3], [2, 2], [4, 5], [0, 1], [0, 1]]
    LockingTree(vector<int>& parent) {
        for(int i=0;i<parent.size();i++){
            int p=parent[i];
            lockd[i]=-1;
            par[i]=p;
            chi[p].emplace_back(i);
        }
    }
    
    bool lock(int num, int user) {
        if(lockd[num]!=-1){
            return false;
        }
        lockd[num]=user;
        return true;
    }
    
    bool unlock(int num, int user) {
        if(lockd[num]!=user){
            return false;
        }
        lockd[num]=-1;
        return true;
    }
    
    bool upgrade(int num, int user) {
        if(lockd[num]!=-1){
            return false;
        }
        int p=num;
        while(par[p]!=-1){
            if(lockd[p]!=-1){
                return false;
            }
        }
        queue<int> mq;
        mq.emplace(num);
        bool res=false;
        while(!mq.empty()){
            int n=mq.front();
            mq.pop();
            if(lockd[n]!=-1){
                lockd[n]=1;
                res=true;
            }
            for(auto i:chi[n]){
                mq.emplace(i);
            }
        }
        return res;
    }
    map<int,int> lockd,par;
    map<int,vector<int>> chi;
};
//2、3、5、7、11、13、17、19、23、29
class Solution {
public:
    set<int> prim={2,3,5,7,11,13,17,19,23,29};
    set<int> fun(int i){
        if(i==1){
            return {};
        }
        if(i%4==0||i%9==0||i==25){
            return {-1};
        }
        if(prim.count(i)){
            return {i};
        }
        set<int> res;
        while(!prim.count(i)){
            for(auto j:prim){
                if(i%j==0){
                    res.emplace(j);
                    i/=j;
                    break;
                }
            }
        }
        res.emplace(i);
        return res;
    }
    vector<int> temp;
    map<int,set<int>> mp;
    int res=0;
    void dfs(vector<int>& nums,vector<int>& visit,set<int> s){
        if(s.size()!=0){
            if(s.size()==1&&s.count(0)){
            }else{
                res++;
            }
        }
        for(int i=0;i<nums.size();i++){
            if(visit[i]==1){
                continue;
            }
            bool flag=true;
            for(int j:mp[i]){
                if(s.count(j)){
                    flag=false;
                }
            }
            if(flag){
                for(int j:mp[i]){
                    s.emplace(j);
                }
                visit[i]=1;
                dfs(nums,visit,s);
                visit[i]=0;
                for(int j:mp[i]){
                    s.erase(j);
                }
            }
        }
    }
    int numberOfGoodSubsets(vector<int>& nums) {
        vector<int> vec;
        for(auto i:nums){
            mp[i]=fun(i);
            if(!mp[i].count(-1)){
                vec.emplace_back(i);
            }
        }    
        return res;
    }
};