#include"head.h"
//最值问题
/* 
给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。
如果没有任何一种硬币组合能组成总金额，返回 -1。
你可以认为每种硬币的数量是无限的。
322
 */
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
		int n=coins.size();
		vector<int> dp(amount+1,amount+1);
		dp[0]=0;
		for(int i=0;i<=amount;i++){
			for(int coin:coins){
				if(coin<=i){
					dp[i]=min(dp[i-coin]+1,dp[i]);
				}
			}
		}
		return dp[amount]>amount?-1:dp[amount];
    }
};
/* 
给你一个二进制字符串数组 strs 和两个整数 m 和 n 。
请你找出并返回 strs 的最大子集的大小，该子集中 最多 有 m 个 0 和 n 个 1 。
如果 x 的所有元素也是 y 的元素，集合 x 是集合 y 的 子集 。
1 <= strs.length <= 600
1 <= strs[i].length <= 100
strs[i] 仅由 '0' 和 '1' 组成
1 <= m, n <= 100
474
对于此类题可以现在表格里推一下
*/
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
		vector<vector<int>> dp(m+1,vector<int>(n+1));
		for(string str:strs){
			int n0=0,n1=0;
			for(char c:str){
				if(c=='0'){
					n0++;
				}else{
					n1++;
				}
			}
			for(int i=m;i>=n0;i--){
				for(int j=n;j>=n1;j--){
					dp[i][j]=max(dp[i-n0][j-n1]+1,dp[i][j]);
				}
			}
		}
		return dp[m][n];
    }
};
/* 
有一堆石头，每块石头的重量都是正整数。
每一回合，从中选出任意两块石头，然后将它们一起粉碎。假设石头的重量分别为 x 和 y，且 x <= y。那么粉碎的可能结果如下：
    如果 x == y，那么两块石头都会被完全粉碎；
    如果 x != y，那么重量为 x 的石头将会完全粉碎，而重量为 y 的石头新重量为 y-x。
最后，最多只会剩下一块石头。返回此石头最小的可能重量。如果没有石头剩下，就返回 0。
*/
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int sum=accumulate(stones.begin(),stones.end(),0);
		int target=sum/2;
		vector<int> dp(target+1);
		for(int stone:stones){
			for(int i=target;i>=stone;i--){
				dp[i]=max(dp[i-stone]+stone,dp[i]);
			}
		}
		return sum-2*dp[target];
    }
};
/* 
给定正整数 n，找到若干个完全平方数（比如 1, 4, 9, 16, ...）使得它们的和等于 n。你需要让组成和的完全平方数的个数最少。
给你一个整数 n ，返回和为 n 的完全平方数的 最少数量 。
完全平方数 是一个整数，其值等于另一个整数的平方；换句话说，其值等于一个整数自乘的积。
例如，1、4、9 和 16 都是完全平方数，而 3 和 11 不是。
279
 */
class Solution {
public:
    int numSquares(int n) {
		vector<int> nums;
		for(int i=1;i<=n;i++){
			if(i*i<n){
				nums.push_back(i*i);
			}else if(i*i==n){
				return 1;
			}else{
				break;
			}
		}
		vector<int> dp(n+1,n+1);
		dp[0]=0;
		for(int num:nums){
			for(int i=num;i<=n;i++){
				dp[i]=min(dp[i-num]+1,dp[i]);
			}
		}
		return dp[n];
    }
};
//True/Fale问题
/* 
给你一个 只包含正整数 的 非空 数组 nums 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
416
 */
class Solution {
public:
    bool canPartition(vector<int>& nums) {
		int sum=accumulate(nums.begin(),nums.end(),0);
		if(sum%2!=0){
			return false;
		}
		int target=sum/2;
		vector<bool> dp(target+1,false);
		dp[0]=true;
		for(int num:nums){
			for(int i=target;i>=num;i--){
				dp[i]=dp[i-num]||dp[i];
			}
		}
		return dp[target];
    }
};
/* 
给定一个非空字符串 s 和一个包含非空单词的列表 wordDict，判定 s 是否可以被空格拆分为一个或多个在字典中出现的单词。
说明：
    拆分时可以重复使用字典中的单词。
    你可以假设字典中没有重复的单词。
139
 */
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
		vector<bool> dp(s.size()+1,false);
		dp[0]=true;
		for(int i=1;i<dp.size();i++){
			for(string str:wordDict){
				string ss=s.substr(0,i);
                int index=0;
                int pos=ss.find(str,index);
				while(pos!=string::npos){
					dp[pos+str.size()]=dp[pos]||dp[pos+str.size()];
					index=pos+1;
                    pos=ss.find(str,index);
				}
			}
		}
		return dp[s.size()];
    }
};
//组合问题
/* 
给你一个由 不同 整数组成的数组 nums ，和一个目标整数 target 。请你从 nums 中找出并返回总和为 target 的元素组合的个数。

题目数据保证答案符合 32 位整数范围。
377
考虑顺序
 */
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
		vector<int> dp(target+1);
		dp[0]=1;
		for(int i=0;i<=target;i++){
			for(int num:nums){
				if(i>=num){
					dp[i]+=dp[i-num];
				}
			}
		}
		return dp[target];
    }
};
/* 
给定一个非负整数数组，a1, a2, ..., an, 和一个目标数，S。现在你有两个符号 + 和 -。对于数组中的任意一个整数，
你都可以从 + 或 -中选择一个符号添加在前面。
返回可以使最终数组和为目标数 S 的所有添加符号的方法数。
ps 给的target是隐含的
494
 */
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
		int sum=accumulate(nums.begin(),nums.end(),0);
		if(target>sum||(target+sum)%2==1){
			return 0;
		}
		int t=(target+sum)/2;
		vector<int> dp(t+1);
		dp[0]=1;
		for(int num:nums){
			for(int i=t;i>=num;i--){
				dp[i]+=dp[i-num];
			}
		}
		return dp[t];
    }
};
/* 
给定不同面额的硬币和一个总金额。写出函数来计算可以凑成总金额的硬币组合数。假设每一种面额的硬币有无限个。 
518
 */
class Solution {
public:
    int change(int amount, vector<int>& coins) {
		vector<unsigned int> dp(amount+1,0);
		dp[0]=1;
		for(int coin:coins){
			for(int i=coin;i<=amount;i++){
				dp[i]+=dp[i-coin];
			}
		}
		return dp[amount];
    }
};
/* 
集团里有 n 名员工，他们可以完成各种各样的工作创造利润。

第 i 种工作会产生 profit[i] 的利润，它要求 group[i] 名成员共同参与。如果成员参与了其中一项工作，就不能参与另一项工作。

工作的任何至少产生 minProfit 利润的子集称为盈利计划。并且工作的成员总数最多为 n 。

有多少种计划可以选择？因为答案很大，所以 返回结果模 10^9 + 7 的值。
879
 */
class Solution {
public:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
		
    }
};