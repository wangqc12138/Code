#include "head.h"
class Solution {
public:
    int res = -1;
    int visit[1001];
    int beautifulSubsets(vector<int>& nums, int k) {
        memset(visit, 0, sizeof(visit));
        sort(nums.begin(), nums.end());
        dfs(nums, 0, k);
        return res;
    }
    void dfs(vector<int>& nums, int index, int k) {
        res++;
        for (int i = index; i < nums.size(); i++) {
            if (nums[i] > k && visit[nums[i] - k]) {
                continue;
            }
            bool flag = visit[nums[i]];
            if (!flag) {
                visit[nums[i]] = 1;
            }
            dfs(nums, i + 1, k);
            if (!flag) {
                visit[nums[i]] = 0;
            }
        }
    }
};
using pii = pair<int, int>;
class Solution {
public:
    bool checkValidGrid(vector<vector<int>>& grid) {
        vector<pii> dir = {{-1, -2}, {-2, -1}, {-1, 2}, {-2, 1}, {1, -2}, {2, -1}, {1, 2}, {2, 1}};
        queue<pii> mq;
        mq.emplace(0, 0);
        int now = 0, n = grid.size();
        while (!mq.empty()) {
            auto [x, y] = mq.front();
            mq.pop();
            for (auto [a, b] : dir) {
                int xx = a + x, yy = b + y;
                if (xx < 0 || xx >= n || yy < 0 || yy >= n) {
                    continue;
                }
                if (grid[xx][yy] == now + 1) {
                    now++;
                    mq.emplace(xx, yy);
                    break;
                }
            }
        }
        return now == n * n - 1;
    }
};
class Solution {
public:
    vector<int> evenOddBit(int n) {
        int even = 0, odd = 0, index = 0;
        while (n) {
            if (index % 2) {
                odd += n % 2;
            } else {
                even += n % 2;
            }
            index++;
            n /= 2;
        }
        return {even, odd};
    }
};
class Solution {
public:
    int findSmallestInteger(vector<int>& nums, int value) {
        map<int, int> mp;
        for (auto i : nums) {
            while (i < 0 || i >= value) {
                i %= value;
            }
            mp[i]++;
        }
        for (int i = 1; i <= nums.size(); i++) {
            i %= value;
            if (mp[i] > 0) {
                mp[i]--;
            } else {
                return i;
            }
        }
        return nums.size() + 1;
    }
};