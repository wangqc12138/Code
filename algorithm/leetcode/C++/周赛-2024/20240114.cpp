#include "head.h"
class Solution {
public:
    int maxFrequencyElements(vector<int>& nums) {
        map<int, int> mp;
        for (auto i : nums) {
            mp[i]++;
        }
        int res = 0, maxn = -1;
        for (auto [x, y] : mp) {
            if (y > maxn) {
                res = y;
                maxn = y;
            } else if (y == maxn) {
                res += y;
            }
        }
        return res;
    }
};

class Solution {
public:
    vector<int> beautifulIndices(string s, string a, string b, int k) {
        int n = s.size();
        set<int> s1, s2;
        for (int i = 0; i < n; i++) {
            if (i <= n - a.size() && s.substr(i, a.size()) == a) {
                s1.emplace(i);
            }
            if (i <= n - b.size() && s.substr(i, b.size()) == b) {
                s2.emplace(i);
            }
        }
        vector<int> res;
        for (auto i : s1) {
            if (upper_bound(s2.begin(), s2.end(), i - k) != upper_bound(s2.begin(), s2.end(), i + k)) {
                res.emplace_back(i);
            }
        }
        return res;
    }
};

/*
给你一个整数 k 和一个整数 x 。

令 s 为整数 num 的下标从 1 开始的二进制表示。我们说一个整数 num 的 价值 是满足 i % x == 0 且 s[i] 是 设置位 的 i 的数目。

请你返回 最大 整数 num ，满足从 1 到 num 的所有整数的 价值 和小于等于 k 。
 */
class Solution {
public:
    long long findMaximumNumber(long long k, int x) {
        long long left = 0, right = 3278539330613;
        auto help = [&](long long mid) {
            long long tmp = 0;
            for (int j = x - 1; j <= 31; j += x) {
                if ((mid >> j) & 1) {
                    tmp += (long long)(mid >> j);
                } else {
                    tmp += (long long)(mid >> j) - 1;
                }
            }
            // cout<<tmp<<endl;
            return tmp <= k;
        };
        while (left < right) {
            long long mid = (right - left + 1) / 2 + left;
            // cout<<left<<" "<<mid<<" "<<right<<endl;
            if (!help(mid)) {
                right = mid - 1;
            } else {
                left = mid;
            }
        }
        return left;
    }
};

// 3278539330613 5