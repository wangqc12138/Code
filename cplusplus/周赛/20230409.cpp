#include "head.h"
class Solution {
public:
    int diagonalPrime(vector<vector<int>>& nums) {
        int n = nums.size();
        set<int> st;
        for (int i = 0; i < n; i++) {
            st.emplace(nums[i][i]);
            st.emplace(nums[i][n - i - 1]);
        }
        vector<int> temp(st.begin(), st.end());

        for (int i = temp.size() - 1; i >= 0; i--) {
            if (isPrime(temp[i])) {
                return temp[i];
            }
        }
        return 0;
    }
    bool isPrime(int n) {
        if (n == 1) {
            return false;
        }
        for (int i = 2; i <= (int)sqrt(n); i++) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }
};
class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        unordered_map<int, vector<int>> pos;
        unordered_map<int, vector<long long>> sum;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (!sum.count(nums[i])) {
                sum[nums[i]].emplace_back(i);
            } else {
                sum[nums[i]].emplace_back(sum[nums[i]].back() + i);
            }
            pos[nums[i]].emplace_back(i);
        }
        if (nums.size() == sum.size()) {
            return vector<long long>(n, 0);
        }
        vector<long long> res(n, 0);
        // for (int i = 0; i < n; i++) {
        //     int x = nums[i];
        //     auto y = sum[x];
        //     if (y.size() == 1) {
        //         res.emplace_back(0);
        //     } else {
        //         int n = y.size();
        //         int j = index[x];
        //         long long t = (y[n - 1] - y[j]) - i * (n - 1 - j) + i * j - (j == 0 ? 0 : y[j - 1]);
        //         res.emplace_back(t);
        //         index[x]++;
        //     }
        // }
        for (auto [x, y] : sum) {
            if (y.size() == 1) {
                continue;
            }
            int m = y.size();
            for (int i = 0; i < pos[x].size(); i++) {
                int k = pos[x][i];
                long long t = (y[m - 1] - y[i]) - k * (m - 1 - i) + k * i - (i == 0 ? 0 : y[i - 1]);
                res[k] = t;
            }
        }
        return res;
    }
};

class Solution {
public:
    int minimizeMax(vector<int>& nums, int p) {
        sort(nums.begin(), nums.end());
        int n = nums.size(), l = 0, r = nums[n - 1] - nums[0];
        while (l < r) {
            int mid = (l + r) / 2;
            int k = 0;
            for (int i = 1; i < n; i++) {
                if (nums[i] - nums[i - 1] <= mid) {
                    i++;
                    if (++k >= p) {
                        break;
                    }
                }
            }
            if (k < p) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        return l;
    }
};