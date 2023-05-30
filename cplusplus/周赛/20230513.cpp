#include "head.h"
class Solution {
public:
    long long maximumOr(vector<int>& nums, int k) {
        auto temp = nums;
        int index = 0;
        for (int i = 31; i >= 0; i--) {
            vector<int> vec;
            for (auto j : temp) {
                if (j >> i & 1) {
                    vec.emplace_back(j);
                }
            }
            if (!vec.empty()) {
                index = i;
                temp = vec;
                break;
            }
        }
        vector<int> v(32, 0);
        for (int i = 31; i >= 0; i--) {
            for (auto j : nums) {
                v[i] += (j >> i & 1);
            }
        }
        long long res = 0;
        if (temp.size() == 1) {
            for (auto i : nums) {
                res |= i;
            }
        } else {
            for (int i = index - k; i > k; i--) {
                vector<int> vec;
                for (auto j : temp) {
                    if ((j >> i & 1) && (v[i + k] == 0 || v[i + k] == 1 && j >> (i + k) == 0)) {
                        vec.emplace_back(j);
                    }
                }
                temp = vec;
                if (vec.size() == 1) {
                    break;
                }
            }
            int n = temp[0];
            set<int> st;
            for (auto i : nums) {
                if (i == n) {
                    if (st.count(i)) {
                        res |= i;
                    }
                }
                st.emplace(i);
            }
            res |= (n << k);
        }
    }
};
class Solution {
public:
    int matrixSum(vector<vector<int>>& nums) {
        vector<priority_queue<int>> temp(nums.size());
        int m = nums.size(), n = nums[0].size();
        for (int i = 0; i < m; i++) {
            for (auto j : nums[i]) {
                temp[i].emplace(j);
            }
        }
        int res = 0;
        for (int j = 0; j < n; j++) {
            int maxn = 0;
            for (auto mpq : temp) {
                if (!mpq.empty()) {
                    maxn = max(mpq.top(), maxn);
                    mpq.pop();
                }
            }
            res += maxn;
        }
        return res;
    }
};
class Solution {
public:
    int countSeniors(vector<string>& details) {
        int res = 0;
        for (auto str : details) {
            if (stoi(str.substr(11, 2)) > 60) {
                res++;
            }
        }
        return res;
    }
};