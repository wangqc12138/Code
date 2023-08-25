#include "head.h"
/*
给你一个整数数组 nums ，数组由 不同正整数 组成，请你找出并返回数组中 任一 既不是 最小值 也不是 最大值 的数字，如果不存在这样的数字，返回 -1 。

返回所选整数。
 */
class Solution {
public:
    int findNonMinOrMax(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for (auto i : nums) {
            if (i != nums[0] && i != nums.back()) {
                return i;
            }
        }
        return -1;
    }
};
/*
给你一个仅由小写英文字母组成的字符串 s 。在一步操作中，你可以完成以下行为：

    选则 s 的任一非空子字符串，可能是整个字符串，接着将字符串中的每一个字符替换为英文字母表中的前一个字符。例如，'b' 用 'a' 替换，'a' 用 'z' 替换。

返回执行上述操作 恰好一次 后可以获得的 字典序最小 的字符串。

子字符串 是字符串中的一个连续字符序列。
现有长度相同的两个字符串 x 和 字符串 y ，在满足 x[i] != y[i] 的第一个位置 i 上，如果  x[i] 在字母表中先于 y[i] 出现，则认为字符串 x 比字符串 y 字典序更小 。
 */
class Solution {
public:
    string smallestString(string s) {
        bool flag = false;
        for (auto& c : s) {
            if (c != 'a') {
                flag = true;
                c = c - 1;
            } else if (flag) {
                break;
            }
        }
        if (!flag) {
            s.back() = 'z';
        }
        return s;
    }
};
/* 
给你一个长度为 n 、下标从 0 开始的整数数组 nums ，表示收集不同巧克力的成本。每个巧克力都对应一个不同的类型，最初，位于下标 i 的巧克力就对应第 i 个类型。

在一步操作中，你可以用成本 x 执行下述行为：

    同时修改所有巧克力的类型，将巧克力的类型 ith 修改为类型 ((i + 1) mod n)th。

假设你可以执行任意次操作，请返回收集所有类型巧克力所需的最小成本。
 */
class Solution {
public:
    long long minCost(vector<int>& nums, int x) {
        
    }
};