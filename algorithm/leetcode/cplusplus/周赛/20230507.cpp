#include "head.h"
class Solution {
public:
    vector<int> distinctDifferenceArray(vector<int>& nums) {
        int n = nums.size();
        set<int> pre;
        vector<int> res;
        for (int i = 0; i < n; i++) {
            pre.emplace(nums[i]);
            set<int> suff;
            for (int j = i + 1; j < n; j++) {
                suff.emplace(nums[j]);
            }
            res.emplace_back(pre.size() - suff.size());
        }
        return res;
    }
};
class FrequencyTracker {
public:
    FrequencyTracker() {
    }

    void add(int number) {
        if (++mp[number] == 1) {
            mp2[1].emplace(number);
        } else {
            mp2[mp[number]].emplace(number);
            mp2[mp[number] - 1].erase(number);
        }
    }

    void deleteOne(int number) {
        if (mp.count(number)) {
            if (--mp[number] == 0) {
                mp2[1].erase(number);
                mp.erase(number);
            } else {
                mp2[mp[number]].emplace(number);
                mp2[mp[number] + 1].erase(number);
            }
        }
    }

    bool hasFrequency(int frequency) {
        return mp2[frequency].size();
    }

private:
    map<int, int> mp;
    map<int, set<int>> mp2;
};

class Solution {
public:
    vector<int> colorTheArray(int n, vector<vector<int>>& queries) {
        map<int, int> mp;
        vector<int> res;
        int sum = 0;
        for (auto vec : queries) {
            int x = vec[0], y = vec[1];
            if (mp[x - 1] == mp[x] && mp[x - 1] != 0) {
                sum--;
            }
            if (mp[x] == mp[x + 1] && mp[x + 1] != 0) {
                sum--;
            }
            if (mp[x - 1] == y) {
                sum++;
            }
            if (mp[x + 1] == y) {
                sum++;
            }
            mp[x] = y;
            res.emplace_back(sum);
        }
        return res;
    }
};
class Solution {
public:
    int minIncrements(int n, vector<int>& cost) {
        int len = (n + 1) / 2, res = 0;
        vector<int> temp(len, 0);
        function<int(int)> dfs = [&](int r) -> int {
            if (r > n) {
                return 0;
            }
            int lv = dfs(r * 2);
            int rv = dfs(r * 2 + 1);
            if (lv != rv) {
                res += abs(lv - rv);
            }
            return max(lv, rv) + cost[r - 1];
        };
        dfs(1);
        return res;
    }
};