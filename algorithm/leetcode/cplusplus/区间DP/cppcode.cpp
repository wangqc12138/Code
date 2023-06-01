#include "head.h"
/*
给你一个正整数数组 arr，考虑所有满足以下条件的二叉树：

    每个节点都有 0 个或是 2 个子节点。
    数组 arr 中的值与树的中序遍历中每个叶节点的值一一对应。
    每个非叶节点的值等于其左子树和右子树中叶节点的最大值的乘积。

在所有这样的二叉树中，返回每个非叶节点的值的最小可能总和。这个和的值是一个 32 位整数。

如果一个节点有 0 个子节点，那么该节点为叶节点。
T1130
 */
class Solution {
public:
    int mctFromLeafValues(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
        auto mx = dp;
        for (int i = 0; i < n; i++) {
            mx[i][i] = arr[i];
            dp[i][i] = 0;
        }
        /* 这样有问题子区间没计算就计算了大区间 */
        // for (int i = 0; i < n; i++) {
        //     for (int j = i + 1; j < n; j++) {
        //         mx[i][j] = max(mx[i][j - 1], arr[j]);
        //         for (int k = i; k < j; k++) {
        //             dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + mx[i][k] * mx[k + 1][j]);
        //         }
        //     }
        // }
        for (int len = 1; len < n; len++) {
            for (int i = 0; i + len < n; i++) {
                int j = i + len;
                mx[i][j] = max(mx[i][j - 1], arr[j]);
                for (int k = i; k < j; k++) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + mx[i][k] * mx[k + 1][j]);
                }
            }
        }
        return dp[0][n - 1];
    }
};
/*
你有一个凸的 n 边形，其每个顶点都有一个整数值。给定一个整数数组 values ，其中 values[i] 是第 i 个顶点的值（即 顺时针顺序 ）。

假设将多边形 剖分 为 n - 2 个三角形。对于每个三角形，该三角形的值是顶点标记的乘积，三角剖分的分数是进行三角剖分后所有 n - 2 个三角形的值之和。

返回 多边形进行三角剖分后可以得到的最低分 。
T1039
 */
class Solution {
public:
    int minScoreTriangulation(vector<int>& values) {
        int n = values.size();
        vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
        for (int i = 0; i < n; i++) {
            dp[i][i] = 0;
            if (i < n - 1) {
                dp[i][i + 1] = 0;
            }
        }
        for (int len = 2; len < n; len++) {
            for (int i = 0; i + len < n; i++) {
                int j = i + len;
                for (int k = i + 1; k < j; k++) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j] + values[i] * values[j] * values[k]);
                }
            }
        }
        return dp[0][n - 1];
    }
};