#include "head.h"
class Solution {
public:
    vector<int> leftRigthDifference(vector<int>& nums) {
        vector<int> sum = nums, res(nums.size());
        int n = nums.size();
        for (int i = 1; i < nums.size(); i++) {
            sum[i] += sum[i - 1];
        }
        res[0] = abs(sum[n - 1]);
        for (int i = 1; i < nums.size(); i++) {
            res[i] = abs(sum[n - 1] - sum[i - 1]);
        }
        return res;
    }
};

class Solution {
public:
    vector<int> divisibilityArray(string word, int m) {
        int t = 0, n = word.size();
        vector<int> res(n, 0);
        for (int i = 0; i < word.size(); i++) {
            t *= 10;
            t += word[i] - '0';
            if (t % m == 0) {
                res[i] = 1;
            }
            t %= m;
        }
        return res;
    }
};
// [1,78,27,48,14,86,79,68,77,20,57,21,18,67,5,51,70,85,47,56,22,79,41,8,39,81,59,74,14,45,49,15,10,28,16,77,22,65,8,36,79,94,44,80,72,8,96,78,39,92,69,55,9,44,26,76,40,77,16,69,40,64,12,48,66,7,59,10]
// 1 5 7 8 8 8 9 10 10 12 14 14 15 16 16 18 20 21 22 22 26 27 28 36 39 39 40 40 41 44 44 45 47 48 48 49 51 55 56 57 59 59 64 65 66 67 68 69 69 70 72 74 76 77 77 77 78 78 79 79 79 80 81 85 86 92 94 96
class Solution {
public:
    int maxNumOfMarkedIndices(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int res = 0, n = nums.size(), i = 0, j = n / 2;
        vector<int> visit(n, 0);
        for (; i < n / 2 && j < n; i++) {
            if (visit[i]) {
                continue;
            }
            for (; j < n; j++) {
                if (nums[i] * 2 <= nums[j]) {
                    visit[i] = 1;
                    visit[j] = 1;
                    res += 2;
                    break;
                }
            }
        }
        return res;
    }
};

using pii = pair<int, int>;
class Solution {
public:
    int minimumTime(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), res = 0;
        auto temp = grid;
        if (grid[0][1] > 1 && grid[1][0] > 1) {
            return -1;
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int t = i + j;
                if (temp[i][j] > t && t % 2 != temp[i][j] % 2) {
                    temp[i][j]++;
                }
                if (i == 0 && j == 0) {
                    continue;
                } else if (i == 0) {
                    temp[i][j] = max(temp[i][j], temp[i][j - 1] + 1);
                } else if (j == 0) {
                    temp[i][j] = max(temp[i][j], temp[i - 1][j] + 1);
                } else {
                    temp[i][j] = max(temp[i][j], min(temp[i][j - 1], temp[i - 1][j]) + 1);
                }
            }
        }
        return temp[m - 1][n - 1];
    }
};

/*
给你一个 m x n 的矩阵 grid ，每个元素都为 非负 整数，其中 grid[row][col] 表示可以访问格子 (row, col) 的 最早 时间。也就是说当你访问格子 (row, col) 时，最少已经经过的时间为 grid[row][col] 。

你从 最左上角 出发，出发时刻为 0 ，你必须一直移动到上下左右相邻四个格子中的 任意 一个格子（即不能停留在格子上）。每次移动都需要花费 1 单位时间。

请你返回 最早 到达右下角格子的时间，如果你无法到达右下角的格子，请你返回 -1 。
2577
 */
using pii = pair<int, int>;
class Solution {
public:
    int minimumTime(vector<vector<int>>& grid) {
        if (grid[0][1] > 1 && grid[1][0] > 1) {
            return -1;
        }
        auto cmp = [&](pii a, pii b) { return a.second > b.second; };
        priority_queue<pii, vector<pii>, decltype(cmp)> mpq(cmp);
        int m = grid.size(), n = grid[0].size();
        set<int> visit;
        mpq.emplace(0, 0);
        vector<pii> dir = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
        while (!mpq.empty()) {
            int x = mpq.top().first / n, y = mpq.top().first % n, t = mpq.top().second;
            mpq.pop();
            if (x == m - 1 && y == n - 1) {
                return t;
            }
            if (visit.count(x * n + y)) {
                continue;
            }
            visit.emplace(x * n + y);
            for (auto [a, b] : dir) {
                int xx = x + a, yy = y + b;
                if (xx < 0 || xx >= m || yy < 0 || yy >= n || visit.count(xx * n + yy)) {
                    continue;
                }
                if ((xx + yy) % 2 != grid[xx][yy] % 2) {
                    grid[xx][yy]++;
                }
                mpq.emplace(xx * n + yy, max(grid[xx][yy], t + 1));
            }
        }
        return 0;
    }
};