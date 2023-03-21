#include "head.h"
// 单调栈主要是为了找离自己最近的大/小值
/*
给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
T42
思路：
从左往右遍历，遇到低的入栈，遇到高的计算栈顶元素的雨水值
 */
class Solution {
public:
    int trap(vector<int>& height) {
        // 单调栈，往下看递增
        stack<int> sk;
        int n = height.size(), res = 0;
        for (int i = 0; i < n; i++) {
            while (!sk.empty() && height[sk.top()] < height[i]) {
                int h = height[sk.top()];
                sk.pop();
                if (!sk.empty()) {
                    int l = height[sk.top()];
                    int r = height[i];
                    res += (min(l, r) - h) * (i - sk.top() - 1);
                }
            }
            sk.emplace(i);
        }
        return res;
    }
};
/*
给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。

求在该柱状图中，能够勾勒出来的矩形的最大面积。
T84
思路：
从左往右遍历，遇到高的就入栈，遇到低的就出栈计算矩形。此时可以看作中间的都是满足条件的，用来计算---------有问题
这么想：高个子找两边离自己最近的矮个子来计算高个子的高度能达到的最大矩形
如果没有左边，则左边都是可以作为高个子的宽度的
右边同理
 */
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        // 从上往下看递减
        stack<int> sk;
        int n = heights.size(), res = 0;
        for (int i = 0; i < n; i++) {
            while (!sk.empty() && heights[sk.top()] > heights[i]) {
                int h = heights[sk.top()];
                int len;
                sk.pop();
                if (!sk.empty()) {
                    len = i - sk.top() - 1;
                } else {
                    len = i;
                }
                res = max(res, len * h);
            }
            sk.emplace(i);
        }
        if (!sk.empty()) {
            int r = sk.top();
            while (!sk.empty()) {
                int h = heights[sk.top()];
                int len;
                sk.pop();
                if (!sk.empty()) {
                    len = r - sk.top();
                } else {
                    len = r + 1;
                }
                res = max(res, len * h);
            }
        }
        return res;
    }
};
/*
给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，其中 answer[i] 是指对于第 i 天，下一个更高温度出现在几天后。
如果气温在这之后都不会升高，请在该位置用 0 来代替。
T739
 */
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
    }
};