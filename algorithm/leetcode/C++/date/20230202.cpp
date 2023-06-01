#include "head.h"
/*
给你两个长度相等的整数数组，返回下面表达式的最大值：

|arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| + |i - j|

其中下标 i，j 满足 0 <= i, j < arr1.length。
1131
 */
class Solution
{
public:
    int maxAbsValExpr(vector<int> &arr1, vector<int> &arr2)
    {
        int res = -1;
        for (int i = 0; i < arr1.size(); i++)
        {
            for (int j = 0; j < arr2.size(); j++)
            {
                res = max(res, abs(arr1[i] - arr1[j]) + abs(arr2[i] - arr2[j]) + abs(i - j));
            }
        }
        return res;
    }
};
/*
给你一个数组 arr ，请你将每个元素用它右边最大的元素替换，如果是最后一个元素，用 -1 替换。

完成所有替换操作后，请你返回这个数组。
1299
 */
class Solution
{
public:
    vector<int> replaceElements(vector<int> &arr)
    {
        int m = -1;
        for (int i = arr.size() - 1; i >= 0; i--)
        {
            int k = max(m, arr[i]);
            arr[i] = m;
            m = k;
        }
        return arr;
    }
};
/*
给你一个正方形字符数组 board ，你从数组最右下方的字符 'S' 出发。

你的目标是到达数组最左上角的字符 'E' ，数组剩余的部分为数字字符 1, 2, ..., 9 或者障碍 'X'。
！！！！在每一步移动中，你可以向上、向左或者左上方移动，可以移动的前提是到达的格子没有障碍。

一条路径的 「得分」 定义为：路径上所有数字的和。

请你返回一个列表，包含两个整数：第一个整数是 「得分」 的最大值，第二个整数是得到最大得分的方案数，请把结果对 10^9 + 7 取余。

如果没有任何路径可以到达终点，请返回 [0, 0] 。
1301
 */
// dijsktra用不了最长路径！思路就错了！
//  using pii=pair<int,int>;
//  using ppi=pair<pii,int>;
//  class Solution {
//  public:
//      vector<int> pathsWithMaxScore(vector<string>& board) {
//          int m=board.size(),n=board[0].size();
//          int visit[m][n][3];
//          board[0][0]='0',board[m-1][n-1]='0';
//          memset(visit,0,sizeof(visit));
//          visit[m-1][n-1][2]=1;
//          auto cmp=[&](ppi i,ppi j){return i.second<j.second;};
//          priority_queue<ppi,vector<ppi>,decltype(cmp)> mpq(cmp);
//          mpq.emplace(ppi({m-1,n-1},0));
//          vector<pii> dir={{0,-1},{0,1},{-1,0},{1,0}};
//          while(!mpq.empty()){
//              auto [x,y] = mpq.top().first;
//              auto t=mpq.top().second;
//              mpq.pop();
//              if(visit[x][y][0]==1){
//                  continue;
//              }
//              visit[x][y][0]=1;
//              if(x==0&&y==0){
//                  break;
//              }
//              for(auto [a,b]:dir){
//                  if(x+a<0||x+a>=m||y+b<0||y+b>=n||board[x+a][y+b]=='X'||visit[x+a][y+b][0]!=0||board[x+a][y+b]+t-'0'<visit[x+a][y+b][1]){
//                      continue;
//                  }
//                  if(board[x+a][y+b]+t-'0'>visit[x+a][y+b][1]){
//                      visit[x+a][y+b][1]=board[x+a][y+b]+t-'0';
//                      visit[x+a][y+b][2]=visit[x][y][2];
//                  }else if(board[x+a][y+b]+t-'0'==visit[x+a][y+b][1]){
//                      visit[x+a][y+b][2]+=visit[x][y][2];
//                  }
//                  mpq.emplace(ppi({x+a,y+b},board[x+a][y+b]+t-'0'));
//              }
//          }
//          return {visit[0][0][1],visit[0][0][2]};
//      }
//  };
class Solution
{
public:
    vector<int> pathsWithMaxScore(vector<string> &board)
    {
        int n = board.size();
        vector<vector<int>> grade(n, vector<int>(n, 0)), dir(n, vector<int>(n, 0));
        dir[n - 1][n - 1] = 1, board[0][0] = '0', board[n - 1][n - 1] = '0';
        auto update = [&](int x, int y, int a, int b)
        {
            if (x < 0 || y < 0 || board[x][y] == 'X' || dir[a][b] == 0 || grade[x][y] > grade[a][b] + board[x][y] - '0')
            {
                return;
            }
            if (grade[x][y] == grade[a][b] + board[x][y] - '0')
            {
                dir[x][y] += dir[a][b];
            }
            else if (grade[x][y] < grade[a][b] + board[x][y] - '0')
            {
                grade[x][y] = grade[a][b] + board[x][y] - '0';
                dir[x][y] = dir[a][b];
            }
            dir[x][y] %= 1000000007;
        };
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = n - 1; j >= 0; j--)
            {
                update(i - 1, j, i, j);
                update(i, j - 1, i, j);
                update(i - 1, j - 1, i, j);
            }
        }
        return {grade[0][0], dir[0][0]};
    }
};
/*
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。

问总共有多少条不同的路径？
62
 */
class Solution
{
public:
    int uniquePaths(int m, int n)
    {
        int dp[m][n];
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                dp[i][j] += (i == 0 ? 0 : dp[i - 1][j]) + (j == 0 ? 0 : dp[i][j - 1]);
            }
        }
        return dp[m - 1][n - 1];
    }
};
/*
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish”）。

现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？

网格中的障碍物和空位置分别用 1 和 0 来表示。
63
 */
class Solution
{
public:
    int uniquePathsWithObstacles(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        int dp[m][n];
        memset(dp, 0, sizeof(dp));
        dp[0][0] = !grid[0][0];
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 1)
                {
                    continue;
                }
                dp[i][j] += (i == 0 ? 0 : dp[i - 1][j]) + (j == 0 ? 0 : dp[i][j - 1]);
            }
        }
        return dp[m - 1][n - 1];
    }
};
/*
给定一个三角形 triangle ，找出自顶向下的最小路径和。

每一步只能移动到下一行中相邻的结点上。相邻的结点 在这里指的是 下标 与 上一层结点下标 相同或者等于 上一层结点下标 + 1 的两个结点。
也就是说，如果正位于当前行的下标 i ，那么下一步可以移动到下一行的下标 i 或 i + 1 。
120
 */
class Solution
{
public:
    int minimumTotal(vector<vector<int>> &triangle)
    {
        int n = triangle.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        dp[0][0] = triangle[0][0];
        for (int i = 1; i < n; i++)
        {
            dp[i][0] = dp[i - 1][0] + triangle[i][0];
            for (int j = 1; j < triangle[i].size() - 1; j++)
            {
                dp[i][j] = min(dp[i - 1][j], dp[i - 1][j - 1]) + triangle[i][j];
            }
            dp[i][triangle[i].size() - 1] = dp[i - 1][triangle[i].size() - 2] + triangle[i][triangle[i].size() - 1];
        }
        return *min_element(dp[n - 1].begin(), dp[n - 1].end());
    }
};

class Solution
{
public:
    int minimumTotal(vector<vector<int>> &triangle)
    {
        int n = triangle.size();
        vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
        dp[0][0] = triangle[0][0];
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < triangle[i].size(); j++)
            {
                dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + triangle[i + 1][j]);
                dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + triangle[i + 1][j + 1]);
            }
        }
        return *min_element(dp[n - 1].begin(), dp[n - 1].end());
    }
};

/*
给你一个 n x n 的 方形 整数数组 matrix ，请你找出并返回通过 matrix 的下降路径 的 最小和 。

下降路径 可以从第一行中的任何元素开始，并从每一行中选择一个元素。在下一行选择的元素和当前行所选元素最多相隔一列（即位于正下方或者沿对角线向左或者向右的第一个元素）。
具体来说，位置 (row, col) 的下一个元素应当是 (row + 1, col - 1)、(row + 1, col) 或者 (row + 1, col + 1) 。
931
 */
class Solution
{
public:
    int minFallingPathSum(vector<vector<int>> &matrix)
    {
        int n = matrix.size();
        vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
        dp[0] = matrix[0];
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n; j++)
            {
                dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + matrix[i + 1][j]);
                if (j > 0)
                    dp[i + 1][j - 1] = min(dp[i + 1][j - 1], dp[i][j] + matrix[i + 1][j - 1]);
                if (j < n - 1)
                    dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + matrix[i + 1][j + 1]);
            }
        }
        return *min_element(dp[n - 1].begin(), dp[n - 1].end());
    }
};