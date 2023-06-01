#include "head.h"
/*
给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。

你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。

返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。
121
 */
// 超时
class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size(), res = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                res = max(res, prices[j] - prices[i]);
            }
        }
        return res;
    }
};
class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int res = 0, minn = prices[0];
        for (int i : prices)
        {
            res = max(res, i - minn);
            minn = min(i, minn);
        }
        return res;
    }
};
/*
给你一个整数数组 prices ，其中 prices[i] 表示某支股票第 i 天的价格。

在每一天，你可以决定是否购买和/或出售股票。你在任何时候 最多 只能持有 一股 股票。你也可以先购买，然后在 同一天 出售。

返回 你能获得的 最大 利润 。
122
 */
class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));
        dp[0][1] = -prices[0];
        for (int i = 1; i < n; i++)
        {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i][0] - prices[i]);
        }
        return dp[n][0];
    }
};
/*
给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
123
 */
class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        int dp[n + 1][2][3];
        memset(dp, 0, sizeof(dp));
        dp[0][1][1] = -prices[0];
        // 第一天进行了买-卖-买
        dp[0][1][2] = -prices[0];
        for (int i = 1; i < n; i++)
        {
            dp[i][1][1] = max(-prices[i], dp[i - 1][1][1]);
            dp[i][0][1] = max(dp[i][1][1] + prices[i], dp[i - 1][0][1]);
            dp[i][1][2] = max(dp[i][0][1] - prices[i], dp[i - 1][1][2]);
            dp[i][0][2] = max(dp[i][1][2] + prices[i], dp[i - 1][0][2]);
        }
        return max(dp[n - 1][0][1], dp[n - 1][0][2]);
    }
};
/*
给定一个整数数组 prices ，它的第 i 个元素 prices[i] 是一支给定的股票在第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）
188
 */
class Solution
{
public:
    int maxProfit(int k, vector<int> &prices)
    {
        int n = prices.size();
        int dp[n + 1][2][k + 1];
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= k; i++)
        {
            dp[0][1][i] = -prices[0];
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= k; j++)
            {
                dp[i][1][j] = max(dp[i][0][j - 1] - prices[i], dp[i - 1][1][j]);
                dp[i][0][j] = max(dp[i][1][j] + prices[i], dp[i - 1][0][j]);
            }
        }
        return dp[n][0][k];
    }
};
/*
给定一个整数数组prices，其中第  prices[i] 表示第 i 天的股票价格 。​

设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:

    卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
309
 */
class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        int dp[n + 1][2][2];
        memset(dp, 0, sizeof(dp));
        // 第一天买入
        dp[0][1][0] = -prices[0];
        for (int i = 1; i < n; i++)
        {
            dp[i][1][0] = max(dp[i - 1][0][0] - prices[i], dp[i - 1][1][0]);
            dp[i][0][1] = dp[i][1][0] + prices[i];
            dp[i][0][0] = max(dp[i - 1][0][1], dp[i - 1][0][0]);
        }
        return max(dp[n - 1][0][0], dp[n - 1][0][1]);
    }
};
/*
给定一个整数数组 prices，其中 prices[i]表示第 i 天的股票价格 ；整数 fee 代表了交易股票的手续费用。

你可以无限次地完成交易，但是你每笔交易都需要付手续费。如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。

返回获得利润的最大值。

注意：这里的一笔交易指买入持有并卖出股票的整个过程，每笔交易你只需要为支付一次手续费。
714
 */
class Solution
{
public:
    int maxProfit(vector<int> &prices, int fee)
    {
        int n = prices.size();
        int dp[n + 1][2];
        memset(dp, 0, sizeof(dp));
        dp[0][1] = -prices[0] - fee;
        dp[0][0] = -fee;
        for (int i = 1; i < n; i++)
        {
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - fee - prices[i]);
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
        }
        return dp[n - 1][0];
    }
};