#include "head.h"
/* 
给你三个整数数组 nums1、nums2 和 nums3 ，请你构造并返回一个 不同 数组，且由 至少 在 两个 数组中出现的所有值组成。
数组中的元素可以按 任意 顺序排列。 
 */
class Solution {
public:
    vector<int> twoOutOfThree(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3) {
		set<int> s1(nums1.begin(),nums1.end());
		set<int> s2(nums2.begin(),nums2.end());
		set<int> s3(nums3.begin(),nums3.end());
		unordered_map<int,int> ump;
		vector<int> res;
		for(int i:s1){
			ump[i]++;
		}
		for(int i:s2){
			ump[i]++;
		}
		for(int i:s3){
			ump[i]++;
		}
		for(auto [x,y]:ump){
			if(y>=2){
				res.emplace_back(x);
			}
		}
		return res;
    }
};
/* 
给你一个大小为 m x n 的二维整数网格 grid 和一个整数 x 。每一次操作，你可以对 grid 中的任一元素 加 x 或 减 x 。

单值网格 是全部元素都相等的网格。

返回使网格化为单值网格所需的 最小 操作数。如果不能，返回 -1 。
 */
class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
		vector<int> num;
		for(auto vec:grid){
			for(auto i:vec){
				num.emplace_back(i);
			}
		}
		sort(num.begin(),num.end());
		int n=num.size();
		if(n%2==1){
			int mid=num[n/2];
			for(int i:num){
				
			}
		}else{

		}
    }
};