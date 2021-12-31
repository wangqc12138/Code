
#include "head.h"
/*
给定一个循环数组（最后一个元素的下一个元素是数组的第一个元素），输出每个元素的下一个更大元素。数字 x 的下一个更大的元素是按数组遍历顺序，这个数字之后的第一个比它更大的数，这意味着你应该循环地搜索它的下一个更大的数。如果不存在，则输出 -1。
503
*/
/*
给你一个整数数组 nums ，数组中共有 n 个整数。132 模式的子序列 由三个整数 nums[i]、nums[j] 和 nums[k] 组成，并同时满足：i < j < k 和 nums[i] < nums[k] < nums[j] 。
如果 nums 中存在 132 模式的子序列 ，返回 true ；否则，返回 false 。
进阶：很容易想到时间复杂度为 O(n^2) 的解决方案，你可以设计一个时间复杂度为 O(n logn) 或 O(n) 的解决方案吗？
456
*/
//[3,5,0,3,4]
class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        int n=nums.size(),two=INT_MIN;
        stack<int> ms;
        for(int i=n-1;i>=0;i--){
            if(nums[i]>=two){
                while(!ms.empty()&&nums[i]>nums[ms.top()]){
                    two=nums[ms.top()];
                    ms.pop();
                }
                ms.push(i);
            }else{
                return true;
            }

        }
        return false;
    }
};
/*
给定一个直方图(也称柱状图)，假设有人从上面源源不断地倒水，最后直方图能存多少水量?直方图的宽度为 1。
面试题 17.21. 直方图的水量
*/
class Solution {
public:
    int trap(vector<int>& height) {
		stack<int> sk;
		int res=0;
		for(int i=0;i<height.size();i++){
			while(!sk.empty()&&height[sk.top()]<height[i]){
				int j=sk.top();
				sk.pop();
				if(sk.empty()){
					break;
				}
				int k=sk.top();
                int h=min(height[i],height[k])-height[j];
                res+=(i-k-1)*h;
			}
			sk.emplace(i);
		}
		return res;
    }
};
/* 
Leetcode 42：接雨水（超详细的解法！！！）

Leetcode 496：下一个更大元素 I（超详细的解法！！！）

Leetcode 503：下一个更大元素 II（超详细的解法！！！）

Leetcode 739：每日温度（超详细的解法！！！）

Leetcode 901：股票价格跨度（超详细的解法！！！）

Leetcode 239：滑动窗口最大值（超详细的解法！！！）

Leetcode 84：柱状图中最大的矩形（超详细的解法！！！）

907 1019 316 402 581 1118
 */