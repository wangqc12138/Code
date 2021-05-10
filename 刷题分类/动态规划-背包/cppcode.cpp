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