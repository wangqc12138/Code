#include "head.h"
class Solution {
public:
    int differenceOfSum(vector<int>& nums) {
        int res = 0;
        for (auto i : nums) {
            res += i;
            for (auto c : to_string(i)) {
                res -= c - '0';
            }
        }
        return res;
    }
};
/* 给你一个正整数 n ，表示最初有一个 n x n 、下标从 0 开始的整数矩阵 mat ，矩阵中填满了 0 。

另给你一个二维整数数组 query 。针对每个查询 query[i] = [row1i, col1i, row2i, col2i] ，请你执行下述操作：

    找出 左上角 为 (row1i, col1i) 且 右下角 为 (row2i, col2i) 的子矩阵，将子矩阵中的 每个元素 加 1 。也就是给所有满足 row1i <= x <= row2i 和 col1i <= y <= col2i 的 mat[x][y] 加 1 。

返回执行完所有操作后得到的矩阵 mat 。
 */
// 超时
class Solution {
public:
    vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& queries) {
        vector<vector<int>> res(n, vector<int>(n, 0));
        for (auto vec : queries) {
            for (int i = vec[0]; i <= vec[1]; i++) {
                for (int j = vec[2]; j <= vec[3]; j++) {
                    res[i][j]++;
                }
            }
        }
        return res;
    }
};
// 二维前缀和
class Solution {
public:
    vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& queries) {
        vector<vector<int>> pre(n, vector<int>(n, 0));
        for (auto vec : queries) {
        }
    }
};