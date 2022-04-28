#include "head.h"
/* 
给你一个整数数组 nums 和一个整数 k ，请你返回数对 (i, j) 的数目，满足 i < j 且 |nums[i] - nums[j]| == k 。

|x| 的值定义为：

    如果 x >= 0 ，那么值为 x 。
    如果 x < 0 ，那么值为 -x 。
 */
class Solution {
public:
    int countKDifference(vector<int>& nums, int k) {
		int res=0;
		for(int i=0;i<nums.size();i++){
			for(int j=i+1;j<nums.size();j++){
				if(abs(nums[i]-nums[j])==k){
					res++;
				}
			}
		}
		return res;
    }
};
/* 
一个整数数组 original 可以转变成一个 双倍 数组 changed ，转变方式为将 original 中每个元素 值乘以 2 加入数组中，然后将所有元素 随机打乱 。

给你一个数组 changed ，如果 change 是 双倍 数组，那么请你返回 original数组，否则请返回空数组。original 的元素可以以 任意 顺序返回。
 */
/* class Solution {
public:
    vector<int> findOriginalArray(vector<int>& changed) {
		unordered_map<int,int> ump;
		for(auto i:changed){
			ump[i]++;
		}
		vector<int> res;
		for(auto [x,y]:ump){
			if(x==0){
				if(y%2!=0){
					return {};
				}else{
					for(int i=0;i<y/2;i++){
						res.emplace_back(0);
					}
				}
			}
			if(!ump.count(2*x)||ump[2*x]<y){
				return {};
			}
			for(int i=0;i<y;i++){
				res.emplace_back(x);
			}
			ump[x]=0;
			ump[2*x]-=y;
		}
		return res;
    }
}; */
/* 

 */