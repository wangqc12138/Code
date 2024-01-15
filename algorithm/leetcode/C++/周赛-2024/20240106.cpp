#include "head.h"
/*
给你两个正整数 x 和 y 。

一次操作中，你可以执行以下四种操作之一：

    如果 x 是 11 的倍数，将 x 除以 11 。
    如果 x 是 5 的倍数，将 x 除以 5 。
    将 x 减 1 。
    将 x 加 1 。

请你返回让 x 和 y 相等的 最少 操作次数。
T2998
 */
class Solution {
public:
    int minimumOperationsToMakeEqual(int x, int y) {
        using pii = pair<int, int>;
        auto cmp = [](pii a, pii b) {
            return a.second >= b.second;
        };
        priority_queue<pii, vector<pii>, decltype(cmp)> mpq(cmp);
        mpq.emplace(x, 0);
        vector<int> visit(10011, 0);
        int res = INT_MAX;
        while (!mpq.empty()) {
            auto t = mpq.top();
            mpq.pop();
            // cout << t.first << " " << t.second << endl;
            if (t.first <= y) {
                res = min(res, y - t.first + t.second);
                continue;
            }
            if (visit[t.first]) {
                continue;
            }
            visit[t.first] = 1;
            if (t.first % 11 == 0 && !visit[t.first / 11]) {
                mpq.emplace(t.first / 11, t.second + 1);
            }
            if (t.first % 5 == 0 && !visit[t.first / 5]) {
                mpq.emplace(t.first / 5, t.second + 1);
            }
            if (!visit[t.first - 1]) {
                mpq.emplace(t.first - 1, t.second + 1);
            }
            if (t.first % 11 >= 6 && !visit[t.first + 1]) {
                mpq.emplace(t.first + 1, t.second + 1);
            }
            if (t.first % 5 >= 3 && !visit[t.first + 1]) {
                mpq.emplace(t.first + 1, t.second + 1);
            }
        }
        return res;
    }
};

class Solution {
public:
    int minimumOperationsToMakeEqual(int x, int y) {
        using pii = pair<int, int>;
        queue<pii> mq;
        mq.emplace(x, 0);
        vector<int> visit(10011, 0);
        int res = INT_MAX;
        while (!mq.empty()) {
            auto t = mq.front();
            mq.pop();
            if (t.first <= y) {
                res = min(res, y - t.first + t.second);
                continue;
            }
            if (visit[t.first]) {
                continue;
            }
            visit[t.first] = 1;
            if (t.first % 11 == 0 && !visit[t.first / 11]) {
                mq.emplace(t.first / 11, t.second + 1);
            }
            if (t.first % 5 == 0 && !visit[t.first / 5]) {
                mq.emplace(t.first / 5, t.second + 1);
            }
            if (!visit[t.first - 1]) {
                mq.emplace(t.first - 1, t.second + 1);
            }
            if (t.first % 11 >= 6 && !visit[t.first + 1]) {
                mq.emplace(t.first + 1, t.second + 1);
            }
            if (t.first % 5 >= 3 && !visit[t.first + 1]) {
                mq.emplace(t.first + 1, t.second + 1);
            }
        }
        return res;
    }
};