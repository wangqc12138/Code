#include "head.h"
/*
给你一个正整数数组 price ，其中 price[i] 表示第 i 类糖果的价格，另给你一个正整数 k 。

商店组合 k 类 不同 糖果打包成礼盒出售。礼盒的 甜蜜度 是礼盒中任意两种糖果 价格 绝对差的最小值。

返回礼盒的 最大 甜蜜度。
T2571
 */
class Solution {
public:
    int maximumTastiness(vector<int>& price, int k) {
        sort(price.begin(), price.end());
        int l = 0, r = price.back() - price[0];
        while (l < r) {
            int mid = (l + r + 1) / 2;
            int t = price[0], x = 1;
            for (auto i : price) {
                if (i - t >= mid) {
                    t = i;
                    x++;
                }
            }
            // 如果选出的糖果数小于k，表示间隔太大了，满足条件的太少了！
            if (x < k) {
                r = mid - 1;
            } else {
                l = mid;
            }
        }
        return l;
    }
};
/*
给你一个下标从 0 开始、大小为 n x n 的整数矩阵 grid ，返回满足 Ri 行和 Cj 列相等的行列对 (Ri, Cj) 的数目。

如果行和列以相同的顺序包含相同的元素（即相等的数组），则认为二者是相等的。
T2352
 */
class Solution {
public:
    int equalPairs(vector<vector<int>>& grid) {
        map<vector<int>, int> mp1, mp2;
        int n = grid.size();
        for (int i = 0; i < n; i++) {
            mp1[grid[i]]++;
            vector<int> temp;
            for (int j = 0; j < n; j++) {
                temp.emplace_back(grid[j][i]);
            }
            mp2[temp]++;
        }
        int res = 0;
        for (auto [x, y] : mp1) {
            if (mp2.count(x)) {
                res += y * mp2[x];
            }
        }
        return res;
    }
};
/*
有两只老鼠和 n 块不同类型的奶酪，每块奶酪都只能被其中一只老鼠吃掉。

下标为 i 处的奶酪被吃掉的得分为：

    如果第一只老鼠吃掉，则得分为 reward1[i] 。
    如果第二只老鼠吃掉，则得分为 reward2[i] 。

给你一个正整数数组 reward1 ，一个正整数数组 reward2 ，和一个非负整数 k 。

请你返回第一只老鼠恰好吃掉 k 块奶酪的情况下，最大 得分为多少。
2611
 */
class Solution {
public:
    int miceAndCheese(vector<int>& reward1, vector<int>& reward2, int k) {
        int n = reward1.size();
        vector<int> index(n);
        iota(index.begin(), index.end(), 0);
        sort(index.begin(), index.end(), [&](int i, int j) { return (reward1[i] - reward2[i]) > (reward1[j] - reward2[j]); });
        int res = 0;
        for (int i = 0; i < n; i++) {
            if (i < k) {
                res += reward1[index[i]];
            } else {
                res += reward2[index[i]];
            }
        }
        return res;
    }
};
/*
给你一个链表的头节点 head，请你编写代码，反复删去链表中由 总和 值为 0 的连续节点组成的序列，直到不存在这样的序列为止。

删除完毕后，请你返回最终结果链表的头节点。

你可以返回任何满足题目要求的答案。

（注意，下面示例中的所有序列，都是对 ListNode 对象序列化的表示。）
T1171
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};
class Solution {
public:
    ListNode* removeZeroSumSublists(ListNode* head) {
        map<int, stack<ListNode*>> mp;
        ListNode* dum = new ListNode(0);
        dum->next = head;
        int k = 0;
        auto p = dum;
        while (p) {
            while (p->next && p->next->val == 0) {
                p->next = p->next->next;
            }
            k += p->val;
            if (mp.count(k)) {
                mp[k].top()->next = p->next;
            }
            mp[k].emplace(p);
            cout << mp[k].top()->val << endl;
            cout << p->val << " " << k << ": ";
            auto t = dum->next;
            while (t) {
                cout << t->val << " ";
                t = t->next;
            }
            cout << endl;
            p = p->next;
        }
        return dum->next;
    }
};
/*
给你一个下标从 0 开始的正整数数组 nums 。请你找出并统计满足下述条件的三元组 (i, j, k) 的数目：

    0 <= i < j < k < nums.length
    nums[i]、nums[j] 和 nums[k] 两两不同 。
        换句话说：nums[i] != nums[j]、nums[i] != nums[k] 且 nums[j] != nums[k] 。

返回满足上述条件三元组的数目。
T2475
 */
class Solution {
public:
    int unequalTriplets(vector<int>& nums) {
        map<int, int> mp;
        for (auto i : nums) {
            mp[i]++;
        }
        int res = 0;
        for (auto [x, y] : mp) {
            for (auto [a, b] : mp) {
                if (a <= x) {
                    continue;
                }
                for (auto [c, d] : mp) {
                    if (c <= a) {
                        continue;
                    }
                    res += y * b * d;
                }
            }
        }
        return res;
    }
};
/*
给你一个长度为 n 、下标从 1 开始的二进制字符串，所有位最开始都是 0 。我们会按步翻转该二进制字符串的所有位（即，将 0 变为 1）。

给你一个下标从 1 开始的整数数组 flips ，其中 flips[i] 表示对应下标 i 的位将会在第 i 步翻转。

二进制字符串 前缀一致 需满足：在第 i 步之后，在 闭 区间 [1, i] 内的所有位都是 1 ，而其他位都是 0 。

返回二进制字符串在翻转过程中 前缀一致 的次数。
T1375
 */
class Solution {
public:
    int numTimesAllBlue(vector<int>& flips) {
        int k = -1, res = 0;
        for (int i = 0; i < flips.size(); i++) {
            k = max(flips[i], k);
            if (k == i + 1) {
                res++;
            }
        }
        return res;
    }
};