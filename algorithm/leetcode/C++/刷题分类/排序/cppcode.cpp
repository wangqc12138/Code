#include "head.h"
/* 
实现获取 下一个排列 的函数，算法需要将给定数字序列重新排列成字典序中下一个更大的排列。

如果不存在下一个更大的排列，则将数字重新排列成最小的排列（即升序排列）。

必须 原地 修改，只允许使用额外常数空间。
31
c++中的next_partition算法
 */
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n=nums.size(),i=n-2,j=n-1;
		for(;i>=0;i--){
			if(nums[i]<nums[i+1]){
				break;
			}
		}
		if(i==-1){
			for(int k=0;k<n/2;k++){
				swap(nums[k],nums[n-1-k]);
			}
			return;
		}
		for(;j>i;j--){
			if(nums[j]>nums[i]){
				swap(nums[i],nums[j]);
				break;
			}
		}
		for(int k=0;k<(n-i)/2;k++){
			swap(nums[i+1+k],nums[n-1-k]);
		}
    }
};
/* 
归并==逆序对
 */