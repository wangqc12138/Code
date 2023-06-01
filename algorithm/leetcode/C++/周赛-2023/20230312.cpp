#include "head.h"
/*
给你一个下标从 0 开始的字符串数组 words 和两个整数：left 和 right 。

如果字符串以元音字母开头并以元音字母结尾，那么该字符串就是一个 元音字符串 ，其中元音字母是 'a'、'e'、'i'、'o'、'u' 。

返回 words[i] 是元音字符串的数目，其中 i 在闭区间 [left, right] 内。
 */
class Solution {
public:
    int vowelStrings(vector<string>& words, int left, int right) {
        set<int> st = {'a', 'e', 'i', 'o', 'u'};
        int res = 0;
        for (int i = left; i <= right; i++) {
            if (st.count(words[i][0]) && st.count(words[i].back())) {
                res++;
            }
        }
        return res;
    }
};
/*
给你一个下标从 0 开始的整数数组 nums 。你可以将 nums 中的元素按 任意顺序 重排（包括给定顺序）。

令 prefix 为一个数组，它包含了 nums 重新排列后的前缀和。换句话说，prefix[i] 是 nums 重新排列后下标从 0 到 i 的元素之和。
nums 的 分数 是 prefix 数组中正整数的个数。

返回可以得到的最大分数。

 */
class Solution {
public:
    int maxScore(vector<int>& nums) {
        sort(nums.begin(), nums.end(), greater<int>());
        int k = 0, res = 0;
        ;
        for (auto i : nums) {
            k += i;
            if (k > 0) {
                res++;
            }
        }
        return res;
    }
};
/*
给你一个下标从 0 开始的整数数组nums 。每次操作中，你可以：

    选择两个满足 0 <= i, j < nums.length 的不同下标 i 和 j 。
    选择一个非负整数 k ，满足 nums[i] 和 nums[j] 在二进制下的第 k 位（下标编号从 0 开始）是 1 。
    将 nums[i] 和 nums[j] 都减去 2k 。

如果一个子数组内执行上述操作若干次后，该子数组可以变成一个全为 0 的数组，那么我们称它是一个 美丽 的子数组。

请你返回数组 nums 中 美丽子数组 的数目。

子数组是一个数组中一段连续 非空 的元素序列。
 */
class Solution {
public:
    long long beautifulSubarrays(vector<int>& nums) {
        map<int, long long> mp;
        long long res = 0;
        int n = nums.size(), sum = 0;
        mp[0] = 1;
        for (int i = 0; i < n; i++) {
            sum ^= nums[i];
            if (mp.count(sum)) {
                res += mp[sum];
            }
            mp[sum]++;
        }
        return res;
    }
};
/*
你有一台电脑，它可以 同时 运行无数个任务。给你一个二维整数数组 tasks ，
其中 tasks[i] = [starti, endi, durationi] 表示第 i 个任务需要在 闭区间 时间段 [starti, endi] 内运行 durationi 个整数时间点（但不需要连续）。

当电脑需要运行任务时，你可以打开电脑，如果空闲时，你可以将电脑关闭。

请你返回完成所有任务的情况下，电脑最少需要运行多少秒。

 */
class Solution {
public:
    int findMinimumTime(vector<vector<int>>& tasks) {
        sort(tasks.begin(), tasks.end(), [](vector<int>& a, vector<int>& b) { return a[1] < b[1]; });
        int used[2001], res = 0;
        fill(used, used + 2001, 0);
        for (auto vec : tasks) {
            int st = vec[0], ed = vec[1], du = vec[2];
            for (int i = st; i <= ed && du; i++) {
                if (used[i]) {
                    du--;
                }
            }
            for (int i = ed; i >= st && du; i--) {
                if (used[i] == 0) {
                    res++;
                    du--;
                    used[i] = 1;
                }
            }
        }
        return res;
    }
};