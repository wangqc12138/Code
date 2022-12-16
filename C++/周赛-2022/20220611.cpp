#include "head.h"
class Solution {
public:
    bool matchReplacement(string s, string sub, vector<vector<char>>& mappings) {
        int m=s.size(),n=sub.size();
        map<char,set<char>> mst;
        for(auto c:sub){
            mst[c].emplace(c);
        }
        for(auto v:mappings){
            if(!mst.count(v[0])){
                continue;
            }
            mst[v[0]].emplace(v[1]);
        }
        for(int i=0;i<m-n;i++){
            int j=0;
            for(;j<n;j++){
                if(!mst[sub[j]].count(s[i+j])){
                    break;
                }
            }
            if(j==n){
                return true;
            }
        }
        return false;
    }
};
class Solution {
public:
    long long countSubarrays(vector<int>& nums, long long k) {
        vector<int> sum(1,0);
        for(int i=0;i<nums.size();i++){
            sum.emplace_back(sum[i]+nums[i]);
        }
        long long res=0;
        int n=nums.size();
        for(int i=1;i<=n;i++){
            if(sum[i]-sum[i-1]>=k){
                continue;
            }
            int l=i,r=n;
            while(l<r){
                int mid=(r+l)/2;
                if((long long)(sum[mid]-sum[i-1])*(mid-i+1)>=k){
                    r=mid-1;
                }else{
                    l=mid;
                }
            }
            res+=l-r;
        }
        return res;
    }
};