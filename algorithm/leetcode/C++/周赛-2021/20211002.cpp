#include "head.h"
/* 
给你一个下标从 0 开始的一维整数数组 original 和两个整数 m 和  n 。你需要使用 original 中 所有 元素创建一个 m 行 n 列的二维数组。

original 中下标从 0 到 n - 1 （都 包含 ）的元素构成二维数组的第一行，
下标从 n 到 2 * n - 1 （都 包含 ）的元素构成二维数组的第二行，依此类推。

请你根据上述过程返回一个 m x n 的二维数组。如果无法构成这样的二维数组，请你返回一个空的二维数组。
 */
class Solution {
public:
    vector<vector<int>> construct2DArray(vector<int>& original, int m, int n) {
		vector<vector<int>> res;
		if(original.size()!=m*n){
			return res;
		}
		int index=0;
		for(int i=0;i<m;i++){
			vector<int> tmp;
			for(int j=0;j<n;j++){
				tmp.emplace_back(original[index++]);
			}
			res.emplace_back(tmp);
		}
		return res;
    }
};
/* 
给你一个 数字 字符串数组 nums 和一个 数字 字符串 target ，
请你返回 nums[i] + nums[j] （两个字符串连接）结果等于 target 的下标 (i, j) （需满足 i != j）的数目。
 */
class Solution {
public:
    int numOfPairs(vector<string>& nums, string target) {
		int res=0;
		for(int i=0;i<nums.size();i++){
			if(target.find(nums[i])!=0){
				continue;
			}
			for(int j=0;j<nums.size();j++){
				if(i==j){
					continue;
				}
				if(nums[i]+nums[j]==target){
					res++;
				}
			}
		}
		return res;
    }
};
/* 
一位老师正在出一场由 n 道判断题构成的考试，每道题的答案为 true （用 'T' 表示）或者 false （用 'F' 表示）。
老师想增加学生对自己做出答案的不确定性，方法是 最大化 有 连续相同 结果的题数。（也就是连续出现 true 或者连续出现 false）。

给你一个字符串 answerKey ，其中 answerKey[i] 是第 i 个问题的正确结果。除此以外，还给你一个整数 k ，表示你能进行以下操作的最多次数：

    每次操作中，将问题的正确答案改为 'T' 或者 'F' （也就是将 answerKey[i] 改为 'T' 或者 'F' ）。

请你返回在不超过 k 次操作的情况下，最大 连续 'T' 或者 'F' 的数目。
 */
class Solution {
public:
    int maxConsecutiveAnswers(string answerKey, int k) {
		int num=0;
		//找F变T
		int n=answerKey.size(),maxn=0;
		int left=0,right=0;
		while(right<n){
			while(right<n){
				if(answerKey[right]=='F'){
					if(num==k){
						break;
					}else{
						num++;
					}
				}
				right++;
			}
			int maxn=max(right-left,maxn);
			while(left<right){
				if(answerKey[right]=='F'){
					num--;
					left++;
					break;
				}
				left++;
			}
		}
		while(right<n){
			while(right<n){
				if(answerKey[right]=='T'){
					if(num==k){
						break;
					}else{
						num++;
					}
				}
				right++;
			}
			int maxn=max(right-left,maxn);
			while(left<right){
				if(answerKey[right]=='T'){
					num--;
					left++;
					break;
				}
				left++;
			}
		}
		return maxn;
    }
};
/* 
给你一个下标从 0 开始且长度为 n 的整数数组 nums 。分割 数组 nums 的方案数定义为符合以下两个条件的 pivot 数目：

    1 <= pivot < n
    nums[0] + nums[1] + ... + nums[pivot - 1] == nums[pivot] + nums[pivot + 1] + ... + nums[n - 1]

同时给你一个整数 k 。你可以将 nums 中 一个 元素变为 k 或 不改变 数组。

请你返回在 至多 改变一个元素的前提下，最多 有多少种方法 分割 nums 使得上述两个条件都满足。
 */
//超时！！！！
class Solution {
public:
    int waysToPartition(vector<int>& nums, int k) {
		int sum=accumulate(nums.begin(),nums.end(),0);
		int n=nums.size();
		vector<int> pre(n);
		pre[0]=nums[0];
		for(int i=1;i<n;i++){
			pre[i]=pre[i-1]+nums[i];
		}
		int maxn=0;
		for(int i=0;i<n-1;i++){
			if(pre[i]==sum-pre[i]){
				maxn++;
			}
		}
		for(int i=0;i<n;i++){
			int s=sum-nums[i]+k,tmp=0;
			for(int j=0;j<n-1;j++){
				if(j>=i){
					if(pre[j]-nums[i]+k==sum-pre[j]){
						tmp++;
					}
				}else{
					if(pre[j]==s-pre[j]){
						tmp++;
					}
				}
			}
			maxn=max(maxn,tmp);
		}
		return maxn;
    }
};