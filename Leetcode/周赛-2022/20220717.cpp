#include "head.h"
class Solution {
public:
    vector<int> numberOfPairs(vector<int>& nums) {
        map<int,int> mp;
        for(auto i:nums){
            mp[i]++;
        }
        vector<int> res(2,0);
        for(auto [x,y]:mp){
            res[0]+=y/2;
            if(y%2){
                res[1]++;
            }
        }
        return res;
    }
};
class Solution {
public:
    int maximumSum(vector<int>& nums) {
        map<int,set<int,greater<int>()>> mp;
        for(int i:nums){
            string t=to_string(i);
            int k=0;
            for(auto c:t){
                k+=c-'0';
            }
            mp[k].emplace(i);
        }
        int res=-1;
        for(auto [x,y]:mp){
            if(y.size()>1){
                sort(y.begin(),y.end(),greater<int>());
                res=max(res,*y.begin()+*(y.begin()++));
            }
        }
        return res;
    }
};
class Solution {
public:
    vector<int> smallestTrimmedNumbers(vector<string>& nums, vector<vector<int>>& queries) {
        vector<int> res;
        int len=nums[0].size();
        int index=0;
        auto cmp=[](auto a,auto b){if(a.frst<b.first||a.frst==b.first&&a.second<b.second){return true;}};
        for(auto vec:queries){
            vector<pair<int,int>> tvec;
            for(int i=0;i<nums.size();i++){
                tvec.emplace_back(stoi(nums[0].substr(len-vec[1])));
            }
            sort(tvec.begin(),tvec.end(),cmp);
            res.emplace_back(tvec[vec[0]]);
        }
        return res;
    }
};
class Solution {
public:
    int minOperations(vector<int>& nums, vector<int>& numsDivide) {
        int n=numsDivide.size(),g;
        if(n==1){
            g=numsDivide[0];
        }else{
            g=__gcd(numsDivide[0],numsDivide[1]);
        }
        for(int i=2;i<n;i++){
            g=__gcd(numsDivide[i],g);
            if(g==1){
                break;
            }
        }
        sort(nums.begin(),nums.end());
        int res=0;
        //cout<<g<<endl;
        for(int i:nums){
            if(i>g){
                g=-1;
                break;
            }
            if(g%i==0){
                break;
            }else{
                res++;
            }
        }
        if(g==-1){
            return -1;
        }
        return res;
    }
};