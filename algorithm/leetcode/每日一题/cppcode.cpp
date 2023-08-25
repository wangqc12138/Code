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
/*
给你一个整数数组 nums，请你找出并返回能被三整除的元素最大和。
T1262
 */

class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        sort(nums.begin(), nums.end(), greater());
        vector<int> v1, v2;
        int res = 0;
        for (auto i : nums) {
            if (i % 3 == 0) {
                res += i;
            } else if (i % 3 == 1) {
                v1.emplace_back(i);
            } else {
                v2.emplace_back(i);
            }
        }
        int m = v1.size(), n = v2.size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
            }
        }
        return res;
    }
};
/*
在 n*m 大小的棋盘中，有黑白两种棋子，黑棋记作字母 "X", 白棋记作字母 "O"，空余位置记作 "."。
当落下的棋子与其他相同颜色的棋子在行、列或对角线完全包围（中间不存在空白位置）另一种颜色的棋子，则可以翻转这些棋子的颜色。
「力扣挑战赛」黑白翻转棋项目中，将提供给选手一个未形成可翻转棋子的棋盘残局，其状态记作 chessboard。若下一步可放置一枚黑棋，请问选手最多能翻转多少枚白棋。
 */
using pii = pair<int, int>;
class Solution {
public:
    int flipChess(vector<string>& chessboard) {
        queue<pii> mq;
        while (!mq.empty()) {
        }
    }
};
/*
给你四个整数 m、n、introvertsCount 和 extrovertsCount 。有一个 m x n 网格，和两种类型的人：内向的人和外向的人。
总共有 introvertsCount 个内向的人和 extrovertsCount 个外向的人。

请你决定网格中应当居住多少人，并为每个人分配一个网格单元。 注意，不必 让所有人都生活在网格中。

每个人的 幸福感 计算如下：

    内向的人 开始 时有 120 个幸福感，但每存在一个邻居（内向的或外向的）他都会 失去  30 个幸福感。
    外向的人 开始 时有 40 个幸福感，每存在一个邻居（内向的或外向的）他都会 得到  20 个幸福感。

邻居是指居住在一个人所在单元的上、下、左、右四个直接相邻的单元中的其他人。

网格幸福感 是每个人幸福感的 总和 。 返回 最大可能的网格幸福感 。
T1659
 */
class Solution {
public:
    int getMaxGridHappiness(int m, int n, int introvertsCount, int extrovertsCount) {
    }
};
/*
给你一个以 (radius, xCenter, yCenter) 表示的圆和一个与坐标轴平行的矩形 (x1, y1, x2, y2) ，其中 (x1, y1) 是矩形左下角的坐标，而 (x2, y2) 是右上角的坐标。

如果圆和矩形有重叠的部分，请你返回 true ，否则返回 false 。

换句话说，请你检测是否 存在 点 (xi, yi) ，它既在圆上也在矩形上（两者都包括点落在边界上的情况）。
T1401
 */
class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
    }
};
/*
给你一个正整数 n ，找出满足下述条件的 中枢整数 x ：

    1 和 x 之间的所有元素之和等于 x 和 n 之间所有元素之和。

返回中枢整数 x 。如果不存在中枢整数，则返回 -1 。题目保证对于给定的输入，至多存在一个中枢整数。
T2485
 */
class Solution {
public:
    int pivotInteger(int n) {
        int sum = (1 + n) * n / 2, t = 0;
        for (int i = 1; i <= n; i++) {
            if (t == sum - t - i) {
                return i;
            }
            t += i;
        }
        return -1;
    }
};
/*
给你一个整数数组，返回它的某个 非空 子数组（连续元素）在执行一次可选的删除操作后，所能得到的最大元素总和。
换句话说，你可以从原数组中选出一个子数组，并可以决定要不要从中删除一个元素（只能删一次哦），
（删除后）子数组中至少应当有一个元素，然后该子数组（剩下）的元素总和是所有子数组之中最大的。

注意，删除一个元素后，子数组 不能为空。
T1186
 */
// 这错了 这是数组删除子数组后的最大值
class Solution {
public:
    int maximumSum(vector<int>& arr) {
        int max_value = *max_element(arr.begin(), arr.end());
        if (max_value <= 0) {
            return max(arr[0], arr.back());
        }
        int m = INT_MIN, t = 0, n = arr.size(), k = INT_MAX;
        for (int i = 0; i < n; i++) {
            t += arr[i];
            m = max(t, m);
            k = min(k, t - m);
        }
        return accumulate(arr.begin(), arr.end(), 0) - k;
    }
};
//
class Solution {
public:
    int maximumSum(vector<int>& arr) {
    }
};
/*
给你一个整数数组 nums​​​ 和一个整数 k 。你需要将这个数组划分到 k 个相同大小的子集中，使得同一个子集里面没有两个相同的元素。

一个子集的 不兼容性 是该子集里面最大值和最小值的差。

请你返回将数组分成 k 个子集后，各子集 不兼容性 的 和 的 最小值 ，如果无法分成分成 k 个子集，返回 -1 。

子集的定义是数组中一些数字的集合，对数字顺序没有要求。
T1681
 */
class Solution {
public:
    int minimumIncompatibility(vector<int>& nums, int k) {
    }
};
/*
给你一个 2 行 n 列的二进制数组：

    矩阵是一个二进制矩阵，这意味着矩阵中的每个元素不是 0 就是 1。
    第 0 行的元素之和为 upper。
    第 1 行的元素之和为 lower。
    第 i 列（从 0 开始编号）的元素之和为 colsum[i]，colsum 是一个长度为 n 的整数数组。

你需要利用 upper，lower 和 colsum 来重构这个矩阵，并以二维整数数组的形式返回它。

如果有多个不同的答案，那么任意一个都可以通过本题。

如果不存在符合要求的答案，就请返回一个空的二维数组。
T1253
 */
class Solution {
public:
    vector<vector<int>> reconstructMatrix(int upper, int lower, vector<int>& colsum) {
    }
};
/*
给你两个 非空 链表来代表两个非负整数。数字最高位位于链表开始位置。它们的每个节点只存储一位数字。将这两数相加会返回一个新的链表。

你可以假设除了数字 0 之外，这两个数字都不会以零开头。
T445
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* RES;
        function<int(ListNode*, ListNode*)> dfs = [&](ListNode* t1, ListNode* t2) -> int {

        };
    }
};
/*
给你一个下标从 0 开始的二维整数数组 nums 。一开始你的分数为 0 。你需要执行以下操作直到矩阵变为空：

    矩阵中每一行选取最大的一个数，并删除它。如果一行中有多个最大的数，选择任意一个并删除。
    在步骤 1 删除的所有数字中找到最大的一个数字，将它添加到你的 分数 中。

请你返回最后的 分数 。
T2679
 */
class Solution {
public:
    int matrixSum(vector<vector<int>>& nums) {
        for (auto& vec : nums) {
            sort(vec.begin(), vec.end(), greater());
        }
        int res = 0;
        for (int j = 0; j < nums[0].size(); j++) {
            int t = INT_MIN;
            for (int i = 0; i < nums.size(); i++) {
                t = max(t, nums[i][j]);
            }
            res += t;
        }
        return res;
    }
};
/*
袋子中装有一些物品，每个物品上都标记着数字 1 、0 或 -1 。

给你四个非负整数 numOnes 、numZeros 、numNegOnes 和 k 。

袋子最初包含：

    numOnes 件标记为 1 的物品。
    numZeroes 件标记为 0 的物品。
    numNegOnes 件标记为 -1 的物品。

现计划从这些物品中恰好选出 k 件物品。返回所有可行方案中，物品上所标记数字之和的最大值。
T2600
 */
class Solution {
public:
    int kItemsWithMaximumSum(int numOnes, int numZeros, int numNegOnes, int k) {
        if (k <= numOnes) {
            return k;
        } else if (k <= numZeros + numOnes) {
            return numOnes;
        } else {
            return numOnes - (k - numOnes - numZeros);
        }
    }
};
/*
给你一个整数 finalSum 。请你将它拆分成若干个 互不相同 的正偶数之和，且拆分出来的正偶数数目 最多 。

    比方说，给你 finalSum = 12 ，那么这些拆分是 符合要求 的（互不相同的正偶数且和为 finalSum）：(2 + 10) ，(2 + 4 + 6) 和 (4 + 8) 。
    它们中，(2 + 4 + 6) 包含最多数目的整数。注意 finalSum 不能拆分成 (2 + 2 + 4 + 4) ，因为拆分出来的整数必须互不相同。

请你返回一个整数数组，表示将整数拆分成 最多 数目的正偶数数组。如果没有办法将 finalSum 进行拆分，请你返回一个 空 数组。你可以按 任意 顺序返回这些整数。
T2178
 */
class Solution {
public:
    vector<long long> maximumEvenSplit(long long finalSum) {
        vector<long long> res;
        if (finalSum % 2) {
            return res;
        }
        for (int i = 2; i <= finalSum; i += 2) {
            if (finalSum > i * 2) {
                res.emplace_back(i);
                finalSum -= i;
            } else {
                res.emplace_back(finalSum);
                break;
            }
        }
        return res;
    }
};
/*
一个下标从 0 开始的数组的 交替和 定义为 偶数 下标处元素之 和 减去 奇数 下标处元素之 和 。

    比方说，数组 [4,2,5,3] 的交替和为 (4 + 5) - (2 + 3) = 4 。

给你一个数组 nums ，请你返回 nums 中任意子序列的 最大交替和 （子序列的下标 重新 从 0 开始编号）。

一个数组的 子序列 是从原数组中删除一些元素后（也可能一个也不删除）剩余元素不改变顺序组成的数组。
比方说，[2,7,4] 是 [4,2,3,7,2,1,4] 的一个子序列（加粗元素），但是 [2,4,2] 不是。
T1911
 */
class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        vector<vector<long long>> dp(n, vector<long long>(2, 0));
        dp[0][0] = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + nums[i]);
            dp[i][1] = max(dp[i - 1][0] - nums[i], dp[i - 1][1]);
        }
        return max(dp[n - 1][0], dp[n - 1][1]);
    }
};
class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        long long M = nums[0], N = 0;
        for (int i = 1; i < nums.size(); i++) {
            M = max(M, N + nums[i]);
            N = max(M - nums[i], N);
        }
        return max(M, N);
    }
};
/*
给定一个有 N 个结点的二叉树的根结点 root，树中的每个结点上都对应有 node.val 枚硬币，并且总共有 N 枚硬币。

在一次移动中，我们可以选择两个相邻的结点，然后将一枚硬币从其中一个结点移动到另一个结点。(移动可以是从父结点到子结点，或者从子结点移动到父结点。)。

返回使每个结点上只有一枚硬币所需的移动次数。
T979
 */
class Solution {
public:
    int distributeCoins(TreeNode* root) {
        int res = 0;
        function<int(TreeNode*, int)> dfs = [&](TreeNode* node, int t) -> int {
            if (node == nullptr) {
                return 0;
            }
            int lv = dfs(node->left, 0);
            int rv = dfs(node->right, 0);
            int nv = node->val;
            nv = nv - 1 + (lv + rv) * 2;
            return nv;
        };

        return dfs(root, 0);
    }
};