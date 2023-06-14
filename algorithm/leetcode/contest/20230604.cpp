#include "head.h"
/*
给你一个下标从 0 开始的字符串 s ，重复执行下述操作 任意 次：

    在字符串中选出一个下标 i ，并使 c 为字符串下标 i 处的字符。并在 i 左侧（如果有）和 右侧（如果有）各 删除 一个距离 i 最近 的字符 c 。

请你通过执行上述操作任意次，使 s 的长度 最小化 。

返回一个表示 最小化 字符串的长度的整数。
 */
class Solution {
public:
    int minimizedStringLength(string s) {
        vector<int> temp(26, 0);
        for (auto c : s) {
            temp[c - 'a']++;
        }
        int res = 0;
        for (int i = 0; i < 26; i++) {
            if (temp[i] % 2) {
                res++;
            }
        }
        return res;
    }
};
/*
给你一个下标从 0 开始、长度为 n 的整数排列 nums 。

如果排列的第一个数字等于 1 且最后一个数字等于 n ，则称其为 半有序排列 。你可以执行多次下述操作，直到将 nums 变成一个 半有序排列 ：

    选择 nums 中相邻的两个元素，然后交换它们。

返回使 nums 变成 半有序排列 所需的最小操作次数。

排列 是一个长度为 n 的整数序列，其中包含从 1 到 n 的每个数字恰好一次。
 */
class Solution {
public:
    int semiOrderedPermutation(vector<int>& nums) {
        int i0 = 0, in = 0, n = nums.size();
        for (int i = 0; i < n; i++) {
            if (nums[i] == 1) {
                i0 = i;
            } else if (nums[i] == n) {
                in = i;
            }
        }
        return i0 < in ? i0 + n - 1 - in : i0 + n - 2 - in;
    }
};