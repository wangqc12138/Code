#include "head.h"
/*
给定两个字符串 text1 和 text2，返回这两个字符串的最长公共子序列的长度。
一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。两个字符串的「公共子序列」是这两个字符串所共同拥有的子序列。
若这两个字符串没有公共子序列，则返回 0。
1143
*/
/*
给定两个字符串s1, s2，找到使两个字符串相等所需删除字符的ASCII值的最小和。
712
*/
/*
给两个整数数组 A 和 B ，返回两个数组中公共的、长度最长的子数组的长度。
718
*/
/* 
在两条独立的水平线上按给定的顺序写下 nums1 和 nums2 中的整数。

现在，可以绘制一些连接两个数字 nums1[i] 和 nums2[j] 的直线，这些直线需要同时满足满足：

     nums1[i] == nums2[j]
    且绘制的直线不与任何其他连线（非水平线）相交。

请注意，连线即使在端点也不能相交：每个数字只能属于一条连线。

以这种方法绘制线条，并返回可以绘制的最大连线数。
1035
 */
//披着皮的最长公共子序列
class Solution {
public:
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
		int m=nums1.size(),n=nums2.size();
		vector<vector<int>> dp(m+1,vector<int>(n+1,0));
		for(int i=1;i<=m;i++){
			for(int j=1;j<=n;j++){
				dp[i][j]=nums1[i-1]==nums2[j-1]?dp[i-1][j-1]+1:max(dp[i-1][j],dp[i][j-1]);
			}
		}
		return dp[m][n];
    }
};