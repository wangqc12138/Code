#include "head.h"
class Solution {
public:
    vector<int> numberGame(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        auto res = nums;
        for (int i = 0; i < nums.size(); i += 2) {
            res[i] = nums[i + 1];
            res[i + 1] = nums[i];
        }
        return res;
    }
};

class Solution {
public:
    int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences) {
        sort(hFences.begin(), hFences.end());
        sort(vFences.begin(), vFences.end());
        unordered_set<int> st1, st2;
        st1.emplace(m - 1);
        st2.emplace(n - 1);
        for (int i = 0; i < hFences.size(); i++) {
            st1.emplace(m - hFences[i]);
            st1.emplace(hFences[i] - 1);
            for (int j = i + 1; j < hFences.size(); j++) {
                st1.emplace(hFences[j] - hFences[i]);
            }
        }
        int t = -1;
        if (st1.count(n - 1)) {
            t = max(t, n - 1);
            return t == -1 ? -1 : (long long)t * t % 1000000007;
        }
        for (int i = 0; i < vFences.size(); i++) {
            if (st1.count(n - vFences[i])) {
                t = max(t, n - vFences[i]);
            }
            if (st1.count(vFences[i] - 1)) {
                t = max(t, vFences[i] - 1);
            }
            for (int j = i + 1; j < vFences.size(); j++) {
                if (st1.count(vFences[j] - vFences[i])) {
                    t = max(t, vFences[j] - vFences[i]);
                }
            }
        }
        return t == -1 ? -1 : (long long)t * t % 1000000007;
    }
};
using pii = pair<int, int>;
class Solution {
public:
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        int n = original.size();
        vector<vector<int>> vec(26, vector<int>(26, INT_MAX));
        for (int i = 0; i < n; i++) {
            vec[original[i] - 'a'][changed[i] - 'a'] = min(vec[original[i] - 'a'][changed[i] - 'a'], cost[i]);
        }
        vector<vector<int>> dvec(26, vector<int>(26, INT_MAX));
        auto help = [&](int ch) {
            auto cmp = [](auto i, auto j) { return i.second > j.second; };
            priority_queue<pii, vector<pii>, decltype(cmp)> mpq(cmp);
            mpq.emplace(ch, 0);
            vector<int> visit(26, 0);
            while (!mpq.empty()) {
                auto t = mpq.top();
                mpq.pop();
                if (visit[t.first]) {
                    continue;
                }
                dvec[ch][t.first] = t.second;
                visit[t.first] = 1;
                for (int i = 0; i < 26; i++) {
                    if (vec[t.first][i] != INT_MAX && visit[i] == 0) {
                        mpq.emplace(i, t.second + vec[t.first][i]);
                    }
                }
            }
        };
        for (int i = 0; i < 26; i++) {
            help(i);
        }
        long long res = 0;
        for (int i = 0; i < source.size(); i++) {
            if (source[i] != target[i]) {
                if (dvec[source[i] - 'a'][target[i] - 'a'] != INT_MAX) {
                    res += dvec[source[i] - 'a'][target[i] - 'a'];
                } else {
                    return -1;
                }
            }
        }
        return res;
    }
};
