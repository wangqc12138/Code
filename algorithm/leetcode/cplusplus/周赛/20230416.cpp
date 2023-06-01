#include "head.h"
class Solution {
public:
    int addMinimum(string word) {
        int now = 0;
        int res = 0;
        for (int i = 0; i < word.size(); i++) {
            int t = word[i] - 'a';
            if (now != t) {
                i--;
                res++;
            }
            now = (now + 1) % 3;
        }
        if (now != 0) {
            res += 3 - now;
        }
        return res;
    }
};
/*
给你一个大小为 m x n 的二进制矩阵 mat ，请你找出包含最多 1 的行的下标（从 0 开始）以及这一行中 1 的数目。

如果有多行包含最多的 1 ，只需要选择 行下标最小 的那一行。

返回一个由行下标和该行中 1 的数量组成的数组。
 */
class Solution {
public:
    vector<int> rowAndMaximumOnes(vector<vector<int>>& mat) {
        vector<int> res(2, 0);
        for (int i = 0; i < mat.size(); i++) {
            int t = 0;
            for (auto j : mat[i]) {
                t += j;
            }
            if (res[1] < t) {
                res[0] = i;
                res[1] = t;
            }
        }
        return res;
    }
};

class Solution {
public:
    int maxDivScore(vector<int>& nums, vector<int>& divisors) {
        int res = INT_MAX, maxn = -1;
        for (auto i : divisors) {
            int t = 0;
            for (auto j : nums) {
                t += j % i == 0;
            }
            if (maxn <= t) {
                if (maxn == t) {
                    res = min(res, i);
                } else {
                    res = i;
                }
                maxn = max(maxn, t);
            }
        }
        return res;
    }
};
using pii = pair<int, int>;
class Solution {
public:
    int minimumTotalPrice(int n, vector<vector<int>>& edges, vector<int>& price, vector<vector<int>>& trips) {
        unordered_map<int, vector<int>> next;
        for (auto vec : edges) {
            next[vec[0]].emplace_back(vec[1]);
            next[vec[1]].emplace_back(vec[0]);
        }
        queue<int> mq;
        vector<int> p1 = price, p2 = price;
        vector<int> visit(n, 0);
        mq.emplace(0);
        bool flag = false;
        while (!mq.empty()) {
            int len = mq.size();
            for (int i = 0; i < len; i++) {
                int t = mq.front();
                mq.pop();
                if (visit[t]) {
                    continue;
                }
                visit[t] = 1;
                if (flag) {
                    p1[t] = price[t] / 2;
                } else {
                    p2[t] = price[t] / 2;
                }
                for (auto j : next[t]) {
                    if (!visit[j]) {
                        mq.emplace(j);
                    }
                }
            }
            flag = !flag;
        }
        for (auto i : p1) {
            cout << i << " ";
        }
        cout << endl;
        for (auto i : p2) {
            cout << i << " ";
        }
        cout << endl;
        auto cmp = [&](pii a, pii b) {
            return a.second > b.second;
        };
        auto help = [&](int i, int j, vector<int>& p) {
            priority_queue<pii, vector<pii>, decltype(cmp)> mpq(cmp);
            vector<int> v(n, 0);
            mpq.emplace(i, p[i]);
            while (!mpq.empty()) {
                auto [x, y] = mpq.top();
                mpq.pop();
                if (x == j) {
                    return y;
                }
                if (v[x]) {
                    continue;
                }
                v[x] = 1;
                for (auto nx : next[x]) {
                    if (!v[nx]) {
                        mpq.emplace(nx, y + p[nx]);
                    }
                }
            }
            return -1;
        };
        int r1 = 0, r2 = 0;
        vector<vector<int>> v1(n, vector<int>(n, -1));
        auto v2 = v1;
        for (auto vec : trips) {
            if (v1[vec[0]][vec[1]] == -1) {
                v1[vec[0]][vec[1]] = help(vec[0], vec[1], p1);
                v1[vec[1]][vec[0]] = help(vec[0], vec[1], p1);
            }
            r1 += v1[vec[0]][vec[1]];
            if (v2[vec[0]][vec[1]] == -1) {
                v2[vec[0]][vec[1]] = help(vec[0], vec[1], p2);
                v2[vec[1]][vec[0]] = help(vec[0], vec[1], p2);
            }
            r2 += v2[vec[0]][vec[1]];
        }
        cout << r1 << " " << r2 << endl;
        return min(r1, r2);
    }
};
/*
9
[[2,5],[3,4],[4,1],[1,7],[6,7],[7,0],[0,5],[5,8]]
[4,4,6,4,2,4,2,14,8]
[[1,5],[2,7],[4,3],[1,8],[2,8],[4,3],[1,5],[1,4],[2,1],[6,0],[0,7],[8,6],[4,0],[7,5],[7,5],[6,0],[5,1],[1,1],[7,5],[1,7],[8,7],[2,3],[4,1],[3,5],[2,5],[3,7],[0,1],[5,8],[5,3],[5,2]]
 */