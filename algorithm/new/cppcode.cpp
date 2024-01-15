#include "head.h"
/*
给你一个下标从 0 开始的字符串 s ，这个字符串只包含 0 到 9 的数字字符。

如果一个字符串 t 中至多有一对相邻字符是相等的，那么称这个字符串 t 是 半重复的 。例如，0010 、002020 、0123 、2002 和 54944 是半重复字符串，而 00101022 和 1101234883 不是。

请你返回 s 中最长 半重复 子字符串的长度。

一个 子字符串 是一个字符串中一段连续 非空 的字符。
2730
 */
class Solution {
public:
    int longestSemiRepetitiveSubstring(string s) {
        int n = s.size(), left = 0, right = 0, k = 0, res = 0;
        while (right < n) {
            while (right < n) {
                if (right < n - 1 && s[right] == s[right + 1]) {
                    if (k) {
                        break;
                    } else {
                        k++;
                    }
                }
                right++;
            }
            res = max(res, min(right, n - 1) - left + 1);
            while (left < right && k == 1) {
                if (left < n - 1 && s[left] == s[left + 1]) {
                    k--;
                }
                left++;
            }
        }
        return res;
    }
};
class Solution {
public:
    int longestSemiRepetitiveSubstring(string s) {
        int n = s.size();
        vector<int> vec;
        for (int i = 0; i < n - 1; i++) {
            if (s[i] == s[i + 1]) {
                vec.emplace_back(i);
            }
        }
        if (vec.size() <= 1) {
            return n;
        }
        int res = 0;
        for (int i = 0; i < vec.size(); i++) {
            if (i != vec.size() - 1) {
                if (i == 0) {
                    res = max(res, vec[i + 1] + 1);
                }
                if (vec[i] + 1 != vec[i + 1]) {
                    if (vec[i - 1] == vec[i] - 1) {
                        res = max(res, vec[i + 1] - vec[i] + 1);
                    } else {
                        res = max(res, vec[i + 1] - vec[i - 1]);
                    }
                } else {
                    res = max(res, 2);
                }
            } else {
                res = max(res, n - vec[i - 1] - 1);
            }
        }
        return res;
    }
};
/*
一个公司准备组织一场会议，邀请名单上有 n 位员工。公司准备了一张 圆形 的桌子，可以坐下 任意数目 的员工。

员工编号为 0 到 n - 1 。每位员工都有一位 喜欢 的员工，每位员工 当且仅当 他被安排在喜欢员工的旁边，他才会参加会议。每位员工喜欢的员工 不会 是他自己。

给你一个下标从 0 开始的整数数组 favorite ，其中 favorite[i] 表示第 i 位员工喜欢的员工。请你返回参加会议的 最多员工数目 。
2127
 */

/*
n 对情侣坐在连续排列的 2n 个座位上，想要牵到对方的手。

人和座位由一个整数数组 row 表示，其中 row[i] 是坐在第 i 个座位上的人的 ID。情侣们按顺序编号，第一对是 (0, 1)，第二对是 (2, 3)，以此类推，最后一对是 (2n-2, 2n-1)。

返回 最少交换座位的次数，以便每对情侣可以并肩坐在一起。 每次交换可选择任意两人，让他们站起来交换座位。
T765
 */
class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        int n = row.size(), res = n / 2;
        for (int i = 0; i < n; i += 2) {
            if (abs(row[i] - row[i + 1] == 1) && min(row[i], row[i + 1]) % 2 == 0) {
                res -= 1;
            }
        }
        return res;
    }
};
/*
Range模块是跟踪数字范围的模块。设计一个数据结构来跟踪表示为 半开区间 的范围并查询它们。

半开区间 [left, right) 表示所有 left <= x < right 的实数 x 。

实现 RangeModule 类:

    RangeModule() 初始化数据结构的对象。
    void addRange(int left, int right) 添加 半开区间 [left, right)，跟踪该区间中的每个实数。
    添加与当前跟踪的数字部分重叠的区间时，应当添加在区间 [left, right) 中尚未跟踪的任何数字到该区间中。
    boolean queryRange(int left, int right) 只有在当前正在跟踪区间 [left, right) 中的每一个实数时，才返回 true ，否则返回 false 。
    void removeRange(int left, int right) 停止跟踪 半开区间 [left, right) 中当前正在跟踪的每个实数。
T715
// 线段树
 */
class RangeModule {
public:
    RangeModule() {
    }

    void addRange(int left, int right) {
    }

    bool queryRange(int left, int right) {
    }

    void removeRange(int left, int right) {
    }
};
/*
有 n 个城市，按从 0 到 n-1 编号。给你一个边数组 edges，其中 edges[i] = [fromi, toi, weighti] 代表 fromi 和 toi 两个城市之间的双向加权边，距离阈值是一个整数 distanceThreshold。

返回能通过某些路径到达其他城市数目最少、且路径距离 最大 为 distanceThreshold 的城市。如果有多个这样的城市，则返回编号最大的城市。

注意，连接城市 i 和 j 的路径的距离等于沿该路径的所有边的权重之和。
T1334
 */
class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
    }
};
/*
给你一个下标从 0 开始的数组 nums ，数组中的元素都是 正 整数。请你选出两个下标 i 和 j（i != j），且 nums[i] 的数位和 与  nums[j] 的数位和相等。

请你找出所有满足条件的下标 i 和 j ，找出并返回 nums[i] + nums[j] 可以得到的 最大值 。
T2342
 */
class Solution {
public:
    int maximumSum(vector<int>& nums) {
        map<int, priority_queue<int>> mp;
        int res = -1;
        for (auto i : nums) {
            int t = 0;
            for (auto j : to_string(i)) {
                t += j - '0';
            }
            mp[t].emplace(i);
        }
        for (auto [x, y] : mp) {
            if (y.size() >= 2) {
                int t = y.top();
                y.pop();
                t += y.top();
                res = max(res, t);
            }
        }
        return res;
    }
};
/*
给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

子数组 是数组中的一个连续部分。
T53
 */
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int now = 0, res = INT_MIN;
        for (auto i : nums) {
            if (now <= 0) {
                now = i;
            } else {
                now += i;
            }
            res = max(now, res);
        }
        return res;
    }
};
/*
你正在经营一座摩天轮，该摩天轮共有 4 个座舱 ，每个座舱 最多可以容纳 4 位游客 。你可以 逆时针 轮转座舱，但每次轮转都需要支付一定的运行成本 runningCost 。摩天轮每次轮转都恰好转动 1 / 4 周。

给你一个长度为 n 的数组 customers ， customers[i] 是在第 i 次轮转（下标从 0 开始）之前到达的新游客的数量。这也意味着你必须在新游客到来前轮转 i 次。
每位游客在登上离地面最近的座舱前都会支付登舱成本 boardingCost ，一旦该座舱再次抵达地面，他们就会离开座舱结束游玩。

你可以随时停下摩天轮，即便是 在服务所有游客之前 。如果你决定停止运营摩天轮，为了保证所有游客安全着陆，将免费进行所有后续轮转 。
注意，如果有超过 4 位游客在等摩天轮，那么只有 4 位游客可以登上摩天轮，其余的需要等待 下一次轮转 。

返回最大化利润所需执行的 最小轮转次数 。 如果不存在利润为正的方案，则返回 -1 。

T1599
 */
class Solution {
public:
    int minOperationsMaxProfit(vector<int>& customers, int boardingCost, int runningCost) {
        int now = 0, cost = 0, res = 0, index = 0;

        for (int i = 0; i < customers.size(); i++) {
            now += customers[i];
            int k = min(4, now);
            now -= k;
            cost += k * boardingCost - runningCost;
            if (res < cost) {
                index = i + 1;
            }
            res = max(res, cost);
        }
        return res > 0 ? cost : -1;
    }
};

/*
定义 str = [s, n] 表示 str 由 n 个字符串 s 连接构成。

    例如，str == ["abc", 3] =="abcabcabc" 。

如果可以从 s2 中删除某些字符使其变为 s1，则称字符串 s1 可以从字符串 s2 获得。

    例如，根据定义，s1 = "abc" 可以从 s2 = "abdbec" 获得，仅需要删除加粗且用斜体标识的字符。

现在给你两个字符串 s1 和 s2 和两个整数 n1 和 n2 。由此构造得到两个字符串，其中 str1 = [s1, n1]、str2 = [s2, n2] 。

请你找出一个最大整数 m ，以满足 str = [str2, m] 可以从 str1 获得。
T466
 */
class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
    }
};
/*
给你一个链表的头节点 head 。

移除每个右侧有一个更大数值的节点。

返回修改后链表的头节点 head 。
T2487
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
class Solution {
public:
    ListNode* removeNodes(ListNode* head) {
        vector<int> vec, data;
        int n = 0;
        while (head) {
            vec.emplace_back(head->val);
            head = head->next;
            n++;
        }
        for (int i = n - 1; i >= 0; i--) {
            if (i == n - 1 || vec[i] >= data.back()) {
                data.emplace_back(vec[i]);
            }
        }
        ListNode* res = new ListNode();
        auto ptr = res;
        for (int i = data.size() - 1; i >= 0; i--) {
            ListNode* tmp = new ListNode(data[i]);
            ptr->next = tmp;
            ptr = ptr->next;
        }
        return res->next;
    }
};
// 递归
class Solution {
public:
    ListNode* removeNodes(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }
        head->next = removeNodes(head->next);
        if (head->next && head->val < head->next->val) {
            return head->next;
        } else {
            return head;
        }
    }
};
/*
给你一个二维整数数组 rectangles ，其中 rectangles[i] = [li, hi] 表示第 i 个矩形长为 li 高为 hi 。给你一个二维整数数组 points ，其中 points[j] = [xj, yj] 是坐标为 (xj, yj) 的一个点。

第 i 个矩形的 左下角 在 (0, 0) 处，右上角 在 (li, hi) 。

请你返回一个整数数组 count ，长度为 points.length，其中 count[j]是 包含 第 j 个点的矩形数目。

如果 0 <= xj <= li 且 0 <= yj <= hi ，那么我们说第 i 个矩形包含第 j 个点。如果一个点刚好在矩形的 边上 ，这个点也被视为被矩形包含。
T2250
 */
class Solution {
public:
    vector<int> countRectangles(vector<vector<int>>& rectangles, vector<vector<int>>& points) {
        vector<set<int>> vst(101);
        for (auto vec : rectangles) {
            for (int i = vec[1]; i <= 100; i++) {
                vst[i].emplace(vec[0]);
            }
        }
        vector<vector<int>> vvec(101);
        for (int i = 0; i <= 100; i++) {
            vvec[i] = vector(vst[i].begin(), vst[i].end());
        }
        int n = points.size();
        vector<int> res;
        for (int i = 0; i < n; i++) {
            int x = points[i][0], y = points[i][1];
            res.emplace_back(vvec[y].size() - (lower_bound(vvec[y].begin(), vvec[y].begin(), x) - vvec[y].begin()));
        }
        return res;
    }
};
/*
给你一个下标从 0 开始、大小为 m x n 的二进制矩阵 matrix ；另给你一个整数 numSelect，表示你必须从 matrix 中选择的 不同 列的数量。

如果一行中所有的 1 都被你选中的列所覆盖，则认为这一行被 覆盖 了。

形式上，假设 s = {c1, c2, ...., cnumSelect} 是你选择的列的集合。对于矩阵中的某一行 row ，如果满足下述条件，则认为这一行被集合 s 覆盖：

    对于满足 matrix[row][col] == 1 的每个单元格 matrix[row][col]（0 <= col <= n - 1），col 均存在于 s 中，或者
    row 中 不存在 值为 1 的单元格。

你需要从矩阵中选出 numSelect 个列，使集合覆盖的行数最大化。

返回一个整数，表示可以由 numSelect 列构成的集合 覆盖 的 最大行数 。
T2397
 */
class Solution {
public:
    int maximumRows(vector<vector<int>>& matrix, int numSelect) {
        int res = 0, m = matrix.size(), n = matrix[0].size();
        vector<int> vec;
        for (int i = 0; i < m; i++) {
            int t = 0, index = 0;
            for (int j = 0; j < n; j++) {
                if (matrix[i][j]) {
                    t |= (1 << j);
                    index++;
                }
            }
            if (index <= numSelect) {
                vec.emplace_back(t);
            }
        }
        function<void(int, int, int)> dfs = [&](int x, int t, int d) -> void {
            if (d == numSelect) {
                int tmp = 0;
                for (auto i : vec) {
                    if ((i & t) == t) {
                        tmp++;
                    }
                }
                res = max(res, tmp);
                return;
            }
            for (int i = x; i < n; i++) {
                dfs(i + 1, t | (1 << i), d + 1);
            }
        };
        dfs(0, 0, 0);
        return res;
    }
};

/*
有 n 个人排成一个队列，从左到右 编号为 0 到 n - 1 。给你以一个整数数组 heights ，每个整数 互不相同，heights[i] 表示第 i 个人的高度。

一个人能 看到 他右边另一个人的条件是这两人之间的所有人都比他们两人 矮 。更正式的，第 i 个人能看到第 j 个人的条件是 i < j 且 min(heights[i], heights[j]) > max(heights[i+1], heights[i+2], ..., heights[j-1]) 。

请你返回一个长度为 n 的数组 answer ，其中 answer[i] 是第 i 个人在他右侧队列中能 看到 的 人数 。
T1944
单调栈
 */
class Solution {
public:
    vector<int> canSeePersonsCount(vector<int>& heights) {
        stack<int> sk;
        int n = heights.size();
        vector<int> res(n, 0);
        for (int i = 0; i < n; i++) {
            while (!sk.empty() && heights[sk.top()] < heights[i]) {
                res[sk.top()]++;
                sk.pop();
                if (!sk.empty()) {
                    res[sk.top()]++;
                }
            }
            sk.emplace(i);
        }
        if (!sk.empty()) {
            sk.pop();
        }
        while (!sk.empty()) {
            res[sk.top()]++;
            sk.pop();
        }
        return res;
    }
};

/*
给你一个链表的头 head ，每个结点包含一个整数值。

在相邻结点之间，请你插入一个新的结点，结点值为这两个相邻结点值的 最大公约数 。

请你返回插入之后的链表。

两个数的 最大公约数 是可以被两个数字整除的最大正整数。、
T2807
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
class Solution {
public:
    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        auto ptr = head;
        while (ptr && ptr->next) {
            int t = gcd(ptr->val, ptr->next->val);
            auto node = new ListNode(t);
            node->next = ptr->next;
            ptr->next = node;
            ptr = node->next;
        }
        return head;
    }
};
/*
给定平面上 n 对 互不相同 的点 points ，其中 points[i] = [xi, yi] 。回旋镖 是由点 (i, j, k) 表示的元组 ，其中 i 和 j 之间的距离和 i 和 k 之间的欧式距离相等（需要考虑元组的顺序）。

返回平面上所有回旋镖的数量
T447
 */
class Solution {
public:
    int numberOfBoomerangs(vector<vector<int>>& points) {
        int n = points.size();
        int res = 0;
        for (int i = 0; i < n; i++) {
            unordered_map<long long, int> mp;
            for (int j = 0; j < n; j++) {
                long long m = pow(points[i][0] - points[j][0], 2) + pow(points[i][1] - points[j][1], 2);
                mp[m]++;
            }
            for (auto [x, y] : mp) {
                res += y * (y - 1);
            }
        }
        return res;
    }
};
/*
给你一个下标从 0 开始的字符串 s 和一个单词字典 dictionary 。你需要将 s 分割成若干个 互不重叠 的子字符串，每个子字符串都在 dictionary 中出现过。s 中可能会有一些 额外的字符 不在任何子字符串中。

请你采取最优策略分割 s ，使剩下的字符 最少 。
T2707
 */
class Solution {
public:
    int minExtraChar(string s, vector<string>& dictionary) {
        int n = s.size(), res = n;
        unordered_set<string> st(dictionary.begin(), dictionary.end());
        vector<int> dp(n, 0);
        for (int i = 0; i < n; i++) {
            string tmp = "";
            for (int j = i; j >= 0; j--) {
                tmp = s[j] + tmp;
                if (st.count(tmp)) {
                    dp[i] = max(dp[i], (j > 0 ? dp[j - 1] : 0) + (int)tmp.size());
                }
                dp[i] = max(dp[i], dp[j]);
            }
            // cout<<dp[i]<<endl;
            res = min(res, n - dp[i]);
        }
        return res;
    }
};
/*
给你一个仅由 大写 英文字符组成的字符串 s 。

你可以对此字符串执行一些操作，在每一步操作中，你可以从 s 中删除 任一个 "AB" 或 "CD" 子字符串。

通过执行操作，删除所有 "AB" 和 "CD" 子串，返回可获得的最终字符串的 最小 可能长度。

注意，删除子串后，重新连接出的字符串可能会产生新的 "AB" 或 "CD" 子串。
T2696
 */
class Solution {
public:
    int minLength(string s) {
        stack<char> sk;
        for (char c : s) {
            if (c == 'B' && !sk.empty() && sk.top() == 'A') {
                sk.pop();
                continue;
            }
            if (c == 'D' && !sk.empty() && sk.top() == 'C') {
                sk.pop();
                continue;
            }
            sk.emplace(c);
        }
        return sk.size();
    }
};

/*
给你一个字符串 word ，你可以向其中任何位置插入 "a"、"b" 或 "c" 任意次，返回使 word 有效 需要插入的最少字母数。

如果字符串可以由 "abc" 串联多次得到，则认为该字符串 有效 。
T2645
 */
class Solution {
public:
    int addMinimum(string word) {
        int index = 0, res = 0;
        for (int i = 0; i < word.size(); i++) {
            if (word[i] != index + 'a') {
                res++;
                i--;
            }
            index = (index + 1) % 3;
        }
        return res + (3 - index) % 3;
    }
};
/*
给你两个字符串数组 words1 和 words2 ，请你返回在两个字符串数组中 都恰好出现一次 的字符串的数目。
T2085
 */
class Solution {
public:
    int countWords(vector<string>& words1, vector<string>& words2) {
        map<string, int> m1, m2;
        int res = 0;
        for (auto i : words1) {
            m1[i]++;
        }
        for (auto i : words2) {
            m2[i]++;
        }
        for (auto [x, y] : m1) {
            if (y == 1 && m2[x] == 1) {
                res++;
            }
        }
        return res;
    }
};
/*
给你一个字符串 s 和一个整数 repeatLimit ，用 s 中的字符构造一个新字符串 repeatLimitedString ，使任何字母 连续 出现的次数都不超过 repeatLimit 次。你不必使用 s 中的全部字符。

返回 字典序最大的 repeatLimitedString 。

如果在字符串 a 和 b 不同的第一个位置，字符串 a 中的字母在字母表中出现时间比字符串 b 对应的字母晚，则认为字符串 a 比字符串 b 字典序更大 。如果字符串中前 min(a.length, b.length) 个字符都相同，那么较长的字符串字典序更大。
T2182
 */
class Solution {
public:
    string repeatLimitedString(string s, int repeatLimit) {
        vector<int> vec(26, 0);
        for (auto c : s) {
            vec[c - 'a']++;
        }
        int k = 0;
        string res = "";
        for (int i = 0; i < s.size(); i++) {
            for (int j = 25; j >= 0; j--) {
                if (vec[j] && (res.empty() || k < repeatLimit || res.back() != j + 'a')) {
                    if (res.empty() || res.back() != j + 'a') {
                        k = 0;
                    }
                    k++;
                    res += j + 'a';
                    vec[j]--;
                    break;
                }
            }
        }
        return res;
    }
};
/*
给定一个已排序的链表的头 head ， 删除所有重复的元素，使每个元素只出现一次 。返回 已排序的链表 。
T83
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        auto ptr = head;
        while (ptr) {
            while (ptr->next && ptr->next->val == ptr->val) {
                ptr->next = ptr->next->next;
            }
            ptr = ptr->next;
        }
        return head;
    }
};