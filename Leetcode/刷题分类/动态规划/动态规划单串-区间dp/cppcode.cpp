#include"head.h"
/* 
有台奇怪的打印机有以下两个特殊要求：

    打印机每次只能打印由 同一个字符 组成的序列。
    每次可以在任意起始和结束位置打印新字符，并且会覆盖掉原来已有的字符。

给你一个字符串 s ，你的任务是计算这个打印机打印它需要的最少打印次数。
664
 */
class Solution {
public:
    int strangePrinter(string s) {
		int n=s.size();
		vector<vector<int>> dp(n,vector<int>(n,1));
		for(int i=n-1;i>=0;i--){
			for(int j=i+1;j<n;j++){
				if(s[i]==s[j]){
					dp[i][j]=dp[i][j-1];
				}else{
                    dp[i][j]=INT_MAX;
					for(int k=i;k<j;k++){
						dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
					}
				}
			}
		}
		return dp[0][n-1];
    }
};
/* 
给出一些不同颜色的盒子，盒子的颜色由数字表示，即不同的数字表示不同的颜色。

你将经过若干轮操作去去掉盒子，直到所有的盒子都去掉为止。
每一轮你可以移除具有相同颜色的连续 k 个盒子（k >= 1），这样一轮之后你将得到 k * k 个积分。

当你将所有盒子都去掉之后，求你能获得的最大积分和。
546
 */
class Solution {
public:
    int removeBoxes(vector<int>& boxes) {

    }
};