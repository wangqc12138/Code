#include "head.h"
/* 
大餐 是指 恰好包含两道不同餐品 的一餐，其美味程度之和等于 2 的幂。

你可以搭配 任意 两道餐品做一顿大餐。

给你一个整数数组 deliciousness ，其中 deliciousness[i] 是第 i​​​​​​​​​​​​​​ 道餐品的美味程度，返回你可以用数组中的餐品做出的不同 大餐 的数量。
结果需要对 109 + 7 取余。

注意，只要餐品下标不同，就可以认为是不同的餐品，即便它们的美味程度相同。
1711

    1 <= deliciousness.length <= 105
    0 <= deliciousness[i] <= 220
进阶版的二数之和
 */
class Solution {
public:
    int countPairs(vector<int>& deliciousness) {
		unordered_map<int,int> ump;
		int res=0;
		for(int num:deliciousness){
			for(int i=0;i<=21;i++){
				int sum=pow(2,i);
				if(ump.count(sum-num)){
					res+=ump[sum-num];
				}
				res%=1000000007;
			}
			ump[num]++;
		}
		return res;
    }
};
/* 
给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。

你可以按任意顺序返回答案。
1
 */
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
		unordered_map<int,int> ump;
		//unordered_set<int> uset;
		int i=0;
		for(int num:nums){
			if(ump.count(target-num)){
				return {i,ump[target-num]};
			}
			ump.emplace(num,i++);
		}
		return {};
    }
};