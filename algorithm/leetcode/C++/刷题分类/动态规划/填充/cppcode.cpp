#include "head.h"
/*
给你一个整数数组 nums 和一个整数 k 。

将数组拆分成一些非空子数组。拆分的 代价 是每个子数组中的 重要性 之和。

令 trimmed(subarray) 作为子数组的一个特征，其中所有仅出现一次的数字将会被移除。

    例如，trimmed([3,1,2,4,3,4]) = [3,4,3,4] 。

子数组的 重要性 定义为 k + trimmed(subarray).length 。

    例如，如果一个子数组是 [1,2,3,3,3,4,4] ，trimmed([1,2,3,3,3,4,4]) = [3,3,3,4,4] 。这个子数组的重要性就是 k + 5 。

找出并返回拆分 nums 的所有可行方案中的最小代价。

子数组 是数组的一个连续 非空 元素序列。
 */
class Solution {
public:
    int minCost(vector<int>& nums, int k) {
        map<int, int> mp;
        for (auto i : nums) {
            mp[i]++;
        }
        vector<int> vec;
        for (auto i : nums) {
            if (mp[i] > 1) {
                vec.emplace_back(i);
            }
        }
        int n = vec.size();
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        int temp[nums.size()];
        for (int i = 1; i <= n; i++) {
            int len = 0;
            memset(temp, 0, sizeof(temp));
            for (int j = i - 1; j >= 0; j--) {
                temp[vec[j]]++;
                if (temp[vec[j]] == 2) {
                    len += 2;
                } else if (temp[vec[j]] > 2) {
                    len++;
                }
                dp[i] = min(dp[i], dp[j] + len + k);
            }
        }
        return dp[n];
    }
};
/*
给定一个数组 books ，其中 books[i] = [thicknessi, heighti] 表示第 i 本书的厚度和高度。你也会得到一个整数 shelfWidth 。

按顺序 将这些书摆放到总宽度为 shelfWidth 的书架上。

先选几本书放在书架上（它们的厚度之和小于等于书架的宽度 shelfWidth ），然后再建一层书架。重复这个过程，直到把所有的书都放在书架上。

需要注意的是，在上述过程的每个步骤中，摆放书的顺序与你整理好的顺序相同。

    例如，如果这里有 5 本书，那么可能的一种摆放情况是：第一和第二本书放在第一层书架上，第三本书放在第二层书架上，第四和第五本书放在最后一层书架上。

每一层所摆放的书的最大高度就是这一层书架的层高，书架整体的高度为各层高之和。

以这种方式布置书架，返回书架整体可能的最小高度。
1105
 */
class Solution {
public:
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        int n = books.size();
        // 以第i本书为当前层数的最后一本的最小高度
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            int high = 0, wigth = 0;
            for (int j = i - 1; j >= 0; j--) {
                high = max(high, books[j][1]);
                wigth += books[j][0];
                if (wigth > shelfWidth) {
                    break;
                }
                dp[i] = min(dp[i], dp[j] + high);
            }
        }
        return dp[n];
    }
};
/*
给你一个整数数组 arr，请你将该数组分隔为长度 最多 为 k 的一些（连续）子数组。分隔完成后，每个子数组的中的所有值都会变为该子数组中的最大值。

返回将数组分隔变换后能够得到的元素最大和。本题所用到的测试用例会确保答案是一个 32 位整数。
T1043
 */
using pii = pair<int, int>;
class Solution {
public:
    int maxSumAfterPartitioning(vector<int>& arr, int K) {
        int n = arr.size();
        int dp[n + 1];
        memset(dp, 0, sizeof(dp));
        // auto cmp = [&](int a, int b) { return arr[a] < arr[b] || arr[a] == arr[b] && a > b; };
        // priority_queue<int, vector<int>, decltype(cmp)> mpq(cmp);
        for (int i = 1; i <= n; i++) {
            // while (!mpq.empty() && i - mpq.top() > K) {
            //     mpq.pop();
            // }
            // mpq.emplace(i - 1);
            int maxn = arr[i - 1];
            for (int j = i - 1; j >= i - K && j >= 0; j--) {
                dp[i] = max(dp[i], dp[j] + maxn * (i - j));
                if (j > 0) {
                    maxn = max(maxn, arr[j - 1]);
                }
            }
        }
        return dp[n];
    }
};
/*
给你一个下标从 0 开始的整数数组 nums ，你必须将数组划分为一个或多个 连续 子数组。

如果获得的这些子数组中每个都能满足下述条件 之一 ，则可以称其为数组的一种 有效 划分：

    子数组 恰 由 2 个相等元素组成，例如，子数组 [2,2] 。
    子数组 恰 由 3 个相等元素组成，例如，子数组 [4,4,4] 。
    子数组 恰 由 3 个连续递增元素组成，并且相邻元素之间的差值为 1 。例如，子数组 [3,4,5] ，但是子数组 [1,3,5] 不符合要求。

如果数组 至少 存在一种有效划分，返回 true ，否则，返回 false 。
T2369
 */
class Solution {
public:
    bool validPartition(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 0);
        if (nums[0] == nums[1]) {
            dp[1] = 1;
        }
        if (n == 2) {
            return dp[1];
        }
        if (nums[0] == nums[1] && nums[0] == nums[2] || nums[0] == nums[1] - 1 && nums[0] == nums[2] - 2) {
            dp[2] = 1;
        }
        for (int i = 3; i < n; i++) {
            if (nums[i] == nums[i - 1]) {
                dp[i] |= dp[i - 2];
            }
            if (nums[i] == nums[i - 1] && nums[i] == nums[i - 2] || nums[i] == nums[i - 1] + 1 && nums[i] == nums[i - 2] + 2) {
                dp[i] |= dp[i - 3];
            }
        }
        return dp[n - 1];
    }
};