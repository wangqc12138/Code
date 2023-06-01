#include "head.h"
/*
给你一个正整数 n 。n 中的每一位数字都会按下述规则分配一个符号：

    最高有效位 上的数字分配到 正 号。
    剩余每位上数字的符号都与其相邻数字相反。

返回所有数字及其对应符号的和。
 */
class Solution {
public:
    int alternateDigitSum(int n) {
        string str = to_string(n);
        int t = 1, res = 0;
        for (auto c : str) {
            res += t * (c - '0');
            t *= -1;
        }
        return res;
    }
};
/*
班里有 m 位学生，共计划组织 n 场考试。
给你一个下标从 0 开始、大小为 m x n 的整数矩阵 score ，其中每一行对应一位学生，
而 score[i][j] 表示第 i 位学生在第 j 场考试取得的分数。
矩阵 score 包含的整数 互不相同 。

另给你一个整数 k 。请你按第 k 场考试分数从高到低完成对这些学生（矩阵中的行）的排序。

返回排序后的矩阵。

 */
class Solution {
public:
    vector<vector<int>> sortTheStudents(vector<vector<int>>& score, int k) {
        auto cmp = [&](const auto& v1, const auto& v2) {
            return v1[k] >= v2[k];
        };
        sort(score.begin(), score.end(), cmp);
        return score;
    }
};
/*
给你两个下标从 0 开始的 二元 字符串 s 和 target ，两个字符串的长度均为 n 。你可以对 s 执行下述操作 任意 次：

    选择两个 不同 的下标 i 和 j ，其中 0 <= i, j < n 。
    同时，将 s[i] 替换为 (s[i] OR s[j]) ，s[j] 替换为 (s[i] XOR s[j]) 。

例如，如果 s = "0110" ，你可以选择 i = 0 和 j = 2，
然后同时将 s[0] 替换为 (s[0] OR s[2] = 0 OR 1 = 1)，并将 s[2] 替换为 (s[0] XOR s[2] = 0 XOR 1 = 1)，最终得到 s = "1110" 。

如果可以使 s 等于 target ，返回 true ，否则，返回 false 。
00--00--00
01--11
11--10--11
10--11
 */
class Solution {
public:
    bool makeStringsEqual(string s, string target) {
        int i0 = count(s.begin(), s.end(), '0');
        int j0 = count(target.begin(), target.end(), '0');
        return i0 == s.size() && j0 == s.size() || i0 < s.size() && j0 < s.size();
    }
};
/*
给你一个整数数组 nums 和一个整数 k 。

将数组拆分成一些非空子数组。拆分的 代价 是每个子数组中的 重要性 之和。

令 trimmed(subarray) 作为子数组的一个特征，其中所有仅出现一次的数字将会被移除。

    例如，trimmed([3,1,2,4,3,4]) = [3,4,3,4] 。

子数组的 重要性 定义为 k + trimmed(subarray).length 。

    例如，如果一个子数组是 [1,2,3,3,3,4,4] ，trimmed([1,2,3,3,3,4,4]) = [3,3,3,4,4] 。这个子数组的重要性就是 k + 5 。

找出并返回拆分 nums 的所有可行方案中的最小代价。

子数组 是数组的一个连续 非空 元素序列。
 */
class Solution {
public:
    int minCost(vector<int>& nums, int k) {
        map<int, int> mp;
        for (auto i : nums) {
            mp[i]++;
        }
        vector<int> vec;
        for (auto i : nums) {
            if (mp[i] > 1) {
                vec.emplace_back(i);
            }
        }
        int n = vec.size();
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        int temp[nums.size()];
        for (int i = 1; i <= n; i++) {
            int len = 0;
            memset(temp, 0, sizeof(temp));
            for (int j = i - 1; j >= 0; j--) {
                temp[vec[j]]++;
                if (temp[vec[j]] == 2) {
                    len += 2;
                } else if (temp[vec[j]] > 2) {
                    len++;
                }
                dp[i] = min(dp[i], dp[j] + len + k);
            }
        }
        return dp[n];
    }
};
/*
给定一个数组 books ，其中 books[i] = [thicknessi, heighti] 表示第 i 本书的厚度和高度。你也会得到一个整数 shelfWidth 。

按顺序 将这些书摆放到总宽度为 shelfWidth 的书架上。

先选几本书放在书架上（它们的厚度之和小于等于书架的宽度 shelfWidth ），然后再建一层书架。重复这个过程，直到把所有的书都放在书架上。

需要注意的是，在上述过程的每个步骤中，摆放书的顺序与你整理好的顺序相同。

    例如，如果这里有 5 本书，那么可能的一种摆放情况是：第一和第二本书放在第一层书架上，第三本书放在第二层书架上，第四和第五本书放在最后一层书架上。

每一层所摆放的书的最大高度就是这一层书架的层高，书架整体的高度为各层高之和。

以这种方式布置书架，返回书架整体可能的最小高度。
 */