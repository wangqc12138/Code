#include "head.h"
class Solution {
public:
    long long minimumReplacement(vector<int>& nums) {
        int n=nums.size();
        int next=nums[n-1];
        long long res=0;
        for(int i=n-2;i>=0;i--){
            if(nums[i]<=next){
                next=nums[i];
                continue;
            }else{
                if(nums[i]%next==0){
                    res+=nums[i]/next-1;
                }
                int t=nums[i]/next;
                next=nums[i]%(t+1);
                res+=t;
            }
        }
        return res;
    }
};