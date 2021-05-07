#include "../../head.h"
//动态规划单串-带维度问题
/*
我们将给定的数组 A 分成 K 个相邻的非空子数组 ，我们的分数由每个子数组内的平均值的总和构成。计算我们所能得到的最大分数是多少。
注意我们必须使用 A 数组中的每一个数进行分组，并且分数不一定需要是整数。
813
*/
class Solution {
public:
    double largestSumOfAverages(vector<int>& A, int K) {
        int n=A.size(),t=0;
        vector<double> sum;
        vector<vector<double>> dp(n,vector<double>(K,0));
        for(auto i:A){
            sum.push_back(t+=i);
        }
        auto averge=[&](int i,int j){
            return i==0?sum[j]/(j+1):(sum[j]-sum[i-1])/(j-i+1);
        };
        for(int i=0;i<n;i++){
            dp[i][0]=averge(0,i);
        }
        for(int k=1;k<K;k++){
            for(int i=0;i<n;i++){
                for(int j=i-1;j>=0;j--){
                    dp[i][k]=max(dp[j][k-1]+averge(j+1,i),dp[i][k]);
                }
            }
        }
            
        return dp[n-1][K-1];       
    }
};
/*
给你 k 枚相同的鸡蛋，并可以使用一栋从第 1 层到第 n 层共有 n 层楼的建筑。
已知存在楼层 f ，满足 0 <= f <= n ，任何从 高于 f 的楼层落下的鸡蛋都会碎，从 f 楼层或比它低的楼层落下的鸡蛋都不会破。
每次操作，你可以取一枚没有碎的鸡蛋并把它从任一楼层 x 扔下（满足 1 <= x <= n）。如果鸡蛋碎了，你就不能再次使用它。如果某枚鸡蛋扔下后没有摔碎，则可以在之后的操作中 重复使用 这枚鸡蛋。
请你计算并返回要确定 f 确切的值 的 最小操作次数 是多少？
887
*/
class Solution {
public:
    int superEggDrop(int k, int n) {
        
    }
};
/* 
假如有一排房子，共 n 个，每个房子可以被粉刷成红色、蓝色或者绿色这三种颜色中的一种，你需要粉刷所有的房子并且使其相邻的两个房子颜色不能相同。
当然，因为市场上不同颜色油漆的价格不同，所以房子粉刷成不同颜色的花费成本也是不同的。
每个房子粉刷成不同颜色的花费是以一个 n x 3 的矩阵来表示的。
例如，costs[0][0] 表示第 0 号房子粉刷成红色的成本花费；
costs[1][2] 表示第 1 号房子粉刷成绿色的花费，以此类推。请你计算出粉刷完所有房子最少的花费成本。
注意：
所有花费均为正整数。
256
 */
class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        int n=costs.size();
        vector<vector<int>> dp(n,vector<int>(3));
        for(int i=0;i<3;i++){
            dp[0][i]=costs[0][i];
        }
        for(int i=1;i<n;i++){
            for(int j=0;j<3;j++){
                dp[i][j]=min(dp[i-1][(j+1)%3],dp[i-1][(j+2)%3])+costs[i][j];
            }
        }
        return *min_element(dp[n-1].begin(),dp[n-1].end());
    }
};
/* 
假如有一排房子，共 n 个，每个房子可以被粉刷成 k 种颜色中的一种，你需要粉刷所有的房子并且使其相邻的两个房子颜色不能相同。
当然，因为市场上不同颜色油漆的价格不同，所以房子粉刷成不同颜色的花费成本也是不同的。
每个房子粉刷成不同颜色的花费是以一个 n x k 的矩阵来表示的。
例如，costs[0][0] 表示第 0 号房子粉刷成 0 号颜色的成本花费；costs[1][2] 表示第 1 号房子粉刷成 2 号颜色的成本花费，
以此类推。请你计算出粉刷完所有房子最少的花费成本。
注意：
所有花费均为正整数。
265
 */
class Solution {
public:
    int minCostII(vector<vector<int>>& costs) {
        int n=costs.size(),k=costs[0].size();
        vector<vector<int>> dp(n,vector<int>(k));
        for(int i=0;i<k;i++){
            dp[0][i]=costs[0][i];
        }
        for(int i=1;i<n;i++){
            vector<int> pre(k,INT_MAX);
            for(int j=0;j<k;j++){
                for(int l=0;l<k;l++){
                    if(l==j){
                        continue;
                    }else{
                        pre[j]=min(pre[j],dp[i-1][l]);
                    }
                }
            }
            for(int j=0;j<k;j++){
                dp[i][j]=pre[j]+costs[i][j];
            }
        }
        return *min_element(dp[n-1].begin(),dp[n-1].end());
    }
};
/* 
在一个小城市里，有 m 个房子排成一排，你需要给每个房子涂上 n 种颜色之一（颜色编号为 1 到 n ）。
有的房子去年夏天已经涂过颜色了，所以这些房子不可以被重新涂色。
我们将连续相同颜色尽可能多的房子称为一个街区。
（比方说 houses = [1,2,2,3,3,2,1,1] ，它包含 5 个街区  [{1}, {2,2}, {3,3}, {2}, {1,1}] 。）
给你一个数组 houses ，一个 m * n 的矩阵 cost 和一个整数 target ，其中：
    houses[i]：是第 i 个房子的颜色，0 表示这个房子还没有被涂色。
    cost[i][j]：是将第 i 个房子涂成颜色 j+1 的花费。
请你返回房子涂色方案的最小总花费，使得每个房子都被涂色后，恰好组成 target 个街区。如果没有可用的涂色方案，请返回 -1 。
 */
/* 
输入：houses = [0,0,0,0,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m = 5, n = 2, target = 3
输出：9
解释：房子涂色方案为 [1,2,2,1,1]
此方案包含 target = 3 个街区，分别是 [{1}, {2,2}, {1,1}]。
涂色的总花费为 (1 + 1 + 1 + 1 + 5) = 9。
 */
class Solution {
public:
    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
        vector<vector<vector<int>>> dp(m,vector<vector<int>>(n,vector<int>(target+1,10001)));
        for(int i=0;i<m;i++){
            int h=houses[i]-1;
            if(i==0){
                if(h==0){
                    for(int j=0;j<n;j++){
                        dp[i][j][1]=cost[i][j];
                    }
                }else{
                    dp[i][h][1]=0;
                }
                continue;
            }
            for(int j=0;j<n;j++){
                for(int k=1;k<=target&&k<=i+1;k++){
                    if(h!=-1){
                        if(h==j){
                            for(int l=0;l<n;l++){
                                if(h!=l){
                                    dp[i][j][k]=min(dp[i][j][k],dp[i-1][l][k-1]);
                                }else{
                                    dp[i][j][k]=min(dp[i][j][k],dp[i-1][l][k]);
                                }
                            }
                        }
                    }else{
                        for(int l=0;l<n;l++){
                            if(j!=l){
                                dp[i][j][k]=min(dp[i][j][k],dp[i-1][l][k-1]+cost[i][j]);
                            }else{
                                dp[i][j][k]=min(dp[i][j][k],dp[i-1][l][k]+cost[i][j]);
                            }
                        }
                    }
                    //printf("dp[%d][%d][%d]:%d\n",i,j,k,dp[i][j][k]);
                }
            }
        }
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                for(int k=1;k<=target&&k<=i+1;k++){
                    printf("dp[%d][%d][%d]:%d\n",i,j,k,dp[i][j][k]);
                }
            }
        }
        int res=10001;
        if(houses[m-1]==0){
            for(int i=0;i<n;i++){
                res=min(res,dp[m-1][i][target]);
            }
        }else{
            res=dp[m-1][houses[m-1]][target];
        }
        
        return res==10001?-1:res;
    }
};

/* 
给定一个整数数组 A，你可以从某一起始索引出发，跳跃一定次数。
在你跳跃的过程中，第 1、3、5... 次跳跃称为奇数跳跃，而第 2、4、6... 次跳跃称为偶数跳跃。
你可以按以下方式从索引 i 向后跳转到索引 j（其中 i < j）：
在进行奇数跳跃时（如，第 1，3，5... 次跳跃），你将会跳到索引 j，使得 A[i] <= A[j]，A[j] 是可能的最小值。
如果存在多个这样的索引 j，你只能跳到满足要求的最小索引 j 上。
在进行偶数跳跃时（如，第 2，4，6... 次跳跃），你将会跳到索引 j，使得 A[i] >= A[j]，A[j] 是可能的最大值。
如果存在多个这样的索引 j，你只能跳到满足要求的最小索引 j 上。
（对于某些索引 i，可能无法进行合乎要求的跳跃。）

如果从某一索引开始跳跃一定次数（可能是 0 次或多次），就可以到达数组的末尾（索引 A.length - 1），那么该索引就会被认为是好的起始索引。
返回好的起始索引的数量。
975
*/

/* 
一只青蛙想要过河。 假定河流被等分为若干个单元格，并且在每一个单元格内都有可能放有一块石子（也有可能没有）。 青蛙可以跳上石子，但是不可以跳入水中。
给你石子的位置列表 stones（用单元格序号 升序 表示）， 请判定青蛙能否成功过河（即能否在最后一步跳至最后一块石子上）。
开始时， 青蛙默认已站在第一块石子上，并可以假定它第一步只能跳跃一个单位（即只能从单元格 1 跳至单元格 2 ）。
如果青蛙上一步跳跃了 k 个单位，那么它接下来的跳跃距离只能选择为 k - 1、k 或 k + 1 个单位。 另请注意，青蛙只能向前方（终点的方向）跳跃。
403
 */