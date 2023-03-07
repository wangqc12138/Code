#include "head.h"
class Solution {
public:
    int splitNum(int num) {
        string str = to_string(num);
        sort(str.begin(), str.end());
        string s1, s2;
        for (int i = 0; i <= str.size(); i++) {
            if (i % 2) {
                s1 += str[i];
            } else {
                s2 += str[i];
            }
        }
        return stoi(s1) + stoi(s2);
    }
};
class Solution {
public:
    long long coloredCells(int n) {
        long long t;
        int k = 2 * n - 1;
        int t = (1 + k) * n;
        return t + 2 * n + 1;
    }
};
class Solution {
public:
    int countWays(vector<vector<int>>& ranges) {
        auto cmp = [&](vector<int>& a, vector<int>& b) {
            return a[0] < b[0] || a[0] == b[0] && a[1] < b[1];
        };
        int res = 1;
        sort(ranges.begin(), ranges.end(), cmp);
        int right = -1;
        for (auto vec : ranges) {
            if (vec[0] > right) {
                res = res * 2 % 1000000007;
            }
            right = max(right, vec[1]);
        }
        return res;
    }
};
/*
Alice 有一棵 n 个节点的树，节点编号为 0 到 n - 1 。树用一个长度为 n - 1 的二维整数数组 edges 表示，其中 edges[i] = [ai, bi] ，表示树中节点 ai 和 bi 之间有一条边。

Alice 想要 Bob 找到这棵树的根。她允许 Bob 对这棵树进行若干次 猜测 。每一次猜测，Bob 做如下事情：

    选择两个 不相等 的整数 u 和 v ，且树中必须存在边 [u, v] 。
    Bob 猜测树中 u 是 v 的 父节点 。

Bob 的猜测用二维整数数组 guesses 表示，其中 guesses[j] = [uj, vj] 表示 Bob 猜 uj 是 vj 的父节点。

Alice 非常懒，她不想逐个回答 Bob 的猜测，只告诉 Bob 这些猜测里面 至少 有 k 个猜测的结果为 true 。

给你二维整数数组 edges ，Bob 的所有猜测和整数 k ，请你返回可能成为树根的 节点数目 。如果没有这样的树，则返回 0。

 */
// 换根dp
class Solution {
public:
    int rootCount(vector<vector<int>>& edges, vector<vector<int>>& guesses, int k) {
        vector<vector<int>> next(edges.size() + 1);
        set<pair<int, int>> st;
        for (auto vec : guesses) {
            st.emplace(pair<int, int>(vec[0], vec[1]));
        }
        for (auto vec : edges) {
            next[vec[0]].emplace_back(vec[1]);
            next[vec[1]].emplace_back(vec[0]);
        }
        int t = 0, res = 0;
        function<void(int, int)> dfs = [&](int x, int f) {
            for (auto y : next[x]) {
                if (y != f) {
                    t += st.count(pair<int, int>(x, y));
                    dfs(y, x);
                }
            }
        };
        function<void(int, int, int)> dfs1 = [&](int x, int f, int cnt) {
            res += cnt >= k;
            for (auto y : next[x]) {
                if (y != f) {
                    dfs1(y, x, cnt - st.count(pair<int, int>(x, y)) + st.count(pair<int, int>(y, x)));
                }
            }
        };
        dfs(0, -1);
        dfs1(0, -1, t);
        return res;
    }
};