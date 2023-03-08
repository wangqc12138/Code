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
/*
给定一个非负整数数组 nums ，你最初位于数组的 第一个下标 。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

判断你是否能够到达最后一个下标。
55
 */
// BFS
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        queue<int> mq;
        vector<int> visit(n, 0);
        mq.emplace(0);
        visit[0] = 1;
        while (!mq.empty()) {
            int k = mq.front();
            if (k + nums[k] >= n - 1) {
                return true;
            }
            mq.pop();
            for (int i = k; i <= k + nums[k]; i++) {
                if (visit[i] == 0) {
                    visit[i] = 1;
                    mq.emplace(i);
                }
            }
        }
        return false;
    }
};
// 贪心-每次到最大
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size(), maxn = 0;
        for (int i = 0; i <= maxn; i++) {
            maxn = max(maxn, i + nums[i]);
            if (maxn >= n - 1) {
                return true;
            }
        }
        return false;
    }
};
/*
在 x 轴上有一个一维的花园。花园长度为 n，从点 0 开始，到点 n 结束。

花园里总共有 n + 1 个水龙头，分别位于 [0, 1, ..., n] 。

给你一个整数 n 和一个长度为 n + 1 的整数数组 ranges ，其中 ranges[i] （下标从 0 开始）表示：如果打开点 i 处的水龙头，可以灌溉的区域为 [i -  ranges[i], i + ranges[i]] 。

请你返回可以灌溉整个花园的 最少水龙头数目 。如果花园始终存在无法灌溉到的地方，请你返回 -1 。
1326
 */
using pii = pair<int, int>;
class Solution {
public:
    int minTaps(int n, vector<int>& ranges) {
        int res = 0;
        vector<pii> temp;
        for (int i = 0; i < ranges.size(); i++) {
            temp.emplace_back(i - ranges[i], i + ranges[i]);
        }
        auto cmp = [&](pii i, pii j) {
            return i.first < j.first || i.first == j.first && i.second < j.second;
        };
        sort(temp.begin(), temp.end(), cmp);
        int last = -101, right = 0;
        for (auto [x, y] : temp) {
            if (right >= n) {
                break;
            }
            if (x > right) {
                return -1;
            }
            if (y <= right) {
                continue;
            }
            if (x > last) {
                res++;
                last = right;
            }
            right = y;
            // cout<<x<<" "<<y<<endl;
            // cout<<last<<" "<<right<<endl;
        }
        return right < n ? -1 : res;
    }
};
/*
以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。
请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。
56
 */
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        auto cmp = [&](const auto& v1, const auto& v2) {
            return v1[0] < v2[0] || v1[0] == v2[0] && v1[1] > v2[1];
        };
        sort(intervals.begin(), intervals.end(), cmp);
        vector<vector<int>> res;
        for (auto vec : intervals) {
            if (res.empty() || res.back()[1] < vec[0]) {
                res.emplace_back(vec);
            } else if (res.back()[1] >= vec[0]) {
                res.back()[1] = max(res.back()[1], vec[1]);
            }
        }
        return res;
    }
};
/*
给你一个 无重叠的 ，按照区间起始端点排序的区间列表。

在列表中插入一个新的区间，你需要确保列表中的区间仍然有序且不重叠（如果有必要的话，可以合并区间）。
57
 */
// 偷懒做法
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        intervals.emplace_back(newInterval);
        return merge(intervals);
    }
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        auto cmp = [&](const auto& v1, const auto& v2) {
            return v1[0] < v2[0] || v1[0] == v2[0] && v1[1] > v2[1];
        };
        sort(intervals.begin(), intervals.end(), cmp);
        vector<vector<int>> res;
        for (auto vec : intervals) {
            if (res.empty() || res.back()[1] < vec[0]) {
                res.emplace_back(vec);
            } else if (res.back()[1] >= vec[0]) {
                res.back()[1] = max(res.back()[1], vec[1]);
            }
        }
        return res;
    }
};
// 老实做法
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> res;
        bool flag = false;
        for (auto vec : intervals) {
            if (res.empty() || res.back()[1] < vec[0]) {
                res.emplace_back(vec);
            } else if (res.back()[1] >= vec[0]) {
                res.back()[1] = max(res.back()[1], vec[1]);
            }
            if (!flag && res.back()[1] >= newInterval[0]) {
                flag = true;
                if (res.back()[0] > newInterval[1]) {
                    auto temp = res.back();
                    res.pop_back();
                    res.emplace_back(newInterval);
                    res.emplace_back(temp);
                } else {
                    res.back()[0] = min(res.back()[0], newInterval[0]);
                    res.back()[1] = max(res.back()[1], newInterval[1]);
                }
            }
        }
        if (!flag) {
            res.emplace_back(newInterval);
        }
        return res;
    }
};