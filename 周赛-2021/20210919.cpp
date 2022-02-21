#include "head.h"
/* 
存在一种仅支持 4 种操作和 1 个变量 X 的编程语言：

    ++X 和 X++ 使变量 X 的值 加 1
    --X 和 X-- 使变量 X 的值 减 1

最初，X 的值是 0

给你一个字符串数组 operations ，这是由操作组成的一个列表，返回执行所有操作后， X 的 最终值 。
 */
class Solution {
public:
    int finalValueAfterOperations(vector<string>& operations) {
        int res=0;
        for(auto str:operations){
            if(str[1]=='+'){
                res++;
            }else{
                res--;
            }
        }
        return res;
    }
};
/* 
给你一个下标从 0 开始的整数数组 nums 。对于每个下标 i（1 <= i <= nums.length - 2），nums[i] 的 美丽值 等于：

    2，对于所有 0 <= j < i 且 i < k <= nums.length - 1 ，满足 nums[j] < nums[i] < nums[k]
    1，如果满足 nums[i - 1] < nums[i] < nums[i + 1] ，且不满足前面的条件
    0，如果上述条件全部不满足

返回符合 1 <= i <= nums.length - 2 的所有 nums[i] 的 美丽值的总和 。
 */
class Solution {
public:
    int sumOfBeauties(vector<int>& nums) {
		int n=nums.size();
		vector<int> mx(n),mn(n);
		int k=nums[0];
		for(int i=0;i<n;i++){
			k=max(nums[i],k);
			mx[i]=k;
		}
		k=nums[n-1];
		for(int i=n-1;i>=0;i--){
			k=min(nums[i],k);
			mn[i]=k;
		}
		int res=0;
		for(int i=1;i<n-1;i++){
			if(mx[i-1]<nums[i]&&mn[i+1]>nums[i]){
				res+=2;
			}else if(nums[i-1]<nums[i]&&nums[i]<nums[i+1]){
				res++;
			}
		}
		return res;
    }
};
/* 
给你一个在 X-Y 平面上的点构成的数据流。设计一个满足下述要求的算法：

    添加 一个在数据流中的新点到某个数据结构中。可以添加 重复 的点，并会视作不同的点进行处理。
    给你一个查询点，请你从数据结构中选出三个点，使这三个点和查询点一同构成一个 面积为正 的 轴对齐正方形 ，统计 满足该要求的方案数目。

轴对齐正方形 是一个正方形，除四条边长度相同外，还满足每条边都与 x-轴 或 y-轴 平行或垂直。

实现 DetectSquares 类：

    DetectSquares() 使用空数据结构初始化对象
    void add(int[] point) 向数据结构添加一个新的点 point = [x, y]
    int count(int[] point) 统计按上述方式与点 point = [x, y] 共同构造 轴对齐正方形 的方案数。

 */
class DetectSquares {
public:
    DetectSquares() {
		col.clear();
		row.clear();
    }
    
    void add(vector<int> point) {
		int m=point[0],n=point[1];
		row[m][n]++;
		col[n][m]++;
    }
    
    int count(vector<int> point) {
		int m=point[0],n=point[1];
		if(!row.count(m)&&!col.count(n)){
			return 0;
		}
		int res=0;
		for(auto [x,y]:row[m]){
			int len=n-x;
			//面积不能为0
			if(len==0){
				continue;
			}
			if(!col[n].count(m+len)&&!col[n].count(m-len)){
				continue;
			}
			if(col[n].count(m+len)&&col[x].count(m+len)){
				res+=y*col[n][m+len]*col[x][m+len];
			}
			if(col[n].count(m-len)&&col[x].count(m-len)){
				res+=y*col[n][m-len]*col[x][m-len];
			}
		}
		return res;
    }
	unordered_map<int,unordered_map<int,int>> col,row;
};

/**
 * Your DetectSquares object will be instantiated and called as such:
 * DetectSquares* obj = new DetectSquares();
 * obj->add(point);
 * int param_2 = obj->count(point);
 */
/* 
给你一个长度为 n 的字符串 s ，和一个整数 k 。请你找出字符串 s 中 重复 k 次的 最长子序列 。

子序列 是由其他字符串删除某些（或不删除）字符派生而来的一个字符串。

如果 seq * k 是 s 的一个子序列，其中 seq * k 表示一个由 seq 串联 k 次构造的字符串，那么就称 seq 是字符串 s 中一个 重复 k 次 的子序列。

    举个例子，"bba" 是字符串 "bababcba" 中的一个重复 2 次的子序列，因为字符串 "bbabba" 是由 "bba" 串联 2 次构造的，而 "bbabba" 是字符串 "bababcba" 的一个子序列。

返回字符串 s 中 重复 k 次的最长子序列  。如果存在多个满足的子序列，则返回 字典序最大 的那个。如果不存在这样的子序列，返回一个 空 字符串。
 */
class Solution {
public:
    string longestSubsequenceRepeatedK(string s, int k) {

    }
};