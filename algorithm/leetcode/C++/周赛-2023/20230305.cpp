#include "head.h"
class Solution {
public:
    long long kthLargestLevelSum(TreeNode* root, int k) {
        queue<TreeNode*> mq;
        mq.emplace(root);
        priority_queue<int, vector<int>, greater<int>> mpq;
        while (!mq.empty()) {
            int len = mq.size();
            int t = 0;
            for (int i = 0; i < len; i++) {
                auto node = mq.front();
                mq.pop();
                t += node->val;
                if (node->left) {
                    mq.emplace(node->left);
                }
                if (node->right) {
                    mq.emplace(node->right);
                }
            }
            mpq.emplace(t);
            if (mpq.size() > k) {
                mpq.pop();
            }
        }
        if (mpq.size() < k) {
            return -1;
        }
        return mpq.top();
    }
};
class Solution {
public:
    int findValidSplit(vector<int>& nums) {
        map<int, vector<int>> mp;
        map<int, map<int, int>> temp;
        for (auto i : nums) {
            mp.emplace(i);
        }
        vector<int> prim(1e6, 1);
        set<int> st;
        for (int i = 2; i <= 1e6; i++) {
            if (prim[i]) {
                st.emplace(i);
                for (int j = 2; j * i <= 1e6; j++) {
                    if (mp.count(j)) {
                        mp[j].emplace_back(i);
                    }
                    prim[j] = 0;
                }
            }
        }
        for (auto [x, y] : mp) {
            int t = x;
            for (auto i : y) {
                while (t) {
                    if (t % i) {
                        temp[x][i]++;
                        t /= i;
                    } else {
                        break;
                    }
                }
            }
        }
        map<int, int> sum;
        for (auto i : nums) {
            for (auto [x, y] : temp[i]) {
                sum[x] += y;
            }
        }
        int n = nums.size();
        for (int i = 0; i <= n - 2; i++) {
            int flag = true;
            for (auto [x, y] : temp[nums[i]]) {
                sum[x] -= y;
                if (sum[x] != 0) {
                    flag = false;
                }
            }
            if (flag) {
                return i;
            }
        }
        return -1;
    }
};
class Solution {
public:
    int findValidSplit(vector<int>& nums) {
        int maxn = *max_element(nums.begin(), nums.end());
        unordered_map<int, int> temp, left, right;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            temp[nums[i]] = i;
        }
        vector<int> prim(maxn + 1, 1);
        for (int i = 2; i <= maxn; i++) {
            if (prim[i]) {
                for (int j = 1; j * i <= maxn; j++) {
                    if (temp.count(j * i)) {
                        right[temp[i * j]] = max(right[temp[i * j]], temp[i * j]);
                        if (!left.count(temp[i * j])) {
                            left[temp[i * j]] = temp[i * j];
                        }
                        left[temp[i * j]] = min(left[temp[i * j]], temp[i * j]);
                    }
                    prim[j * i] = 0;
                }
            }
        }
        int maxR = 0;
        for (int i = 0; i < n; i++) {
            if (i > maxR) {
                return i;
            }
            maxR = max(maxR, right[i]);
        }
        return -1;
    }
};
/*
给你一个长度为 n 的整数数组 nums ，下标从 0 开始。

如果在下标 i 处 分割 数组，其中 0 <= i <= n - 2 ，使前 i + 1 个元素的乘积和剩余元素的乘积互质，则认为该分割 有效 。

    例如，如果 nums = [2, 3, 3] ，那么在下标 i = 0 处的分割有效，因为 2 和 9 互质，而在下标 i = 1 处的分割无效，因为 6 和 3 不互质。
    在下标 i = 2 处的分割也无效，因为 i == n - 1 。

返回可以有效分割数组的最小下标 i ，如果不存在有效分割，则返回 -1 。

当且仅当 gcd(val1, val2) == 1 成立时，val1 和 val2 这两个值才是互质的，其中 gcd(val1, val2) 表示 val1 和 val2 的最大公约数。
2584
 */
class Solution {
public:
    int findValidSplit(vector<int>& nums) {
        int maxn = *max_element(nums.begin(), nums.end());
        unordered_map<int, unordered_map<int, int>> temp;
        unordered_set<int> p;
        for (auto i : nums) {
            temp[i] = {};
        }
        vector<int> prim(maxn + 1, 1);
        for (int i = 2; i * i <= maxn; i++) {
            if (prim[i]) {
                p.emplace(i);
                for (int j = 1; j * i <= maxn; j++) {
                    prim[j * i] = 0;
                }
            }
        }
        for (auto [x, y] : temp) {
            int t = x;
            for (auto i : p) {
                if (t % i)
                    continue;
                if (t < i)
                    break;
                while (t % i == 0) {
                    t /= i;
                    temp[x][i]++;
                }
            }
            if (t > 1) {
                temp[x][t]++;
            }
        }
        unordered_map<int, int> sum;
        map<int, int> now;
        for (auto i : nums) {
            for (auto [x, y] : temp[i]) {
                sum[x] += y;
            }
        }
        int n = nums.size();
        for (int i = 0; i <= n - 2; i++) {
            int flag = true;
            for (auto [x, y] : temp[nums[i]]) {
                sum[x] -= y;
                now[x] += y;
                if (sum[x] != 0) {
                    flag = false;
                }
            }
            if (!flag) {
                continue;
            }
            for (auto [x, y] : now) {
                if (sum[x] != 0) {
                    flag = false;
                } else {
                    now.erase(x);
                }
            }
            if (flag) {
                return i;
            }
        }
        return -1;
    }
};
// 方法二 类似跳跃游戏 找最远的能到达的地方，超过最远的地方后就是互质的另外一部分

/*
考试中有 n 种类型的题目。给你一个整数 target 和一个下标从 0 开始的二维整数数组 types ，其中 types[i] = [counti, marksi] 表示第 i 种类型的题目有 counti 道，每道题目对应 marksi 分。

返回你在考试中恰好得到 target 分的方法数。由于答案可能很大，结果需要对 109 +7 取余。

注意，同类型题目无法区分。

    比如说，如果有 3 道同类型题目，那么解答第 1 和第 2 道题目与解答第 1 和第 3 道题目或者第 2 和第 3 道题目是相同的。
2585
 */
class Solution {
public:
    int waysToReachTarget(int target, vector<vector<int>>& types) {
        int n = types.size(), dp[n + 1][target + 1];
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= target; j++) {
                for (int k = 0; k * types[i - 1][1] <= j && k <= types[i - 1][0]; k++) {
                    dp[i][j] += dp[i - 1][j - k * types[i - 1][1]];
                    dp[i][j] %= 1000000007;
                }
            }
        }
        return dp[n][target];
    }
};
// 一维
class Solution {
public:
    int waysToReachTarget(int target, vector<vector<int>>& types) {
        int dp[target + 1];
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        for (auto vec : types) {
            for (int i = target; i >= 0; i--) {
                for (int k = 1; k * vec[1] <= i && k <= vec[0]; k++) {
                    dp[i] += dp[i - k * vec[1]];
                    dp[i] %= 1000000007;
                }
            }
        }
        return dp[target];
    }
};