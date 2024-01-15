#include "head.h"
class Solution {
public:
    int areaOfMaxDiagonal(vector<vector<int>>& dimensions) {
        int a = 0, b = 0, index = 0, res = 0;
        for (auto vec : dimensions) {
            if (a < pow(vec[0], 2) + pow(vec[1], 2) || a == pow(vec[0], 2) + pow(vec[1], 2) && b < vec[0] * vec[1]) {
                a = pow(vec[0], 2) + pow(vec[1], 2);
                b = vec[0] * vec[1];
                res = index;
            }
            index++;
        }
        return b;
    }
};

class Solution {
public:
    int minMovesToCaptureTheQueen(int a, int b, int c, int d, int e, int f) {
        if (a == e || b == f || abs(c - e) == abs(d - f)) {
            // 中间有棋子
            if (a == e && c == e && d > min(b, f) && d < max(b, f)) {
                return 2;
            }
            if (b == f && d == f && c > min(a, e) && c < max(a, e)) {
                return 2;
            }
            if (abs(a - e) == abs(b - f) && a > min(c, e) && a < max(c, e) && b < max(d, f) && b > min(d, f)) {
                return 2;
            }
            return 1;
        }
        return 2;
    }
};

class Solution {
public:
    int maximumSetSize(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        set<int> s1(nums1.begin(), nums1.end());
        set<int> s2(nums2.begin(), nums2.end());
        set<int> res;
        if (s1.size() < n / 2 && s2.size() < n / 2) {
            res.insert(s1.begin(), s1.end());
            res.insert(s2.begin(), s2.end());
        } else if (s1.size() < n / 2) {
            res.insert(s1.begin(), s1.end());
            int index = 0;
            for (auto i : s2) {
                if (res.count(i)) {
                    continue;
                }
                res.emplace(i);
                if (++index == n / 2) {
                    break;
                }
            }
        } else if (s2.size() < n / 2) {
            res.insert(s2.begin(), s2.end());
            int index = 0;
            for (auto i : s1) {
                if (res.count(i)) {
                    continue;
                }
                res.emplace(i);
                if (++index == n / 2) {
                    break;
                }
            }
        } else {
            int index = 0;
            for (auto i : s1) {
                if (!s2.count(i)) {
                    res.emplace(i);
                    if (++index == n / 2) {
                        break;
                    }
                }
            }
            int j = 0;
            for (auto i : s2) {
                if (!s1.count(i)) {
                    res.emplace(i);
                    if (++j == n / 2) {
                        break;
                    }
                }
            }
            if (res.size() == n) {
                return n;
            }
            for (auto i : s1) {
                if (!res.count(i) && index < n / 2) {
                    res.emplace(i);
                    if (++index == n / 2) {
                        break;
                    }
                }
            }
            for (auto i : s2) {
                if (!res.count(i) && j < n / 2) {
                    res.emplace(i);
                    if (++j == n / 2) {
                        break;
                    }
                }
            }
        }
        return res.size();
    }
};
4
    [1, 2, 1, 1]
    [1, 2, 3, 4] 3
        [1, 1, 1, 1]
        [12, 23, 41, 9] 4
            [2, 4, 1, 4]
            [10, 2, 4, 10]