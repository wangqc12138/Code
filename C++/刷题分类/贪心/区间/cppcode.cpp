#include "head.h"
/*
你将会获得一系列视频片段，这些片段来自于一项持续时长为 time 秒的体育赛事。这些片段可能有所重叠，也可能长度不一。

使用数组 clips 描述所有的视频片段，其中 clips[i] = [starti, endi] 表示：某个视频片段开始于 starti 并于 endi 结束。

甚至可以对这些片段自由地再剪辑：

    例如，片段 [0, 7] 可以剪切成 [0, 1] + [1, 3] + [3, 7] 三部分。

我们需要将这些片段进行再剪辑，并将剪辑后的内容拼接成覆盖整个运动过程的片段（[0, time]）。返回所需片段的最小数目，如果无法完成该任务，则返回 -1 。
1024
 */
class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int time) {
        int res = 0, last = -1, right = 0;
        sort(clips.begin(), clips.end(), [&](auto i, auto j) { return i[0] < j[0] || i[0] == j[0] && i[1] > j[1]; });
        for (auto vec : clips) {
            if (vec[0] > right) {
                return -1;
            }
            if (vec[1] <= right) {
                continue;
            }
            if (vec[0] > last) {
                res++;
                last = right;
            }
            right = vec[1];
            if (right >= time) {
                return res;
            }
        }
        return -1;
    }
};
/*
给定一个长度为 n 的 0 索引整数数组 nums。初始位置为 nums[0]。

每个元素 nums[i] 表示从索引 i 向前跳转的最大长度。换句话说，如果你在 nums[i] 处，你可以跳转到任意 nums[i + j] 处:

    0 <= j <= nums[i]
    i + j < n

返回到达 nums[n - 1] 的最小跳跃次数。生成的测试用例可以到达 nums[n - 1]。
45
 */
using pii = pair<int, int>;
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size(), res = 0;
        int last = 0, right = 0;
        for (int i = 0; i < n; i++) {
            if (i > right) {
                return -1;
            }
            if (i + nums[i] <= right) {
                continue;
            }
            if (last == i) {
                last = right;
                res++;
            }
            right = i + nums[i];
        }
        return res;
    }
};