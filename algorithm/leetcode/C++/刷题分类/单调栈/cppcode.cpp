
#include "head.h"
/*
给你一份工作时间表 hours，上面记录着某一位员工每天的工作小时数。

我们认为当员工一天中的工作小时数大于 8 小时的时候，那么这一天就是「劳累的一天」。

所谓「表现良好的时间段」，意味在这段时间内，「劳累的天数」是严格 大于「不劳累的天数」。

请你返回「表现良好时间段」的最大长度。
1124
 */
class Solution {
public:
    int longestWPI(vector<int>& hours) {
        stack<int> sk;
        sk.emplace(0);
        int n = hours.size(), sum = 0, res = 0;
        vector<int> pre(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            pre[i] = pre[i - 1] + (hours[i] > 8 ? 1 : -1);
            if (pre[sk.top()] > pre[i]) {
                sk.emplace(i);
            }
        }
        for (int i = n; i > 0; i--) {
            while (!sk.empty() && pre[sk.top()] < pre[i]) {
                res = max(res, i - sk.top());
                sk.pop();
            }
        }
    }
};
/*
给定一个整数数组 A，坡是元组 (i, j)，其中  i < j 且 A[i] <= A[j]。这样的坡的宽度为 j - i。

找出 A 中的坡的最大宽度，如果不存在，返回 0 。
962
 */
class Solution {
public:
    int maxWidthRamp(vector<int>& nums) {
        stack<int> sk;
        int res = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (sk.empty() || nums[sk.top()] > nums[i]) {
                sk.emplace(i);
            }
        }
        for (int i = nums.size() - 1; i > 0; i--) {
            while (!sk.empty() && nums[sk.top()] <= nums[i]) {
                res = max(res, i - sk.top());
                sk.pop();
            }
        }
        return res;
    }
};
// 做法2排序
class Solution {
public:
    int maxWidthRamp(vector<int>& nums) {
        int n = nums.size(), minn = INT_MAX, res = 0;
        vector<int> temp(n);
        iota(temp.begin(), temp.end(), 0);
        auto cmp = [&](int i, int j) { return nums[i] < nums[j] || nums[i] == nums[j] && i < j; };
        sort(temp.begin(), temp.end(), cmp);
        for (int i = 0; i < n; i++) {
            minn = min(temp[i], minn);
            res = max(res, i - minn);
        }
        return res;
    }
};
/*
给你一个整数数组 nums 和一个整数 k ，找出 nums 中和至少为 k 的 最短非空子数组 ，并返回该子数组的长度。如果不存在这样的 子数组 ，返回 -1 。

子数组 是数组中 连续 的一部分。
862
 */
class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        int n = nums.size(), res = INT_MAX;
        vector<int> sum(n + 1, 0);
        stack<int> sk;
        sk.emplace(0);
        for (int i = 1; i <= n; i++) {
            sum[i] = sum[i - 1] + nums[i - 1];
            auto temp = sk;
            while (!temp.empty() && sum[i] - sum[temp.top()] < k) {
                temp.pop();
            }
            if (!temp.empty()) {
                res = min(res, i - temp.top());
            }
            while (!sk.empty() && sum[sk.top()] >= sum[i]) {
                sk.pop();
            }
            sk.emplace(i);
        }
        // for(auto i:sum){
        //     cout<<i<<" ";
        // }
        return res == INT_MAX ? -1 : res;
    }
};
/*
nums1 中数字 x 的 下一个更大元素 是指 x 在 nums2 中对应位置 右侧 的 第一个 比 x 大的元素。

给你两个 没有重复元素 的数组 nums1 和 nums2 ，下标从 0 开始计数，其中nums1 是 nums2 的子集。

对于每个 0 <= i < nums1.length ，找出满足 nums1[i] == nums2[j] 的下标 j ，并且在 nums2 确定 nums2[j] 的 下一个更大元素 。
如果不存在下一个更大元素，那么本次查询的答案是 -1 。

返回一个长度为 nums1.length 的数组 ans 作为答案，满足 ans[i] 是如上所述的 下一个更大元素 。
496
 */
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int n = nums2.size();
        map<int, int> mp;
        stack<int> sk;
        for (int i : nums2) {
            while (!sk.empty() && sk.top() < i) {
                mp[sk.top()] = i;
                sk.pop();
            }
            sk.emplace(i);
        }
        for (auto& i : nums1) {
            if (mp.count(i)) {
                i = mp[i];
            } else {
                i = -1;
            }
        }
        return nums1;
    }
};
/*
给定一个循环数组（最后一个元素的下一个元素是数组的第一个元素），输出每个元素的下一个更大元素。
数字 x 的下一个更大的元素是按数组遍历顺序，这个数字之后的第一个比它更大的数，这意味着你应该循环地搜索它的下一个更大的数。如果不存在，则输出 -1。
503
*/
/*
给你一个整数数组 nums ，数组中共有 n 个整数。132 模式的子序列 由三个整数 nums[i]、nums[j] 和 nums[k] 组成，并同时满足：i < j < k 和 nums[i] < nums[k] < nums[j] 。
如果 nums 中存在 132 模式的子序列 ，返回 true ；否则，返回 false 。
进阶：很容易想到时间复杂度为 O(n^2) 的解决方案，你可以设计一个时间复杂度为 O(n logn) 或 O(n) 的解决方案吗？
456
*/
//[3,5,0,3,4]
class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        int n = nums.size(), two = INT_MIN;
        stack<int> ms;
        for (int i = n - 1; i >= 0; i--) {
            if (nums[i] >= two) {
                while (!ms.empty() && nums[i] > nums[ms.top()]) {
                    two = nums[ms.top()];
                    ms.pop();
                }
                ms.push(i);
            } else {
                return true;
            }
        }
        return false;
    }
};
/*
给定一个直方图(也称柱状图)，假设有人从上面源源不断地倒水，最后直方图能存多少水量?直方图的宽度为 1。
面试题 17.21. 直方图的水量
*/
class Solution {
public:
    int trap(vector<int>& height) {
        stack<int> sk;
        int res = 0;
        for (int i = 0; i < height.size(); i++) {
            while (!sk.empty() && height[sk.top()] < height[i]) {
                int j = sk.top();
                sk.pop();
                if (sk.empty()) {
                    break;
                }
                int k = sk.top();
                int h = min(height[i], height[k]) - height[j];
                res += (i - k - 1) * h;
            }
            sk.emplace(i);
        }
        return res;
    }
};
/*
Leetcode 42：接雨水（超详细的解法！！！）

Leetcode 496：下一个更大元素 I（超详细的解法！！！）

Leetcode 503：下一个更大元素 II（超详细的解法！！！）

Leetcode 739：每日温度（超详细的解法！！！）

Leetcode 901：股票价格跨度（超详细的解法！！！）

Leetcode 239：滑动窗口最大值（超详细的解法！！！）

Leetcode 84：柱状图中最大的矩形（超详细的解法！！！）

907 1019 316 402 581 1118
 */