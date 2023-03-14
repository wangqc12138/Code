#include "head.h"
/*
给你两个整数数组 nums1 和 nums2 ，它们已经按非降序排序，请你返回两个数组的 最小公共整数 。如果两个数组 nums1 和 nums2 没有公共整数，请你返回 -1 。

如果一个整数在两个数组中都 至少出现一次 ，那么这个整数是数组 nums1 和 nums2 公共 的。
 */
class Solution {
public:
    int getCommon(vector<int>& nums1, vector<int>& nums2) {
        set<int> st(nums1.begin(), nums1.end());
        for (auto i : nums2) {
            if (st.count(i)) {
                return i;
            }
        }
        return -1;
    }
};
/*
给你两个整数数组 nums1 和 nums2 ，两个数组长度都是 n ，再给你一个整数 k 。你可以对数组 nums1 进行以下操作：

    选择两个下标 i 和 j ，将 nums1[i] 增加 k ，将 nums1[j] 减少 k 。换言之，nums1[i] = nums1[i] + k 且 nums1[j] = nums1[j] - k 。

如果对于所有满足 0 <= i < n 都有 num1[i] == nums2[i] ，那么我们称 nums1 等于 nums2 。

请你返回使 nums1 等于 nums2 的 最少 操作数。如果没办法让它们相等，请你返回 -1 。

 */
class Solution {
public:
    long long minOperations(vector<int>& nums1, vector<int>& nums2, int k) {
        int sum1 = accumulate(nums1.begin(), nums1.end(), 0);
        int sum2 = accumulate(nums2.begin(), nums2.end(), 0);
        if (sum1 != sum2) {
            return -1;
        }
        long long res = 0;
        for (int i = 0; i < nums1.size(); i++) {
            if (nums1[i] != nums2[i]) {
                if (abs(nums1[i] - nums2[i]) % k) {
                    return -1;
                }
                res += (long long)abs(nums1[i] - nums2[i]) / k;
            }
        }
        return res;
    }
};
/*
你两个下标从 0 开始的整数数组 nums1 和 nums2 ，两者长度都是 n ，再给你一个正整数 k 。你必须从 nums1 中选一个长度为 k 的 子序列 对应的下标。

对于选择的下标 i0 ，i1 ，...， ik - 1 ，你的 分数 定义如下：

    nums1 中下标对应元素求和，乘以 nums2 中下标对应元素的 最小值 。
    用公示表示： (nums1[i0] + nums1[i1] +...+ nums1[ik - 1]) * min(nums2[i0] , nums2[i1], ... ,nums2[ik - 1]) 。

请你返回 最大 可能的分数。

一个数组的 子序列 下标是集合 {0, 1, ..., n-1} 中删除若干元素得到的剩余集合，也可以不删除任何元素。

 */
class Solution {
public:
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size();
        vector<int> index(n);
        for (int i = 0; i < n; i++) {
            index[i] = i;
        }
        sort(index.begin(), index.end(), [&](int a, int b) { return nums2[a] > nums2[b]; });
        priority_queue<int, vector<int>, greater<int>> mpq;
        int sum = 0, res = 0;
        for (auto i : index) {
            mpq.emplace(nums1[i]);
            if (mpq.size() > k) {
                sum -= mpq.top();
                mpq.pop();
            }
            if (mpq.size() == k) {
                res = max(res, sum * nums2[i]);
            }
        }
        return res;
    }
};