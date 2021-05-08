#include "head.h"
/*
给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是 回文串 。返回 s 所有可能的分割方案。
回文串 是正着读和反着读都一样的字符串。
131
*/
/*
给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
candidates 中的数字可以无限制重复被选取。
说明：
    所有数字（包括 target）都是正整数。
    解集不能包含重复的组合。 
39
*/
/*
给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
candidates 中的每个数字在每个组合中只能使用一次。
说明：
    所有数字（包括目标数）都是正整数。
    解集不能包含重复的组合。 
40
*/
class Solution {
public:
	vector<vector<int>> res;
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
		sort(candidates.begin(),candidates.end());
		vector<int> temp;
		dfs(candidates,target,0,temp,0);
		return res;
    }
	void dfs(vector<int>& candidates,int target,int sum,vector<int> temp,int index){
		if(sum>target){
			return;
		}
		if(sum==target){
			res.push_back(temp);
            return;
		}
		for(int i=index;i<candidates.size();i++){
            if(i>index&&candidates[i]==candidates[i-1]){
                continue;
            }
			sum+=candidates[i];
			temp.push_back(candidates[i]);
			dfs(candidates,target,sum,temp,i+1);
			temp.pop_back();
			sum-=candidates[i];
		}
	}
};
/*
给定一个 没有重复 数字的序列，返回其所有可能的全排列。
46
*/
/*
给定一个可包含重复数字的序列 nums ，按任意顺序 返回所有不重复的全排列。
47
*/
/*
给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合。
77
*/
/*
给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。
解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。
78
*/
/*
给定一个可能包含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
说明：解集不能包含重复的子集。
90
*/
/*
给定一个只包含数字的字符串，用以表示一个 IP 地址，返回所有可能从 s 获得的 有效 IP 地址 。你可以按任何顺序返回答案。
有效 IP 地址 正好由四个整数（每个整数位于 0 到 255 之间组成，且不能含有前导 0），整数之间用 '.' 分隔。
例如："0.1.2.201" 和 "192.168.1.1" 是 有效 IP 地址，但是 "0.011.255.245"、"192.168.1.312" 和 "192.168@1.1" 是 无效 IP 地址。
93
*/
/*
给定一个二维网格和一个单词，找出该单词是否存在于网格中。
单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。
79
*/
/*
给你一个 m x n 的矩阵 board ，由若干字符 'X' 和 'O' ，找到所有被 'X' 围绕的区域，并将这些区域里所有的 'O' 用 'X' 填充。 
130
*/
/*
给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。
给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。
17
*/
/*
给定一个字符串S，通过将字符串S中的每个字母转变大小写，我们可以获得一个新的字符串。返回所有可能得到的字符串集合。
784
*/
/*
数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
22
*/
/*
n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。
每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。
51
*/
/*
编写一个程序，通过填充空格来解决数独问题。

一个数独的解法需遵循如下规则：

    数字 1-9 在每一行只能出现一次。
    数字 1-9 在每一列只能出现一次。
    数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。

空白格用 '.' 表示。
37
*/
/* 
给定一个整数数组  nums 和一个正整数 k，找出是否有可能把这个数组分成 k 个非空子集，其总和都相等。
698
 */
class Solution {
public:
	vector<int> visit;
	bool res=false;
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        int sum=accumulate(nums.begin(),nums.end(),0);
		if(sum%k){
			return false;
		}
		visit.resize(nums.size());
		dfs(nums,k,sum/k,0,0);
		return res;
    }
	void dfs(vector<int>& nums,int k,int target,int sum,int index){
		if(k==1){
			res=true;
			return;
		}
		if(target==sum){
			dfs(nums,k-1,target,0,0);
		}
		for(int i=index;i<nums.size();i++){
            //剪枝，去除与前一个相同但是前一个没取过的。去重
            if(i>0&&nums[i]==nums[i-1]&&visit[i-1]==0){
                continue;
            }
			if(visit[i]==0&&sum+nums[i]<=target){
				visit[i]=1;
				dfs(nums,k,target,sum+nums[i],i+1);
				visit[i]=0;
			}
		}
	}
};