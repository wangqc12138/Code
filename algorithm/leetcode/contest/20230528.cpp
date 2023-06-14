#include "head.h"
/*
给你一个用字符串表示的正整数 num ，请你以字符串形式返回不含尾随零的整数 num 。
 */
class Solution {
public:
    string removeTrailingZeros(string num) {
        while (num.back() == '0') {
            num.pop_back();
        }
        return num;
    }
};
/*
给你一个下标从 0 开始、大小为 m x n 的二维矩阵 grid ，请你求解大小同样为 m x n 的答案矩阵 answer 。

矩阵 answer 中每个单元格 (r, c) 的值可以按下述方式进行计算：

    令 topLeft[r][c] 为矩阵 grid 中单元格 (r, c) 左上角对角线上 不同值 的数量。
    令 bottomRight[r][c] 为矩阵 grid 中单元格 (r, c) 右下角对角线上 不同值 的数量。

然后 answer[r][c] = |topLeft[r][c] - bottomRight[r][c]| 。

返回矩阵 answer 。

矩阵对角线 是从最顶行或最左列的某个单元格开始，向右下方向走到矩阵末尾的对角线。

如果单元格 (r1, c1) 和单元格 (r, c) 属于同一条对角线且 r1 < r ，则单元格 (r1, c1) 属于单元格 (r, c) 的左上对角线。类似地，可以定义右下对角线。
范围小，直接暴力就可以的
 */
class Solution {
public:
    vector<vector<int>> differenceOfDistinctValues(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<set<int>>> pre(m, vector<set<int>>(n, set<int>()));
        auto p = pre;
        vector<vector<int>> res(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i > 0 && j > 0) {
                    pre[i][j] = pre[i - 1][j - 1];
                    res[i][j] = pre[i - 1][j - 1].size();
                }
                pre[i][j].emplace(grid[i][j]);
            }
        }
        pre = p;
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (i < m - 1 && j < n - 1) {
                    pre[i][j] = pre[i + 1][j + 1];
                    res[i][j] -= pre[i + 1][j + 1].size();
                }
                res[i][j] = abs(res[i][j]);
                pre[i][j].emplace(grid[i][j]);
            }
        }
        return res;
    }
};
/*
给你一个下标从 0 开始、长度为 n 的二进制字符串 s ，你可以对其执行两种操作：

    选中一个下标 i 并且反转从下标 0 到下标 i（包括下标 0 和下标 i ）的所有字符，成本为 i + 1 。
    选中一个下标 i 并且反转从下标 i 到下标 n - 1（包括下标 i 和下标 n - 1 ）的所有字符，成本为 n - i 。

返回使字符串内所有字符 相等 需要的 最小成本 。

反转 字符意味着：如果原来的值是 '0' ，则反转后值变为 '1' ，反之亦然。
 */
class Solution {
public:
    long long minimumCost(string s) {
        int n = s.size();
        vector<vector<long long>> v1(n, vector<long long>(2, 0));
        auto v2 = v1;
        v1[0][!(s[0] - '0')] = 1;
        v2[n - 1][!(s[n - 1] - '0')] = 1;
        for (int i = 1; i < n; i++) {
            int t = s[i] - '0';
            v1[i][t] = min(v1[i - 1][t], v1[i - 1][!t] + i);
            v1[i][!t] = min(v1[i - 1][!t] + 2 * i + 1, v1[i - 1][t] + i + 1);
        }
        for (int i = n - 2; i >= 0; i--) {
            int t = s[i] - '0';
            v2[i][t] = min(v2[i + 1][t], v2[i + 1][!t] + n - i - 1);
            v2[i][!t] = min(v2[i + 1][!t] + 2 * (n - i) - 1, v2[i + 1][t] + n - i);
        }
        long long res = LONG_MAX;
        for (int i = 0; i < n; i++) {
            res = min(res, min(v1[i][0] + v2[i][0], v1[i][1] + v2[i][1]));
        }
        return res;
    }
};
/*
翻转一段字符串，该字符串内部差异仍然保持不变！，所以每次只要找翻转前面和翻转后面的最小值即可！
 */
class Solution {
public:
    long long minimumCost(string s) {
        long long res = 0;
        int n = s.size();
        for (int i = 1; i < n; i++) {
            if (s[i] != s[i - 1]) {
                res += min(i, n - i);
            }
        }
        return res;
    }
};