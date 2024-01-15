#include "head.h"
/*
给你一个下标从 0 开始的字符串数组 words 和一个字符 x 。

请你返回一个 下标数组 ，表示下标在数组中对应的单词包含字符 x 。

注意 ，返回的数组可以是 任意 顺序。
 */
class Solution {
public:
    vector<int> findWordsContaining(vector<string>& words, char x) {
        vector<int> res;
        for (int i = 0; i < words.size(); i++) {
            if (set<char>(words[i].begin(), words[i].end()).count(x)) {
                res.emplace_back(i);
            }
        }
        return res;
    }
};
/*
给你一个网格图，由 n + 2 条 横线段 和 m + 2 条 竖线段 组成，一开始所有区域均为 1 x 1 的单元格。

所有线段的编号从 1 开始。

给你两个整数 n 和 m 。

同时给你两个整数数组 hBars 和 vBars 。

    hBars 包含区间 [2, n + 1] 内 互不相同 的横线段编号。
    vBars 包含 [2, m + 1] 内 互不相同的 竖线段编号。

如果满足以下条件之一，你可以 移除 两个数组中的部分线段：

    如果移除的是横线段，它必须是 hBars 中的值。
    如果移除的是竖线段，它必须是 vBars 中的值。

请你返回移除一些线段后（可能不移除任何线段），剩余网格图中 最大正方形 空洞的面积，正方形空洞的意思是正方形 内部 不含有任何线段。

 */
class Solution {
public:
    int maximizeSquareHoleArea(int n, int m, vector<int>& hBars, vector<int>& vBars) {
        sort(hBars.begin(), hBars.end());
        sort(vBars.begin(), vBars.end());
        int len = 1, l1 = 1, l2 = 1;
        for (int i = 1; i < hBars.size(); i++) {
            if (hBars[i] == hBars[i - 1] + 1) {
                len++;
            } else {
                l1 = max(len, l1);
                len = 1;
            }
        }
        l1 = max(len, l1);
        len = 1;
        for (int i = 1; i < vBars.size(); i++) {
            if (vBars[i] == vBars[i - 1] + 1) {
                len++;
            } else {
                l2 = max(len, l2);
                len = 1;
            }
        }
        l2 = max(len, l2);
        return pow(min(l1, l2) + 1, 2);
    }
};
/*
你在一个水果超市里，货架上摆满了玲琅满目的奇珍异果。

给你一个下标从 1 开始的数组 prices ，其中 prices[i] 表示你购买第 i 个水果需要花费的金币数目。

水果超市有如下促销活动：

    如果你花费 price[i] 购买了水果 i ，那么接下来的 i 个水果你都可以免费获得。

注意 ，即使你 可以 免费获得水果 j ，你仍然可以花费 prices[j] 个金币去购买它以便能免费获得接下来的 j 个水果。

请你返回获得所有水果所需要的 最少 金币数。
 */
class Solution {
public:
    int minimumCoins(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n + 1, vector<int>(2, INT_MAX));
        dp[1][1] = prices[0];
        for (int i = 1; i < n; i++) {
            for (int j = i + 1; i + i <= j && j <= n; j++) {
                dp[j][0] = min(dp[j][0], dp[i][1]);
                dp[j][1] = min(dp[j][1], dp[j][0] + prices[j - 1]);
            }
        }
        return min(dp[n][0], dp[n][1]);
    }
};