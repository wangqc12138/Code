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
遇到下一个比我大的就弹出
 */
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> sk;
        int n = temperatures.size();
        vector<int> res(n, 0);
        for (int i = 0; i < n; i++) {
            while (!sk.empty() && temperatures[i] > temperatures[sk.top()]) {
                res[sk.top()] = i - sk.top();
                sk.pop();
            }
            sk.emplace(i);
        }
        return res;
    }
};
/*
给定一个长度为 n 的整数数组 arr ，它表示在 [0, n - 1] 范围内的整数的排列。

我们将 arr 分割成若干 块 (即分区)，并对每个块单独排序。将它们连接起来后，使得连接的结果和按升序排序后的原数组相同。

返回数组能分成的最多块数量。
T769
意思就是如果一个数后面都是比他小的，就必须分到一个组
 */
// 非单调栈做法1
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int n = arr.size(), next = 0, res = 0;
        for (int i = 0; i < n; i++) {
            next = max(next, arr[i]);
            if (i == next) {
                res++;
                next++;
            }
        }
        return res;
    }
};
// 非单调栈做法2
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int n = arr.size(), res = 0, sum = 0;
        for (int i = 0; i < n; i++) {
            sum += i;
            sum -= arr[i];
            if (sum == 0) {
                res++;
            }
        }
        return res;
    }
};
// 单调栈做法
// 把栈看作每个子数组的最大值的集合，从小到大排序
// 如果遇到比当前最大值小的，则弹出顶，这个顶还是当前最后一个子数组的最大值，前面的如果有大于该值的，就需要弹出，因为这些子数组需要和当前最后一个子数组合并
// 没有0-n-1的限制 如T768
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        stack<int> sk;
        for (auto i : arr) {
            if (sk.empty() || sk.top() <= i) {
                sk.emplace(i);
            } else {
                int mx = sk.top();
                sk.pop();
                while (!sk.empty() && sk.top() > i) {
                    sk.pop();
                }
                sk.emplace(mx);
            }
        }
        return sk.size();
    }
};
/*
设计一个算法收集某些股票的每日报价，并返回该股票当日价格的 跨度 。

当日股票价格的 跨度 被定义为股票价格小于或等于今天价格的最大连续日数（从今天开始往回数，包括今天）。

    例如，如果未来 7 天股票的价格是 [100,80,60,70,60,75,85]，那么股票跨度将是 [1,1,1,2,1,4,6] 。

实现 StockSpanner 类：

    StockSpanner() 初始化类对象。
    int next(int price) 给出今天的股价 price ，返回该股票当日价格的 跨度 。
T901

 */
class StockSpanner {
public:
    StockSpanner() {
    }

    int next(int price) {
        arr.emplace_back(price);
        while (!sk.empty() && arr[sk.top()] <= price) {
            sk.pop();
        }
        int res;
        if (!sk.empty()) {
            res = arr.size() - sk.top() - 1;
        } else {
            res = arr.size();
        }
        sk.emplace(arr.size() - 1);
        return res;
    }

private:
    stack<int> sk;
    vector<int> arr;
};

/*
给你一个以字符串表示的非负整数 num 和一个整数 k ，移除这个数中的 k 位数字，使得剩下的数字最小。请你以字符串形式返回这个最小的数字。
T402
排在前面的数字只要比后面的大就是需要弹出的，直到不能弹出
 */
class Solution {
public:
    string removeKdigits(string num, int k) {
        stack<char> sk;
        for (auto c : num) {
            while (!sk.empty() && sk.top() > c && k) {
                sk.pop();
                k--;
            }
            sk.emplace(c);
        }
        string res = "";
        while (!sk.empty()) {
            if (k == 0) {
                res += sk.top();
            } else {
                k--;
            }
            sk.pop();
        }
        while (res.back() == '0') {
            res.pop_back();
        }
        if (res == "") {
            return "0";
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
/*
给你一个字符串 s ，请你去除字符串中重复的字母，使得每个字母只出现一次。需保证 返回结果的字典序最小（要求不能打乱其他字符的相对位置）。
T316
排在前面的字母如果比后面的大并且是重复的就弹出。如果栈里已经有了就跳过
20230329
 */
// 丑
class Solution {
public:
    string removeDuplicateLetters(string s) {
        stack<char> sk;
        map<char, int> mp;
        set<char> now;
        for (auto c : s) {
            mp[c]++;
        }
        for (auto c : s) {
            while (!sk.empty() && !now.count(c) && sk.top() >= c) {
                if (mp[sk.top()] == 1) {
                    break;
                }
                mp[sk.top()]--;
                now.erase(sk.top());
                sk.pop();
            }
            if (!now.count(c)) {
                sk.emplace(c);
                now.emplace(c);
            } else {
                mp[c]--;
            }
        }
        string res = "";
        while (!sk.empty()) {
            res += sk.top();
            sk.pop();
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
// 修
class Solution {
public:
    string removeDuplicateLetters(string s) {
        string res;
        vector<int> all(26, 0), visit(26, 0);
        for (auto c : s) {
            all[c - 'a']++;
        }
        for (auto c : s) {
            if (visit[c - 'a'] == 0) {
                while (!res.empty() && res.back() > c && all[res.back() - 'a']) {
                    visit[res.back() - 'a'] = 0;
                    res.pop_back();
                }
                res += c;
                visit[c - 'a'] = 1;
            }
            all[c - 'a']--;
        }
        return res;
    }
};
/*
给定长度分别为 m 和 n 的两个数组，其元素由 0-9 构成，表示两个自然数各位上的数字。现在从这两个数组中选出 k (k <= m + n) 个数字拼接成一个新的数，
要求从同一个数组中取出的数字保持其在原数组中的相对顺序。

求满足该条件的最大数。结果返回一个表示该最大数的长度为 k 的数组。
T321
 */
class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        int m = nums1.size(), n = nums2.size();
        vector<int> res(k, 0);
        for (int i = 0; i <= min(m, k); i++) {
            if (i > m || k - i > n) {
                continue;
            }
            // auto v1 = help(nums1, i);
            // auto v2 = help(nums2, k - i);
            // for (auto i : v1) {
            //     cout << i << " ";
            // }
            // cout << "\n";
            // for (auto i : v2) {
            //     cout << i << " ";
            // }
            // cout << "\n";
            auto temp = merge(help(nums1, i), help(nums2, k - i));
            // for (auto i : temp) {
            //     cout << i << " ";
            // }
            // cout << "\n";
            for (int j = 0; j < k; j++) {
                if (temp[j] > res[j]) {
                    res = temp;
                    break;
                } else if (temp[j] < res[j]) {
                    break;
                }
            }
        }
        return res;
    }
    vector<int> help(const vector<int>& A, int k) {
        vector<int> res;
        int t = A.size() - k;
        for (auto i : A) {
            while (!res.empty() && res.back() < i && t) {
                res.pop_back();
                t--;
            }
            res.emplace_back(i);
        }
        res.resize(min((int)A.size(), k));
        return res;
    }
    vector<int> merge(const vector<int>& A, const vector<int>& B) {
        int i = 0, j = 0, k = 0, m = A.size(), n = B.size();
        vector<int> res(m + n);
        while (i < m && j < n) {
            res[k++] = A[i] > B[j] ? A[i++] : B[j++];
        }
        while (i < m) {
            res[k++] = A[i++];
        }
        while (j < n) {
            res[k++] = B[j++];
        }
        return res;
    }
};