#include "head.h"
/*
给你一个仅由 0 和 1 组成的二进制字符串 s 。

如果子字符串中 所有的 0 都在 1 之前 且其中 0 的数量等于 1 的数量，则认为 s 的这个子字符串是平衡子字符串。请注意，空子字符串也视作平衡子字符串。

返回  s 中最长的平衡子字符串长度。

子字符串是字符串中的一个连续字符序列。
 */
// 这种写法是01位置不限
class Solution {
public:
    int findTheLongestBalancedSubstring(string s) {
        map<int, int> mp;
        int k = 0, res = 0;
        mp[0] = -1;
        for (int i = 0; i <= s.size(); i++) {
            k += s[i] == '0' ? 1 : -1;
            if (mp.count(-k)) {
                res = max(res, i - mp[-k]);
            }
            if (!mp.count(k)) {
                mp[k] = i;
            }
        }
        return res;
    }
};
class Solution {
public:
    int findTheLongestBalancedSubstring(string s) {
        int n = s.size(), res = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '1') {
                continue;
            } else {
                int t = 0, j = i, k = 0;
                for (; j < n; j++) {
                    if (s[j] == '0') {
                        t++;
                    } else {
                        break;
                    }
                }
                for (; j < n; j++) {
                    if (s[j] == '1') {
                        if (++k == t) {
                            break;
                        }
                    } else {
                        break;
                    }
                }
                if (t == k) {
                    res = max(res, 2 * t);
                }
            }
        }
        return res;
    }
};
/*
给你一个整数数组 nums 。请你创建一个满足以下条件的二维数组：

    二维数组应该 只 包含数组 nums 中的元素。
    二维数组中的每一行都包含 不同 的整数。
    二维数组的行数应尽可能 少 。

返回结果数组。如果存在多种答案，则返回其中任何一种。

请注意，二维数组的每一行上可以存在不同数量的元素。
 */
class Solution {
public:
    vector<vector<int>> findMatrix(vector<int>& nums) {
        unordered_map<int, int> ump;
        int n = 0;
        for (auto i : nums) {
            n = max(n, ++ump[i]);
        }
        vector<vector<int>> res(n);
        for (auto [x, y] : ump) {
            for (int i = 0; i < y; i++) {
                res[i].emplace_back(x);
            }
        }
        return res;
    }
};
/*
有两只老鼠和 n 块不同类型的奶酪，每块奶酪都只能被其中一只老鼠吃掉。

下标为 i 处的奶酪被吃掉的得分为：

    如果第一只老鼠吃掉，则得分为 reward1[i] 。
    如果第二只老鼠吃掉，则得分为 reward2[i] 。

给你一个正整数数组 reward1 ，一个正整数数组 reward2 ，和一个非负整数 k 。

请你返回第一只老鼠恰好吃掉 k 块奶酪的情况下，最大 得分为多少。
 */
// dp超时
class Solution {
public:
    int miceAndCheese(vector<int>& reward1, vector<int>& reward2, int k) {
        int n = reward1.size();
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, INT_MIN));
        dp[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= min(k, i); j++) {
                if (j == 0) {
                    dp[i][j] = dp[i - 1][j] + reward2[i - 1];
                } else {
                    dp[i][j] = max(dp[i - 1][j] + reward2[i - 1], dp[i - 1][j - 1] + reward1[i - 1]);
                }
            }
        }
        return dp[n][k];
    }
};
class Solution {
public:
    int miceAndCheese(vector<int>& reward1, vector<int>& reward2, int k) {
        int n = reward1.size(), res = 0;
        vector<int> index(n);
        iota(index.begin(), index.end(), 0);
        sort(index.begin(), index.end(), [&](int i, int j) { return reward1[i] - reward2[i] > reward1[j] - reward2[j]; });

        for (int i = 0; i < n; i++) {
            if (i < k) {
                res += reward1[index[i]];
            } else {
                res += reward2[index[i]];
            }
        }
        return res;
    }
};