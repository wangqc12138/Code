#include "head.h"
/* 
给你一个下标从 0 开始的整数数组 nums ，该数组的大小为 n ，请你计算 nums[j] - nums[i] 能求得的 最大差值 ，其中 0 <= i < j < n 且 nums[i] < nums[j] 。

返回 最大差值 。如果不存在满足要求的 i 和 j ，返回 -1 。
 */
class Solution {
public:
    int maximumDifference(vector<int>& nums) {
		int res=INT_MIN;
		for(int i=0;i<nums.size();i++){
			for(int j=i+1;j<nums.size();j++){
				res=max(res,nums[j]-nums[i]);
			}
		}
		return res<=0?-1:res;
    }
};
/* 
给你一个下标从 0 开始的二维数组 grid ，数组大小为 2 x n ，其中 grid[r][c] 表示矩阵中 (r, c) 位置上的点数。
现在有两个机器人正在矩阵上参与一场游戏。

两个机器人初始位置都是 (0, 0) ，目标位置是 (1, n-1) 。每个机器人只会 向右 ((r, c) 到 (r, c + 1)) 或 向下 ((r, c) 到 (r + 1, c)) 。

游戏开始，第一个 机器人从 (0, 0) 移动到 (1, n-1) ，并收集路径上单元格的全部点数。
对于路径上所有单元格 (r, c) ，途经后 grid[r][c] 会重置为 0 。
然后，第二个 机器人从 (0, 0) 移动到 (1, n-1) ，同样收集路径上单元的全部点数。注意，它们的路径可能会存在相交的部分。

第一个 机器人想要打击竞争对手，使 第二个 机器人收集到的点数 最小化 。
与此相对，第二个 机器人想要 最大化 自己收集到的点数。两个机器人都发挥出自己的 最佳水平 的前提下，返回 第二个 机器人收集到的 点数 。
 */
class Solution {
public:
    long long gridGame(vector<vector<int>>& grid) {
        return dfs(grid,0,0);
    }
	long long help(vector<vector<int>>& grid) {
		int m=grid.size();
		int n=grid[0].size();
		vector<vector<long long>> dp(m,vector<long long>(n,0));
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				if(i==0&&j==0){
					dp[0][0]=grid[0][0];
				}else if(i==0){
					dp[i][j]=dp[i][j-1]+grid[i][j];
				}else if(j==0){
					dp[i][j]=grid[i][j]+dp[i-1][j];
				}else{
					dp[i][j]=grid[i][j]+max(dp[i-1][j],dp[i][j-1]);
				}
			}
		}
		return dp[m-1][n-1];
	}
};
/* 
给你一个 m x n 的矩阵 board ，它代表一个填字游戏 当前 的状态。填字游戏格子中包含小写英文字母（已填入的单词），
表示 空 格的 ' ' 和表示 障碍 格子的 '#' 。

如果满足以下条件，那么我们可以 水平 （从左到右 或者 从右到左）或 竖直 （从上到下 或者 从下到上）填入一个单词：

    该单词不占据任何 '#' 对应的格子。
    每个字母对应的格子要么是 ' ' （空格）要么与 board 中已有字母 匹配 。
    如果单词是 水平 放置的，那么该单词左边和右边 相邻 格子不能为 ' ' 或小写英文字母。
    如果单词是 竖直 放置的，那么该单词上边和下边 相邻 格子不能为 ' ' 或小写英文字母。

给你一个字符串 word ，如果 word 可以被放入 board 中，请你返回 true ，否则请返回 false 。
 */
class Solution {
public:
    bool placeWordInCrossword(vector<vector<char>>& board, string word) {
		int m=board.size();
		int n=board[0].size();
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				if(board[i][j]==' '||board[i][j]==word[0]){
					if((j==0||board[i][j-1]=='#')&&n-j>=word.size()){
						int k=j+1;
						for(;k<n&&k-j<word.size();k++){
							if(board[i][k]!=' '&&word[k-j]!=board[i][k]){
								break;
							}
						}
						if(k-j==word.size()&&(k==n-1||board[i][k+1]=='#')){
							return true;
						}
					}
				}
			}
		}
		for(int j=0;j<n;j++){
			for(int i=0;i<m;i++){
				if(board[i][j]==' '||board[i][j]==word[0]){
					if((i==0||board[i-1][j]=='#')&&m-i>=word.size()){
						int k=i+1;
						for(;k<m&&k-i<word.size();k++){
							if(board[k][j]!=' '&&word[k-i]!=board[k][j]){
								break;
							}
						}
						if(k-i==word.size()&&(k==m-1||board[k+1][j]=='#')){
							return true;
						}
					}
				}
			}
		}
		return false;
    }
};