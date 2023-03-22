#include "head.h"
/*
给你两个字符串 a 和 b ，它们长度相同。请你选择一个下标，将两个字符串都在 相同的下标 分割开。
由 a 可以得到两个字符串： aprefix 和 asuffix ，满足 a = aprefix + asuffix ，同理，由 b 可以得到两个字符串 bprefix 和 bsuffix ，满足 b = bprefix + bsuffix 。
请你判断 aprefix + bsuffix 或者 bprefix + asuffix 能否构成回文串。

当你将一个字符串 s 分割成 sprefix 和 ssuffix 时， ssuffix 或者 sprefix 可以为空。比方说， s = "abc" 那么 "" + "abc" ， "a" + "bc" ， "ab" + "c" 和 "abc" + "" 都是合法分割。

如果 能构成回文字符串 ，那么请返回 true，否则返回 false 。

注意， x + y 表示连接字符串 x 和 y 。
T1616
思路：
双指针从两端开始遍历
 */
class Solution {
public:
    bool checkPalindromeFormation(string a, string b) {
        int n = a.size(), i = 0, j = n - 1;
        bool aa = false, bb = false, f1 = true, f2 = true;
        while (i < j) {
            if (f1) {
                if (aa == false) {
                    if (a[i] != b[j] && a[i] == a[j]) {
                        aa = true;
                    }
                    if (a[i] != b[j] && a[i] != a[j]) {
                        f1 = false;
                    }
                }
                if (aa == true && a[i] != a[j]) {
                    f1 = false;
                }
            }
            if (f2) {
                if (bb == false) {
                    if (b[i] != a[j] && b[i] == b[j]) {
                        bb = true;
                    }
                    if (b[i] != a[j] && b[i] != b[j]) {
                        f2 = false;
                    }
                }
                if (bb == true && b[i] != b[j]) {
                    f2 = false;
                }
            }
            if (!f1 && !f2) {
                return false;
            }
            i++;
            j--;
        }
        return true;
    }
};
/*
给定正整数 n，返回在 [1, n] 范围内具有 至少 1 位 重复数字的正整数的个数。
T1012
20230320
// 数位DP，学一下
 */
// 超时
class Solution {
public:
    int numDupDigitsAtMostN(int n) {
        int res = 0;
        for (int i = 1; i <= n; i++) {
            string str = to_string(i);
            if (set<char>(str.begin(), str.end()).size() != str.size()) {
                res++;
            }
        }
        return res;
    }
};
class Solution {
public:
    int numDupDigitsAtMostN(int n) {
        string num = to_string(n);
        int len = num.size(), dp[len + 1][1 << 10];
        memset(dp, -1, sizeof(dp));
        function<int(int, int, int, int)> f = [&](int pos, int mask, bool limit, bool isnum) -> int {
            if (pos >= len) {
                return isnum;
            }
            if (!limit && isnum && dp[pos][mask] != -1) {
                return dp[pos][mask];
            }
            int up = limit ? (num[pos] - '0') : 9;
            int res = 0;
            // 如果都是前导0，则跳过
            if (!isnum) {
                res = f(pos + 1, mask, false, false);
            }
            for (int i = !isnum; i <= up; i++) {
                if (((mask >> i) & 1) == 0) {
                    res += f(pos + 1, mask | (1 << i), limit && i == num[pos] - '0', true);
                }
            }
            if (!limit && isnum) {
                dp[pos][mask] = res;
            }
            return res;
        };
        return n - f(0, 0, true, false);
    }
};
/*
给你一个四舍五入到两位小数的非负浮点数 celsius 来表示温度，以 摄氏度（Celsius）为单位。

你需要将摄氏度转换为 开氏度（Kelvin）和 华氏度（Fahrenheit），并以数组 ans = [kelvin, fahrenheit] 的形式返回结果。

返回数组 ans 。与实际答案误差不超过 10-5 的会视为正确答案。
T2469
纯粹模拟，没什么好说的，垃圾！
 */
class Solution {
public:
    vector<double> convertTemperature(double celsius) {
        return {celsius + 273.15, celsius * 1.8 + 32};
    }
};
/*
假设你是球队的经理。对于即将到来的锦标赛，你想组合一支总体得分最高的球队。球队的得分是球队中所有球员的分数 总和 。

然而，球队中的矛盾会限制球员的发挥，所以必须选出一支 没有矛盾 的球队。如果一名年龄较小球员的分数 严格大于 一名年龄较大的球员，则存在矛盾。同龄球员之间不会发生矛盾。

给你两个列表 scores 和 ages，其中每组 scores[i] 和 ages[i] 表示第 i 名球员的分数和年龄。请你返回 所有可能的无矛盾球队中得分最高那支的分数 。
T1626
 */
class Solution {
public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int n = scores.size(), res = 0;
        vector<int> index(n);
        iota(index.begin(), index.end(), 0);
        sort(index.begin(), index.end(), [&](int i, int j) { return ages[i] < ages[j] || ages[i] == ages[j] && scores[i] <= scores[j]; });
        vector<int> dp(n, 0);
        for (int i = 0; i < n; i++) {
            for (int j = i; j >= 0; j--) {
                if (scores[index[i]] >= scores[index[j]] || ages[index[i]] == ages[index[j]]) {
                    dp[index[i]] = max(dp[index[i]], dp[index[j]] + scores[index[i]]);
                }
            }
            res = max(res, dp[index[i]]);
        }
        return res;
    }
};