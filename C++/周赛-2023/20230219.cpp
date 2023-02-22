#include "head.h"
/*
给你两个 二维 整数数组 nums1 和 nums2.
    nums1[i] = [idi, vali] 表示编号为 idi 的数字对应的值等于 vali 。
    nums2[i] = [idi, vali] 表示编号为 idi 的数字对应的值等于 vali 。
每个数组都包含 互不相同 的 id ，并按 id 以 递增 顺序排列。
请你将两个数组合并为一个按 id 以递增顺序排列的数组，并符合下述条件：
    只有在两个数组中至少出现过一次的 id 才能包含在结果数组内。
    每个 id 在结果数组中 只能出现一次 ，并且其对应的值等于两个数组中该 id 所对应的值求和。如果某个数组中不存在该 id ，则认为其对应的值等于 0 。
返回结果数组。返回的数组需要按 id 以递增顺序排列。
 */
class Solution {
public:
    vector<vector<int>> mergeArrays(vector<vector<int>>& nums1, vector<vector<int>>& nums2) {
        map<int, int> mp;
        for (auto vec : nums1) {
            mp[vec[0]] += vec[1];
        }
        for (auto vec : nums2) {
            mp[vec[0]] += vec[1];
        }
        vector<vector<int>> res;
        for (auto [x, y] : mp) {
            res.push_back({x, y});
        }
        return res;
    }
};
/*
给你一个正整数 n ，你可以执行下述操作 任意 次：
    n 加上或减去 2 的某个 幂
返回使 n 等于 0 需要执行的 最少 操作数。
如果 x == 2i 且其中 i >= 0 ，则数字 x 是 2 的幂。
 */
class Solution {
public:
    int minOperations(int n) {
        int res = 1;
        while (n & (n - 1)) {
            int t = n & (-n);
            if (n & (t << 1)) {
                n += t;
            } else {
                n -= t;
            }
            res++;
        }
        return res;
    }
};
/*
给你一个正整数数组 nums 。
如果数组 nums 的子集中的元素乘积是一个 无平方因子数 ，则认为该子集是一个 无平方 子集。
无平方因子数 是无法被除 1 之外任何平方数整除的数字。
返回数组 nums 中 无平方 且 非空 的子集数目。因为答案可能很大，返回对 109 + 7 取余的结果。
nums 的 非空子集 是可以由删除 nums 中一些元素（可以不删除，但不能全部删除）得到的一个数组。如果构成两个子集时选择删除的下标不同，则认为这两个子集不同。
 */
class Solution {
public:
    map<int, set<int>> mp;
    int squareFreeSubsets(vector<int>& nums) {
        set<int> st;
        for (int i = 2; i <= 30; i++) {
            st.emplace(i * i);
        }
        for (int i = 1; i <= 30; i++) {
            for (int j = 1; j <= 30; j++) {
                for (auto k : st) {
                    if (i * j % k == 0) {
                        mp[i].emplace(j);
                        break;
                    }
                }
            }
        }
        sort(nums.begin(), nums.end());
    }
    int dfs(vector<int>& nums, int index, set<int>& now) {
    }
};
class Solution {
public:
    int squareFreeSubsets(vector<int>& nums) {
        // 质数表
        const int MAXK = 10;
        int prime[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
        // 检查 x 是否为平方数
        auto check = [&](int x) {
            for (int i = 0; i < MAXK; i++)
                if (x % (prime[i] * prime[i]) == 0)
                    return true;
            return false;
        };
        const int MOD = 1e9 + 7;
        int n = nums.size();
        long long f[n + 1][1 << MAXK];
        memset(f, 0, sizeof(f));
        f[0][0] = 1;
        for (int i = 1; i <= n; i++) {
            // 不把第 i 个数加入子集的方案数
            for (int j = 0; j < (1 << MAXK); j++) f[i][j] = f[i - 1][j];
            int x = nums[i - 1];
            // 如果 x 是平方数，那么肯定不能把它加入子集，直接看下一个数
            if (check(x))
                continue;
            // 计算第 i 个数的质因数分解
            int msk = 0;
            for (int j = 0; j < MAXK; j++)
                if (x % prime[j] == 0)
                    msk |= 1 << j;
            // 把第 i 个数加入子集的方案数
            for (int j = 0; j < (1 << MAXK); j++)
                if ((j & msk) == 0)
                    f[i][j | msk] = (f[i][j | msk] + f[i - 1][j]) % MOD;
        }
        long long ans = 0;
        for (int j = 0; j < (1 << MAXK); j++) ans = (ans + f[n][j]) % MOD;
        // 注意题目求的是非空子集，因此要扣掉空集合
        ans = (ans - 1 + MOD) % MOD;
        return ans;
    }
};
/*
给你一个整数数组 nums 。如果 nums 的一个子集中，所有元素的乘积可以表示为一个或多个 互不相同的质数 的乘积，那么我们称它为 好子集 。

    比方说，如果 nums = [1, 2, 3, 4] ：
        [2, 3] ，[1, 2, 3] 和 [1, 3] 是 好 子集，乘积分别为 6 = 2*3 ，6 = 2*3 和 3 = 3 。
        [1, 4] 和 [4] 不是 好 子集，因为乘积分别为 4 = 2*2 和 4 = 2*2 。

请你返回 nums 中不同的 好 子集的数目对 109 + 7 取余 的结果。

nums 中的 子集 是通过删除 nums 中一些（可能一个都不删除，也可能全部都删除）元素后剩余元素组成的数组。如果两个子集删除的下标不同，那么它们被视为不同的子集。
1994
 */
class Solution {
public:
    int numberOfGoodSubsets(vector<int>& nums) {
    }
};