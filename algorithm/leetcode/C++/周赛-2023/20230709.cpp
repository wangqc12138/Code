#include "head.h"
/*
给你两个整数 num 和 t 。

如果整数 x 可以在执行下述操作不超过 t 次的情况下变为与 num 相等，则称其为 可达成数字 ：

    每次操作将 x 的值增加或减少 1 ，同时可以选择将 num 的值增加或减少 1 。

返回所有可达成数字中的最大值。可以证明至少存在一个可达成数字。
 */
class Solution {
public:
    int theMaximumAchievableX(int num, int t) {
        return num + 2 * t;
    }
};
/*
给你一个下标从 0 开始、由 n 个整数组成的数组 nums 和一个整数 target 。

你的初始位置在下标 0 。在一步操作中，你可以从下标 i 跳跃到任意满足下述条件的下标 j ：

    0 <= i < j < n
    -target <= nums[j] - nums[i] <= target

返回到达下标 n - 1 处所需的 最大跳跃次数 。

如果无法到达下标 n - 1 ，返回 -1 。
 */
class Solution {
public:
    int maximumJumps(vector<int>& nums, int target) {
        int n = nums.size(), k = 0, res = 0;
        map<int, vector<int>> mp;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (abs(nums[i] - nums[j]) <= target) {
                    mp[i].emplace_back(j);
                    mp[j].emplace_back(i);
                }
            }
        }
        queue<int> mq;
        mq.emplace(0);
        vector<int> visit(n, 0);
        while (!mq.empty()) {
            int len = mq.size();
            for (int i = 0; i < len; i++) {
                auto t = mq.front();
                mq.pop();
                if (t == n - 1) {
                    res = max(k, res);
                }
                if (visit[t]) {
                    continue;
                }
                visit[t] = 1;
                for (auto nx : mp[t]) {
                    if (!visit[nx]) {
                        mq.emplace(nx);
                    }
                }
            }
            k++;
        }
        return -1;
    }
};