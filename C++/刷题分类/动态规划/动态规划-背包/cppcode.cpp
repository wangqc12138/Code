#include "head.h"
// 最值问题
/*
给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。
如果没有任何一种硬币组合能组成总金额，返回 -1。
你可以认为每种硬币的数量是无限的。
322
 */
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        for (int i = 0; i <= amount; i++) {
            for (int coin : coins) {
                if (coin <= i) {
                    dp[i] = min(dp[i - coin] + 1, dp[i]);
                }
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }
};
/*
给你一个二进制字符串数组 strs 和两个整数 m 和 n 。
请你找出并返回 strs 的最大子集的大小，该子集中 最多 有 m 个 0 和 n 个 1 。
如果 x 的所有元素也是 y 的元素，集合 x 是集合 y 的 子集 。
1 <= strs.length <= 600
1 <= strs[i].length <= 100
strs[i] 仅由 '0' 和 '1' 组成
1 <= m, n <= 100
474
对于此类题可以现在表格里推一下
*/
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (string str : strs) {
            int n0 = 0, n1 = 0;
            for (char c : str) {
                if (c == '0') {
                    n0++;
                } else {
                    n1++;
                }
            }
            for (int i = m; i >= n0; i--) {
                for (int j = n; j >= n1; j--) {
                    dp[i][j] = max(dp[i - n0][j - n1] + 1, dp[i][j]);
                }
            }
        }
        return dp[m][n];
    }
};
/*
有一堆石头，每块石头的重量都是正整数。
每一回合，从中选出任意两块石头，然后将它们一起粉碎。假设石头的重量分别为 x 和 y，且 x <= y。那么粉碎的可能结果如下：
    如果 x == y，那么两块石头都会被完全粉碎；
    如果 x != y，那么重量为 x 的石头将会完全粉碎，而重量为 y 的石头新重量为 y-x。
最后，最多只会剩下一块石头。返回此石头最小的可能重量。如果没有石头剩下，就返回 0。
*/
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int sum = accumulate(stones.begin(), stones.end(), 0);
        int target = sum / 2;
        vector<int> dp(target + 1);
        for (int stone : stones) {
            for (int i = target; i >= stone; i--) {
                dp[i] = max(dp[i - stone] + stone, dp[i]);
            }
        }
        return sum - 2 * dp[target];
    }
};
/*
给定正整数 n，找到若干个完全平方数（比如 1, 4, 9, 16, ...）使得它们的和等于 n。你需要让组成和的完全平方数的个数最少。
给你一个整数 n ，返回和为 n 的完全平方数的 最少数量 。
完全平方数 是一个整数，其值等于另一个整数的平方；换句话说，其值等于一个整数自乘的积。
例如，1、4、9 和 16 都是完全平方数，而 3 和 11 不是。
279
 */
class Solution {
public:
    int numSquares(int n) {
        vector<int> nums;
        for (int i = 1; i <= n; i++) {
            if (i * i < n) {
                nums.push_back(i * i);
            } else if (i * i == n) {
                return 1;
            } else {
                break;
            }
        }
        vector<int> dp(n + 1, n + 1);
        dp[0] = 0;
        for (int num : nums) {
            for (int i = num; i <= n; i++) {
                dp[i] = min(dp[i - num] + 1, dp[i]);
            }
        }
        return dp[n];
    }
};
// True/Fasle问题
/*
给你一个 只包含正整数 的 非空 数组 nums 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
416
 */
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2 != 0) {
            return false;
        }
        int target = sum / 2;
        vector<bool> dp(target + 1, false);
        dp[0] = true;
        for (int num : nums) {
            for (int i = target; i >= num; i--) {
                dp[i] = dp[i - num] || dp[i];
            }
        }
        return dp[target];
    }
};
/*
给定一个非空字符串 s 和一个包含非空单词的列表 wordDict，判定 s 是否可以被空格拆分为一个或多个在字典中出现的单词。
说明：
    拆分时可以重复使用字典中的单词。
    你可以假设字典中没有重复的单词。
139
 */
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;
        for (int i = 1; i < dp.size(); i++) {
            for (string str : wordDict) {
                string ss = s.substr(0, i);
                int index = 0;
                int pos = ss.find(str, index);
                while (pos != string::npos) {
                    dp[pos + str.size()] = dp[pos] || dp[pos + str.size()];
                    index = pos + 1;
                    pos = ss.find(str, index);
                }
            }
        }
        return dp[s.size()];
    }
};
// 组合问题
/*
给你一个由 不同 整数组成的数组 nums ，和一个目标整数 target 。请你从 nums 中找出并返回总和为 target 的元素组合的个数。

题目数据保证答案符合 32 位整数范围。
377
考虑顺序
 */
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<int> dp(target + 1);
        dp[0] = 1;
        for (int i = 0; i <= target; i++) {
            for (int num : nums) {
                if (i >= num) {
                    dp[i] += dp[i - num];
                }
            }
        }
        return dp[target];
    }
};
/*
给定一个非负整数数组，a1, a2, ..., an, 和一个目标数，S。现在你有两个符号 + 和 -。对于数组中的任意一个整数，
你都可以从 + 或 -中选择一个符号添加在前面。
返回可以使最终数组和为目标数 S 的所有添加符号的方法数。
ps 给的target是隐含的
494
 */
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (target > sum || (target + sum) % 2 == 1) {
            return 0;
        }
        int t = (target + sum) / 2;
        vector<int> dp(t + 1);
        dp[0] = 1;
        for (int num : nums) {
            for (int i = t; i >= num; i--) {
                dp[i] += dp[i - num];
            }
        }
        return dp[t];
    }
};
/*
给定不同面额的硬币和一个总金额。写出函数来计算可以凑成总金额的硬币组合数。假设每一种面额的硬币有无限个。
518
 */
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        vector<unsigned int> dp(amount + 1, 0);
        dp[0] = 1;
        for (int coin : coins) {
            for (int i = coin; i <= amount; i++) {
                dp[i] += dp[i - coin];
            }
        }
        return dp[amount];
    }
};
// 0-1背包
/*
给你一个 只包含正整数 的 非空 数组 nums 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
416
 */
// 用指定大小sum/2的背包去装nums的数字，只能选一次，恰好装到sum/2
// 背包指代当前的和，
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size(), sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2) {
            return false;
        }
        int target = sum / 2;
        vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));
        // 选择0时和为0/2是正确的
        dp[0][0] = true;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= target; j++) {
                // 可以选择第i号时，结果是不选和选的或
                if (j >= nums[i - 1]) {
                    dp[i][j] = dp[i - 1][j] | dp[i - 1][j - nums[i - 1]];
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[n][target];
    }
};
// 一维
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size(), sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2) {
            return false;
        }
        int target = sum / 2;
        vector<bool> dp(target + 1, false);
        dp[0] = true;
        for (int i = 0; i < n; i++) {
            for (int j = target; j >= nums[i]; j--) {
                dp[j] = dp[j] | dp[j - nums[i]];
            }
        }
        return dp[target];
    }
};
/*
给你一个二进制字符串数组 strs 和两个整数 m 和 n 。

请你找出并返回 strs 的最大子集的长度，该子集中 最多 有 m 个 0 和 n 个 1 。

如果 x 的所有元素也是 y 的元素，集合 x 是集合 y 的 子集 。
474
这个是数组里选元素，如果是字符串则是滑动窗口-字串的前提
 */
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<pair<int, int>> temp;
        for (auto str : strs) {
            int i0 = 0;
            for (auto i : str) {
                i0 += i == '0';
            }
            temp.emplace_back(i0, str.size() - i0);
        }
        int len = strs.size();
        int dp[len + 1][m + 1][n + 1];
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= len; i++) {
            for (int j = 0; j <= m; j++) {
                for (int k = 0; k <= n; k++) {
                    if (temp[i - 1].first <= j && temp[i - 1].second <= k) {
                        dp[i][j][k] = max(dp[i - 1][j][k], dp[i - 1][j - temp[i - 1].first][k - temp[i - 1].second] + 1);
                    } else {
                        dp[i][j][k] = dp[i - 1][j][k];
                    }
                }
            }
        }
        return dp[len][m][n];
    }
};
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        int dp[m + 1][n + 1];
        memset(dp, 0, sizeof(dp));
        for (auto str : strs) {
            int c0 = count(str.begin(), str.end(), '0'), c1 = str.size() - c0;
            for (int i = m; i >= c0; i--) {
                for (int j = n; j >= c1; j--) {
                    dp[i][j] = max(dp[i][j], dp[i - c0][j - c1] + 1);
                }
            }
        }
        return dp[m][n];
    }
};
/*
给你一个整数数组 nums 和一个整数 target 。

向数组中的每个整数前添加 '+' 或 '-' ，然后串联起所有整数，可以构造一个 表达式 ：

    例如，nums = [2, 1] ，可以在 2 之前添加 '+' ，在 1 之前添加 '-' ，然后串联起来得到表达式 "+2-1" 。

返回可以通过上述方法构造的、运算结果等于 target 的不同 表达式 的数目。
494
 */
// 背包大小为(sum+target)/2，恰好装满的方案有几种？
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        // t1+t2=sum,t1-t2=target
        if (sum < abs(target) || (sum + target) % 2) {
            return 0;
        }
        int t = (sum + target) / 2, n = nums.size();
        int dp[n + 1][t + 1];
        memset(dp, 0, sizeof(dp));
        // 背包大小为0，恰好装0个物品的方案是一种
        dp[0][0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= t; j++) {
                if (j >= nums[i - 1]) {
                    // 背包大小为j，恰好装满的方案数是不装第i-1个物品和装i-1个物品中的较大的方案数?不是，此时的方案数应该是不装+装的
                    // 装i-1个的物品为上次选择时的j-nums[i-1]的背包大小的方案数
                    dp[i][j] = dp[i - 1][j] + dp[i - 1][j - nums[i - 1]];
                } else {
                    // 容量不够装不了
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[n][t];
    }
};
// 一维
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        // t1+t2=sum,t1-t2=target
        if (sum < abs(target) || (sum + target) % 2) {
            return 0;
        }
        int t = (sum + target) / 2, n = nums.size();
        int dp[t + 1];
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        for (auto i : nums) {
            for (int j = t; j >= i; j--) {
                dp[j] += dp[j - i];
            }
        }
        return dp[t];
    }
};
/*
有一堆石头，用整数数组 stones 表示。其中 stones[i] 表示第 i 块石头的重量。

每一回合，从中选出任意两块石头，然后将它们一起粉碎。假设石头的重量分别为 x 和 y，且 x <= y。那么粉碎的可能结果如下：

    如果 x == y，那么两块石头都会被完全粉碎；
    如果 x != y，那么重量为 x 的石头将会完全粉碎，而重量为 y 的石头新重量为 y-x。

最后，最多只会剩下一块 石头。返回此石头 最小的可能重量 。如果没有石头剩下，就返回 0。
1049
 */
// 最大容量为sum/2的背包最多装多少石头？sum-2倍这个最大容量就是剩下来的
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int sum = accumulate(stones.begin(), stones.end(), 0), target = sum / 2;
        int dp[target + 1];
        memset(dp, 0, sizeof(dp));
        for (auto i : stones) {
            for (int j = target; j >= i; j--) {
                dp[j] = max(dp[j], dp[j - i] + i);
            }
        }
        return sum - 2 * dp[target];
    }
};
// 完全背包
/*
给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。
如果没有任何一种硬币组合能组成总金额，返回 -1。
你可以认为每种硬币的数量是无限的。
322
 */
// 用amount限量的背包去装不同面额的硬币，无限量，恰好装满
// 超时
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<vector<int>> dp(n + 1, vector<int>(amount + 1, amount + 1));
        dp[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= amount; j++) {
                for (int k = 0; k * coins[i - 1] <= j; k++) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - k * coins[i - 1]] + k);
                }
            }
        }
        return dp[n][amount] == amount + 1 ? -1 : dp[n][amount];
    }
};
// 二维
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<vector<int>> dp(n + 1, vector<int>(amount + 1, amount + 1));
        dp[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= amount; j++) {
                // 可以选择第i-1个硬币，此时最小值为不选择这个，或者选择这个加上选择这个之前的最小值。这个最小值前面已经更新了！
                if (j >= coins[i - 1]) {
                    dp[i][j] = min(dp[i - 1][j], dp[i][j - coins[i - 1]] + 1);
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[n][amount] == amount + 1 ? -1 : dp[n][amount];
    }
};
// 一维
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= amount; j++) {
                if (j >= coins[i - 1]) {
                    dp[j] = min(dp[j], dp[j - coins[i - 1]] + 1);
                }
            }
        }
        return dp[amount] == amount + 1 ? -1 : dp[amount];
    }
};
/*
给你一个整数 n ，返回 和为 n 的完全平方数的最少数量 。

完全平方数 是一个整数，其值等于另一个整数的平方；换句话说，其值等于一个整数自乘的积。例如，1、4、9 和 16 都是完全平方数，而 3 和 11 不是。
279
恰好装满，其他条件初始化为不满足，即最大
 */
class Solution {
public:
    int numSquares(int n) {
        vector<int> nums;
        for (int i = 0; i <= 100 && i * i <= n; i++) {
            nums.emplace_back(i * i);
        }
        int m = nums.size();
        int dp[m + 1][n + 1];
        memset(dp, 10000, sizeof(dp));
        dp[0][0] = 0;
        for (int i = 1; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                if (j >= nums[i - 1]) {
                    dp[i][j] = min(dp[i - 1][j], dp[i][j - nums[i - 1]] + 1);
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[m][n];
    }
};
// 一维
class Solution {
public:
    int numSquares(int n) {
        vector<int> nums;
        for (int i = 0; i <= 100 && i * i <= n; i++) {
            nums.emplace_back(i * i);
        }
        int m = nums.size();
        int dp[n + 1];
        memset(dp, 10000, sizeof(dp));
        dp[0] = 0;
        for (int i : nums) {
            for (int j = i; j <= n; j++) {
                dp[j] = min(dp[j], dp[j - i] + 1);
            }
        }
        return dp[n];
    }
};
/*
给你一个整数数组 coins 表示不同面额的硬币，另给一个整数 amount 表示总金额。

请你计算并返回可以凑成总金额的硬币组合数。如果任何硬币组合都无法凑出总金额，返回 0 。

假设每一种面额的硬币有无限个。

题目数据保证结果符合 32 位带符号整数。
518
 */
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        vector<int> dp(amount + 1, 0);
        dp[0] = 1;
        for (int i : coins) {
            for (int j = i; j <= amount; j++) {
                dp[j] += dp[j - i];
            }
        }
        return dp[amount];
    }
};
/*
给你一个由 不同 整数组成的数组 nums ，和一个目标整数 target 。请你从 nums 中找出并返回总和为 target 的元素组合的个数。

题目数据保证答案符合 32 位整数范围。
377
 */
// 本题参考70爬楼梯，而非背包
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<int> dp(target + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= target; i++) {
            for (int j : nums) {
                if (j <= i && INT_MAX - dp[i - j] >= dp[i])
                    dp[i] += dp[i - j];
            }
        }
        return dp[target];
    }
};
/*
假设你正在爬楼梯。需要 n 阶你才能到达楼顶。

每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
70
 */
class Solution {
public:
    int climbStairs(int n) {
        vector<int> nums({1, 2}), dp(n + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j : nums) {
                if (j <= i)
                    dp[i] += dp[i - j];
            }
        }
        return dp[n];
    }
};
/*
给你一个字符串 s 和一个字符串列表 wordDict 作为字典。请你判断是否可以利用字典中出现的单词拼接出 s 。

注意：不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。
139
//把字符串作为背包容量，从头开始匹配
讲顺序的，模板参考走楼梯
 */
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int t = s.size();
        vector<int> dp(t + 1, false);
        dp[0] = true;
        for (int i = 1; i <= t; i++) {
            for (auto str : wordDict) {
                int len = str.size();
                if (i >= len) {
                    if (s.substr(i - len, len) == str) {
                        dp[i] |= dp[i - len];
                    }
                }
            }
        }
        return dp[t];
    }
};
/*
这里有 n 个一样的骰子，每个骰子上都有 k 个面，分别标号为 1 到 k 。

给定三个整数 n ,  k 和 target ，返回可能的方式(从总共 kn 种方式中)滚动骰子的数量，使正面朝上的数字之和等于 target 。

答案可能很大，你需要对 109 + 7 取模 。
1155
//分组背包
 */
class Solution {
public:
    int numRollsToTarget(int n, int k, int target) {
        vector<int> dp(target + 1, 0);
        dp[0] = 1;
    }
};
/*
给你一个整数数组 cost 和一个整数 target 。请你返回满足如下规则可以得到的 最大 整数：

    给当前结果添加一个数位（i + 1）的成本为 cost[i] （cost 数组下标从 0 开始）。
    总成本必须恰好等于 target 。
    添加的数位中没有数字 0 。

由于答案可能会很大，请你以字符串形式返回。

如果按照上述要求无法得到任何整数，请你返回 "0" 。
1449
 */
class Solution {
public:
    string largestNumber(vector<int>& cost, int target) {
    }
};
/*
集团里有 n 名员工，他们可以完成各种各样的工作创造利润。

第 i 种工作会产生 profit[i] 的利润，它要求 group[i] 名成员共同参与。如果成员参与了其中一项工作，就不能参与另一项工作。

工作的任何至少产生 minProfit 利润的子集称为盈利计划。并且工作的成员总数最多为 n 。

有多少种计划可以选择？因为答案很大，所以 返回结果模 10^9 + 7 的值。
879
 */
class Solution {
public:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
    }
};