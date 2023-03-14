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