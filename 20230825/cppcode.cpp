#include "head.h"
/*
给你一棵根为 root 的二叉树，请你返回二叉树中好节点的数目。

「好节点」X 定义为：从根到该节点 X 所经过的节点中，没有任何节点的值大于 X 的值。
T1448
 */
class Solution {
public:
    int goodNodes(TreeNode* root) {
        int res = 0;
        function<void(TreeNode*, int)> dfs = [&](TreeNode* node, int maxn) {
            if (root == nullptr) {
                return;
            }
            if (root->val >= maxn) {
                res++;
            }
            dfs(node->left, max(maxn, root->val));
            dfs(node->right, max(maxn, root->val));
        };
        dfs(root, root->val);
        return res;
    }
};

/*
这里有一幅服务器分布图，服务器的位置标识在 m * n 的整数矩阵网格 grid 中，1 表示单元格上有服务器，0 表示没有。

如果两台服务器位于同一行或者同一列，我们就认为它们之间可以进行通信。

请你统计并返回能够与至少一台其他服务器进行通信的服务器的数量。
T1267
 */
class Solution {
public:
    int countServers(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), sum = 0;
        vector<int> col(m, 0), row(n, 0);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                sum += grid[i][j];
                col[i] += grid[i][j];
                row[j] += grid[i][j];
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1 && col[i] == 1 && row[j] == 1) {
                    sum--;
                }
            }
        }
        return sum;
    }
};
/*
给定一个  无重复元素 的 有序 整数数组 nums 。

返回 恰好覆盖数组中所有数字 的 最小有序 区间范围列表 。也就是说，nums 的每个元素都恰好被某个区间范围所覆盖，并且不存在属于某个范围但不属于 nums 的数字 x 。

列表中的每个区间范围 [a,b] 应该按如下格式输出：

    "a->b" ，如果 a != b
    "a" ，如果 a == b

T228
 */

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        int t = 0, n = nums.size();
        vector<string> res;
        if (n == 0) {
            return res;
        }
        for (int i = 1; i < n; i++) {
            if (nums[t] != nums[i] - (i - t)) {
                if (t == i - 1) {
                    res.emplace_back(to_string(nums[t]));
                } else {
                    res.emplace_back(to_string(nums[t]) + "->" + to_string(nums[i - 1]));
                }
                t = i;
            }
        }
        if (t == n - 1) {
            res.emplace_back(to_string(nums[t]));
        } else {
            res.emplace_back(to_string(nums[t]) + "->" + to_string(nums[n - 1]));
        }
        return res;
    }
};
/*
给你一个 无重叠的 ，按照区间起始端点排序的区间列表。

在列表中插入一个新的区间，你需要确保列表中的区间仍然有序且不重叠（如果有必要的话，可以合并区间）。
T57
 */
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int flag = 0;
        vector<vector<int>> res;
        for (auto vec : intervals) {
            if (flag == 0) {
                if (vec[1] < newInterval[0]) {
                    res.emplace_back(vec);
                } else {
                    vector<int> temp;
                    temp.emplace_back(min(vec[0], newInterval[0]));
                    res.emplace_back(temp);
                    if (newInterval[1] <= vec[1]) {
                        res.back().emplace_back(vec[1]);
                        flag = 2;
                    } else {
                        flag = 1;
                    }
                }
            } else if (flag == 1) {
                if (newInterval[1] < vec[0]) {
                    res.back().emplace_back(vec[0]);
                    flag = 2;
                } else if (newInterval[1] <= vec[1]) {
                    res.back().emplace_back(vec[1]);
                    flag = 2;
                }
            } else {
                res.emplace_back(vec);
            }
        }
        if (flag == 1) {
            res.back().emplace_back(newInterval[1]);
        }
        if (flag == 0) {
            res.emplace_back(newInterval);
        }
        return res;
    }
};
/*
给出一个含有不重复整数元素的数组 arr ，每个整数 arr[i] 均大于 1。

用这些整数来构建二叉树，每个整数可以使用任意次数。其中：每个非叶结点的值应等于它的两个子结点的值的乘积。

满足条件的二叉树一共有多少个？答案可能很大，返回 对 109 + 7 取余 的结果。
T823
 */
class Solution {
public:
    int numFactoredBinaryTrees(vector<int>& arr) {
        set<int> st(arr.begin(), arr.end());
        int res = 0;
        map<int, int> mp;
        function<long long(int)> dfs = [&](int n) -> long long {
            if (mp.count(n)) {
                return mp[n];
            }
            long long re = 1;
            for (auto i : st) {
                if ((long long)i * i <= n && n % i == 0 && st.count(n / i)) {
                    long long k = dfs(i);
                    if (i * i != n) {
                        re += (long long)2 * k * dfs(n / i) % 1000000007;
                    } else {
                        re += (long long)k * k;
                    }
                    re %= 1000000007;
                }
            }
            mp[n] = re;
            return re;
        };
        for (auto i : st) {
            res += dfs(i);
            res %= 1000000007;
        }
        return res;
    }
};
/*
有一只跳蚤的家在数轴上的位置 x 处。请你帮助它从位置 0 出发，到达它的家。

跳蚤跳跃的规则如下：

    它可以 往前 跳恰好 a 个位置（即往右跳）。
    它可以 往后 跳恰好 b 个位置（即往左跳）。
    它不能 连续 往后跳 2 次。
    它不能跳到任何 forbidden 数组中的位置。

跳蚤可以往前跳 超过 它的家的位置，但是它 不能跳到负整数 的位置。

给你一个整数数组 forbidden ，其中 forbidden[i] 是跳蚤不能跳到的位置，同时给你整数 a， b 和 x ，请你返回跳蚤到家的最少跳跃次数。如果没有恰好到达 x 的可行方案，请你返回 -1 。
T1654
 */
class Solution {
public:
    int minimumJumps(vector<int>& forbidden, int a, int b, int x) {
        set<pair<int, int>> visit;
        for (auto i : forbidden) {
            visit.emplace(i, 0);
            visit.emplace(i, 1);
        }
        queue<pair<int, int>> mq;
        mq.emplace(0, 0);
        visit.emplace(0, 0);
        int res = 0;
        while (!mq.empty()) {
            int len = mq.size();
            for (int i = 0; i < len; i++) {
                int t = mq.front().first;
                int d = mq.front().second;
                mq.pop();
                if (t == x) {
                    return res;
                }
                // 数学计算？md不想看了
                if (t <= 2000 + b && !visit.count(pair<int, int>(t + a, 0))) {
                    mq.emplace(t + a, 0);
                    visit.emplace(t + a, 0);
                }
                if (d == 0) {
                    if (t - b > 0 && !visit.count(pair<int, int>(t - b, 1))) {
                        mq.emplace(t - b, 1);
                        visit.emplace(t - b, 1);
                    }
                }
            }
            res++;
        }
        return -1;
    }
};