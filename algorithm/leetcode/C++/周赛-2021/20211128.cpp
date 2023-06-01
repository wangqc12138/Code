#include "head.h"
/* 
给你一个下标从 0 开始的整数数组 nums 以及一个目标元素 target 。

目标下标 是一个满足 nums[i] == target 的下标 i 。

将 nums 按 非递减 顺序排序后，返回由 nums 中目标下标组成的列表。
如果不存在目标下标，返回一个 空 列表。返回的列表必须按 递增 顺序排列。
 */
class Solution {
public:
    vector<int> targetIndices(vector<int>& nums, int target) {
		vector<int> res;
		int index=0;
		sort(nums.begin(),nums.end());
		for(auto i:nums){
			if(i==target){
				res.emplace_back(index);
			}
			index++;
		}
		return res;
    }
};
/* 
给你一个下标从 0 开始的数组 nums ，数组中有 n 个整数，另给你一个整数 k 。

半径为 k 的子数组平均值 是指：nums 中一个以下标 i 为 中心 且 半径 为 k 的子数组中所有元素的平均值，
即下标在 i - k 和 i + k 范围（含 i - k 和 i + k）内所有元素的平均值。
如果在下标 i 前或后不足 k 个元素，那么 半径为 k 的子数组平均值 是 -1 。

构建并返回一个长度为 n 的数组 avgs ，其中 avgs[i] 是以下标 i 为中心的子数组的 半径为 k 的子数组平均值 。

x 个元素的 平均值 是 x 个元素相加之和除以 x ，此时使用截断式 整数除法 ，即需要去掉结果的小数部分。

    例如，四个元素 2、3、1 和 5 的平均值是 (2 + 3 + 1 + 5) / 4 = 11 / 4 = 3.75，截断后得到 3 。
 */
class Solution {
public:
    vector<int> getAverages(vector<int>& nums, int k) {
		int right=0,left=0,n=nums.size();
		int sum=0;
		vector<int> res(n,-1);
		while(right<n){
			while(right<=2*k&&right<n){
				sum+=nums[right];
			}
			int mid=(right+left)/2;
			res[mid]=sum/(2*k+1);
			left++;
			right++;
			if(right<n){
				sum+=nums[right];
				sum-=nums[left];
			}
		}
		return res;
    }
};
/* 
给你一个下标从 0 开始的数组 nums ，数组由若干 互不相同 的整数组成。

nums 中有一个值最小的元素和一个值最大的元素。分别称为 最小值 和 最大值 。你的目标是从数组中移除这两个元素。

一次 删除 操作定义为从数组的 前面 移除一个元素或从数组的 后面 移除一个元素。

返回将数组中最小值和最大值 都 移除需要的最小删除次数。
 */
class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        map<int,int> mp;
		int M=0,m=0,n=nums.size(),mx=nums[0],mn=nums[0];
		for(int i=0;i<n;i++){
			if(nums[i]>mx){
				mx=nums[i];
				M=i;
			}
			if(nums[i]<mn){
				mn=nums[i];
				m=i;
			}
		}
		if(m==M){
			return (m+1)<n/2?m+1:(n-m);
		}else if(m<M){
			return min(m+1+(n-M),min(n-m,M+1));
		}else{
			return min(M+1+(n-m),min(n-M,m+1));
		}
		return -1;
    }
};
/* 
给你一个整数 n ，表示有 n 个专家从 0 到 n - 1 编号。
另外给你一个下标从 0 开始的二维整数数组 meetings ，其中 meetings[i] = [xi, yi, timei] 表示专家 xi 和专家 yi 在时间 timei 要开一场会。
一个专家可以同时参加 多场会议 。最后，给你一个整数 firstPerson 。

专家 0 有一个 秘密 ，最初，他在时间 0 将这个秘密分享给了专家 firstPerson 。
接着，这个秘密会在每次有知晓这个秘密的专家参加会议时进行传播。
更正式的表达是，每次会议，如果专家 xi 在时间 timei 时知晓这个秘密，那么他将会与专家 yi 分享这个秘密，反之亦然。

秘密共享是 瞬时发生 的。也就是说，在同一时间，一个专家不光可以接收到秘密，还能在其他会议上与其他专家分享。

在所有会议都结束之后，返回所有知晓这个秘密的专家列表。你可以按 任何顺序 返回答案。
 */
