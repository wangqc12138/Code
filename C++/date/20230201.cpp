#include "head.h"
/*
在第 1 天，有一个人发现了一个秘密。

给你一个整数 delay ，表示每个人会在发现秘密后的 delay 天之后，每天 给一个新的人 分享 秘密。
同时给你一个整数 forget ，表示每个人在发现秘密 forget 天之后会 忘记 这个秘密。一个人 不能 在忘记秘密那一天及之后的日子里分享秘密。

给你一个整数 n ，请你返回在第 n 天结束时，知道秘密的人数。由于答案可能会很大，请你将结果对 109 + 7 取余 后返回。
2327
 */
class Solution
{
public:
    const int MOD = 1e9 + 7;
    int peopleAwareOfSecret(int n, int delay, int forget)
    {
        vector<int> dp(n);
        dp[0] = 1;
        int res = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + delay; j < i + forget; j++)
            {
                if (j < n)
                {
                    dp[j] += dp[i];
                    dp[j] %= MOD;
                }
            }
            if (i >= n - forget)
            {
                res += dp[i];
                res %= MOD;
            }
        }
        return res;
    }
};
/*
给你一个 m x n 的整数网格图 grid ，你可以从一个格子移动到 4 个方向相邻的任意一个格子。

请你返回在网格图中从 任意 格子出发，达到 任意 格子，且路径中的数字是 严格递增 的路径数目。由于答案可能会很大，请将结果对 109 + 7 取余 后返回。

如果两条路径中访问过的格子不是完全相同的，那么它们视为两条不同的路径。
2328
 */
class Solution
{
public:
    int countPaths(vector<vector<int>> &grid)
    {
        int res = 0, m = grid.size(), n = grid[0].size();
        vector<vector<int>> ready(m, vector<int>(n, -1));
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                res += dfs(grid, ready, m, n, i, j);
                res %= 1000000007;
            }
        }
        return res;
    }
    vector<pair<int, int>> dir = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    int dfs(vector<vector<int>> &grid, vector<vector<int>> &ready, int m, int n, int i, int j)
    {
        if (ready[i][j] != -1)
        {
            return ready[i][j];
        }
        int t = 1;
        for (auto [a, b] : dir)
        {
            int x = a + i, y = b + j;
            if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] <= grid[i][j])
            {
                continue;
            }
            t += dfs(grid, ready, m, n, x, y);
            t %= 1000000007;
        }
        return ready[i][j] = t;
    }
};
/*
给定一个 m x n 整数矩阵 matrix ，找出其中 最长递增路径 的长度。

对于每个单元格，你可以往上，下，左，右四个方向移动。 你 不能 在 对角线 方向上移动或移动到 边界外（即不允许环绕）。
329
 */
class Solution
{
public:
    int longestIncreasingPath(vector<vector<int>> &grid)
    {
        int res = 0, m = grid.size(), n = grid[0].size();
        vector<vector<int>> ready(m, vector<int>(n, -1));
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                res = max(res, dfs(grid, ready, m, n, i, j));
            }
        }
        return res;
    }
    vector<pair<int, int>> dir = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    int dfs(vector<vector<int>> &grid, vector<vector<int>> &ready, int m, int n, int i, int j)
    {
        if (ready[i][j] != -1)
        {
            return ready[i][j];
        }
        int t = 0;
        for (auto [a, b] : dir)
        {
            int x = a + i, y = b + j;
            if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] <= grid[i][j])
            {
                continue;
            }
            t = max(dfs(grid, ready, m, n, x, y), t);
        }
        return ready[i][j] = t + 1;
    }
};

class Solution
{
public:
    vector<pair<int, int>> dir = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    int longestIncreasingPath(vector<vector<int>> &matrix)
    {
        int m = matrix.size(), n = matrix[0].size(), res = 0;
        vector<vector<int>> next(m * n);
        vector<int> in_(m * n);
        queue<int> mq;

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                for (auto [a, b] : dir)
                {
                    if (a + i < 0 || a + i >= m || b + j < 0 || b + j >= n)
                    {
                        continue;
                    }
                    if (matrix[a + i][b + j] > matrix[i][j])
                    {
                        next[i * n + j].emplace_back((i + a) * n + j + b);
                        in_[(i + a) * n + j + b]++;
                    }
                }
            }
        }

        for (int i = 0; i < m * n; i++)
        {
            if (in_[i] == 0)
            {
                mq.emplace(i);
            }
        }
        while (!mq.empty())
        {
            int len = mq.size();
            for (int i = 0; i < len; i++)
            {
                int k = mq.front();
                mq.pop();
                for (int j : next[k])
                {
                    if (--in_[j] == 0)
                    {
                        mq.emplace(j);
                    }
                }
            }
            res++;
        }
        return res;
    }
};
/*
给你两个整数：m 和 n ，表示矩阵的维数。

另给你一个整数链表的头节点 head 。

请你生成一个大小为 m x n 的螺旋矩阵，矩阵包含链表中的所有整数。链表中的整数从矩阵 左上角 开始、顺时针 按 螺旋 顺序填充。如果还存在剩余的空格，则用 -1 填充。

返回生成的矩阵。
2326
 */
class Solution
{
public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode *head)
    {
        vector<vector<int>> res(m, vector<int>(n, -1));
        int a = 0, b = 0, c = m - 1, d = n - 1, index = 0;
        vector<int> nums;
        while (!head)
        {
            nums.emplace_back(head->val);
            head = head->next;
        }
        while (nums.size() < m * n)
        {
            nums.emplace_back(-1);
        }
        if (nums.size() == 1)
        {
            res[0][0] = nums[0];
        }
        while (a <= c && b <= d)
        {
            help(res, nums, a, b, c, d, index);
            a++, b++, c--, d--;
        }
        return res;
    }
    void help(vector<vector<int>> &matrix, vector<int> &nums, int a, int b, int c, int d, int &index)
    {
        int i = a, j = b;
        for (; j < d; j++)
        {
            matrix[i][j] = nums[index++];
        }
        for (; i < c; i++)
        {
            matrix[i][j] = nums[index++];
        }
        for (; j > b; j--)
        {
            matrix[i][j] = nums[index++];
        }
        for (; i > a; i--)
        {
            matrix[i][j] = nums[index++];
        }
    }
};
class Solution
{
public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode *head)
    {
        vector<vector<int>> res(m, vector<int>(n, -1));
        int a = 0, b = 0, c = m - 1, d = n - 1;
        while (head)
        {
            for (int i = b; i <= d && head; i++)
            {
                res[a][i] = head->val;
                head = head->next;
            }
            a++;
            for (int i = a; i <= c && head; i++)
            {
                res[i][d] = head->val;
                head = head->next;
            }
            d--;
            for (int i = d; i >= b && head; i--)
            {
                res[c][i] = head->val;
                head = head->next;
            }
            c--;
            for (int i = c; i >= a && head; i--)
            {
                res[i][b] = head->val;
                head = head->next;
            }
            b++;
        }
        return res;
    }
};