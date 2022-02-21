#include "head.h"
/* 
给你一个整数数组 nums 。nums 中，子数组的 范围 是子数组中最大元素和最小元素的差值。

返回 nums 中 所有 子数组范围的 和 。

子数组是数组中一个连续 非空 的元素序列。
 */
class Solution {
public:
    long long subArrayRanges(vector<int>& nums) {
		int n=nums.size();
		long long res=0;
		for(int i=0;i<n;i++){
			int maxn=nums[i],minn=nums[i];
			for(int j=i+1;j<n;j++){
				maxn=max(nums[j],maxn);
				minn=min(nums[j],minn);
				res+=maxn-minn;
			}
		}
		return res;
    }
};
/* 
Alice 和 Bob 打算给花园里的 n 株植物浇水。植物排成一行，从左到右进行标记，编号从 0 到 n - 1 。其中，第 i 株植物的位置是 x = i 。

每一株植物都需要浇特定量的水。Alice 和 Bob 每人有一个水罐，最初是满的 。他们按下面描述的方式完成浇水：

     Alice 按 从左到右 的顺序给植物浇水，从植物 0 开始。Bob 按 从右到左 的顺序给植物浇水，从植物 n - 1 开始。他们 同时 给植物浇水。
    如果没有足够的水 完全 浇灌下一株植物，他 / 她会立即重新灌满浇水罐。
    不管植物需要多少水，浇水所耗费的时间都是一样的。
    不能 提前重新灌满水罐。
    每株植物都可以由 Alice 或者 Bob 来浇水。
    如果 Alice 和 Bob 到达同一株植物，那么当前水罐中水更多的人会给这株植物浇水。如果他俩水量相同，那么 Alice 会给这株植物浇水。

给你一个下标从 0 开始的整数数组 plants ，数组由 n 个整数组成。其中，plants[i] 为第 i 株植物需要的水量。
另有两个整数 capacityA 和 capacityB 分别表示 Alice 和 Bob 水罐的容量。返回两人浇灌所有植物过程中重新灌满水罐的 次数 。

 */
class Solution {
public:
    int minimumRefill(vector<int>& plants, int capacityA, int capacityB) {
        int res=0,n=plants.size(),left=0,right=n-1;
		int lw=capacityA,rw=capacityB;
		while(left<=right){
			if(left==right){
				int w=max(lw,rw);
				if(w<plants[left]){
					res++;
				}
				break;
			}
			if(lw<plants[left]){
				lw=capacityA-plants[left];
				res++;
			}else{
				lw-=plants[left];
			}
			if(rw<plants[right]){
				rw=capacityB-plants[right];
				res++;
			}else{
				rw-=plants[right];
			}
		}
		return res;
    }
};
/* 
在一个无限的 x 坐标轴上，有许多水果分布在其中某些位置。
给你一个二维整数数组 fruits ，其中 fruits[i] = [positioni, amounti] 表示共有 amounti 个水果放置在 positioni 上。
fruits 已经按 positioni 升序排列 ，每个 positioni 互不相同 。

另给你两个整数 startPos 和 k 。最初，你位于 startPos 。
从任何位置，你可以选择 向左或者向右 走。在 x 轴上每移动 一个单位 ，就记作 一步 。
你总共可以走 最多 k 步。你每达到一个位置，都会摘掉全部的水果，水果也将从该位置消失（不会再生）。

返回你可以摘到水果的 最大总数 。
二分
 */
class Solution {
public:
    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
		vector<int> tmp(2*k+1,0);
		for(int i=k;i<2*k+1;i++){
			int j=i-k;
			
		}
    }
};