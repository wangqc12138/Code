#include"head.h"
/* 
给定一个表示分数的非负整数数组。 
玩家 1 从数组任意一端拿取一个分数，随后玩家 2 继续从剩余数组任意一端拿取分数，然后玩家 1 拿，…… 。
每次一个玩家只能拿取一个分数，分数被拿取之后不再可取。直到没有剩余分数可取时游戏结束。最终获得分数总和最多的玩家获胜。
给定一个表示分数的数组，预测玩家1是否会成为赢家。你可以假设每个玩家的玩法都会使他的分数最大化
486
*/
class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
		int n=nums.size();
		//由于是偶数堆，则先手可以选择先拿偶数号或是奇数号，必赢
		if(n%2==0){
			return true;
		}
		vector<vector<int>> dp(n,vector<int>(n,0));
		for(int i=0;i<n;i++){
			dp[i][i]=nums[i];
		}
		for(int i=n-2;i>=0;i--){
			for(int j=i+1;j<n;j++){
				dp[i][j]=max(nums[i]-dp[i+1][j],nums[j]-dp[i][j-1]);
			}
		}
		return dp[0][n-1]>=0;
    }
};
/* 
亚历克斯和李用几堆石子在做游戏。偶数堆石子排成一行，每堆都有正整数颗石子 piles[i] 。
游戏以谁手中的石子最多来决出胜负。石子的总数是奇数，所以没有平局。
亚历克斯和李轮流进行，亚历克斯先开始。 每回合，玩家从行的开始或结束处取走整堆石头。 这种情况一直持续到没有更多的石子堆为止，此时手中石子最多的玩家获胜。
假设亚历克斯和李都发挥出最佳水平，当亚历克斯赢得比赛时返回 true ，当李赢得比赛时返回 false 。
877
*/
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
		return true;
    }
};
/* 
亚历克斯和李继续他们的石子游戏。许多堆石子 排成一行，每堆都有正整数颗石子 piles[i]。游戏以谁手中的石子最多来决出胜负。
亚历克斯和李轮流进行，亚历克斯先开始。最初，M = 1。
在每个玩家的回合中，该玩家可以拿走剩下的 前 X 堆的所有石子，其中 1 <= X <= 2M。然后，令 M = max(M, X)。
游戏一直持续到所有石子都被拿走。
假设亚历克斯和李都发挥出最佳水平，返回亚历克斯可以得到的最大数量的石头。
1140
    1 <= piles.length <= 100
    1 <= piles[i] <= 10 ^ 4
*/
//前X堆
class Solution {
public:
    int stoneGameII(vector<int>& piles) {
		int n=piles.size(),sum=0;
		vector<vector<int>> dp(n,vector<int>(n+1,0));
		for(int i=n-1;i>=0;i--){
			sum+=piles[i];
			for(int j=1;j<=n;j++){
				if(i+2*j>=n){
					dp[i][j]=sum;
				}else{
					for(int x=1;x<=2*j;x++){
						dp[i][j]=max(dp[i][j],sum-dp[i+x][max(j,x)]);
					}
				}
			}
		}
		return dp[0][1];
	}
};
/* 
Alice 和 Bob 用几堆石子在做游戏。几堆石子排成一行，每堆石子都对应一个得分，由数组 stoneValue 给出。

Alice 和 Bob 轮流取石子，Alice 总是先开始。在每个玩家的回合中，该玩家可以拿走剩下石子中的的前 1、2 或 3 堆石子 。
比赛一直持续到所有石头都被拿走。

每个玩家的最终得分为他所拿到的每堆石子的对应得分之和。每个玩家的初始分数都是 0 。
比赛的目标是决出最高分，得分最高的选手将会赢得比赛，比赛也可能会出现平局。

假设 Alice 和 Bob 都采取 最优策略 。如果 Alice 赢了就返回 "Alice" ，Bob 赢了就返回 "Bob"，平局（分数相同）返回 "Tie" 。
 */
class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
		int n=stoneValue.size(),sum=0;
		vector<int> dp(n+3,0);
		for(int i=n-1;i>=0;i--){
			dp[i]=INT_MIN;
			sum+=stoneValue[i];
			for(int j=1;j<4;j++){
				dp[i]=max(dp[i],sum-dp[i+j]);
			}
		}
		sum=accumulate(stoneValue.begin(),stoneValue.end(),0);
		if(sum>2*dp[0]){
			return "Bob";
		}
		if(sum==2*dp[0]){
			return "Tie";
		}
		return "Alice";
    }
};
/* 
Alice 和 Bob 两个人轮流玩一个游戏，Alice 先手。
一开始，有 n 个石子堆在一起。每个人轮流操作，正在操作的玩家可以从石子堆里拿走 任意 非零 平方数 个石子。
如果石子堆里没有石子了，则无法操作的玩家输掉游戏。
给你正整数 n ，且已知两个人都采取最优策略。如果 Alice 会赢得比赛，那么返回 True ，否则返回 False 。
1510
1 <= n <= 10^5
*/
class Solution {
public:
    bool winnerSquareGame(int n) {
		vector<bool> dp(n+1,false);
		for(int i=1;i<n;i++){
			for(int j=1;j<n;j++){
				if(j*j>i){
					break;
				}
				if(dp[i-j*j]==false){
					dp[i]=true;
					break;
				}
			}
		}
		return dp[n];
    }
};
/* 
几块石子 排成一行 ，每块石子都有一个关联值，关联值为整数，由数组 stoneValue 给出。

游戏中的每一轮：Alice 会将这行石子分成两个 非空行（即，左侧行和右侧行）；
Bob 负责计算每一行的值，即此行中所有石子的值的总和。Bob 会丢弃值最大的行，Alice 的得分为剩下那行的值（每轮累加）。

如果两行的值相等，Bob 让 Alice 决定丢弃哪一行。下一轮从剩下的那一行开始。

只 剩下一块石子 时，游戏结束。Alice 的分数最初为 0 。
返回 Alice 能够获得的最大分数 。
1563
 */
class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {

    }
};
