#include "head.h"
/*
记忆化是每个状态，就是每个pos+会影响后续计数的因素
T1是不重复，所以记录前面选择了哪些数字
T2是不连续的1，所以记录上一个数字是否是1
T3是1的个数，则是前面已经有的1的个数，这个到底还要返回来的，比如11 789和10 789是不一样的
 */
/*
给定正整数 n，返回在 [1, n] 范围内具有 至少 1 位 重复数字的正整数的个数。
T1012
查找没重复的正整数，然后减去
用记忆化搜索去找，比如7000-7999，8000-8999，那么这000-999是可以记忆化的
 */
class Solution {
public:
    int numDupDigitsAtMostN(int n) {
        string num = to_string(n);
        int dp[num.size()][1 << 10];
        memset(dp, -1, sizeof(dp));
        function<int(int, int, bool, bool)> f = [&](int pos, int mask, bool limit, bool isnum) -> int {
            if (pos >= num.size()) {
                return isnum;
            }
            // 如果这是一个数字，并且没有被限制，
            if (isnum && !limit && dp[pos][mask] != -1) {
                return dp[pos][mask];
            }
            int res = 0;
            if (!isnum) {
                res = f(pos + 1, mask, false, isnum);
            }
            int up = limit ? num[pos] - '0' : 9;
            for (int i = 1 - isnum; i <= up; i++) {
                if ((mask & (1 << i)) == 0) {
                    res += f(pos + 1, mask | (1 << i), limit && i == up, true);
                }
            }
            if (isnum && !limit) {
                dp[pos][mask] = res;
            }
            return res;
        };
        return n - f(0, 0, true, false);
    }
};
/*
不含连续1的非负整数
给定一个正整数 n ，请你统计在 [0, n] 范围的非负整数中，有多少个整数的二进制表示中不存在 连续的 1 。
T600
思路：
10 10101010
00 10101010
以上两种可以记忆化
 */
class Solution {
public:
    int findIntegers(int n) {
        string s = bitset<32>(n).to_string();
        int dp[s.size()][2];
        memset(dp, -1, sizeof(dp));
        function<int(int, int, bool)> f = [&](int pos, int mask, bool limit) -> int {
            if (pos >= s.size()) {
                return 1;
            }
            if (!limit && dp[pos][mask] != -1) {
                return dp[pos][mask];
            }
            int res = 0;
            int up = limit ? s[pos] - '0' : 1;
            for (int i = 0; i <= up; i++) {
                if (!mask || i != 1) {
                    res += f(pos + 1, i == 1, limit && i == up);
                }
            }
            if (!limit) {
                dp[pos][mask] = res;
            }
            return res;
        };
        return f(0, 0, true);
    }
};
/*
给定一个整数 n，计算所有小于等于 n 的非负整数中数字 1 出现的个数。
T233

 */
class Solution {
public:
    int countDigitOne(int n) {
        string s = to_string(n);
        int m = s.size();
        vector<vector<int>> dp(m, vector<int>(m, -1));
        function<int(int, bool, int)> f = [&](int pos, bool limit, int k) -> int {
            if (pos == m) {
                return k;
            }
            if (!limit && dp[pos][k] != -1) {
                return dp[pos][k];
            }
            int res = 0;
            int up = limit ? s[pos] - '0' : 9;
            for (int i = 0; i <= up; i++) {
                res += f(pos + 1, limit && i == up, k + (i == 1));
            }
            if (!limit) {
                dp[pos][k] = res;
            }
            return res;
        };
        return f(0, true, 0);
    }
};
/*
编写一个方法，计算从 0 到 n (含 n) 中数字 2 出现的次数。
面试题 17.06. 2出现的次数
雷同上题
 */
class Solution {
public:
    int numberOf2sInRange(int n) {
        string s = to_string(n);
        int m = s.size();
        vector<vector<int>> dp(m, vector<int>(m, -1));
        function<int(int, int, bool)> f = [&](int pos, int cnt, bool limit) -> int {
            if (pos >= m) {
                return cnt;
            }
            if (!limit && dp[pos][cnt] != -1) {
                return dp[pos][cnt];
            }
            int res = 0;
            int up = limit ? s[pos] - '0' : 9;
            for (int i = 0; i <= up; i++) {
                res += f(pos + 1, cnt + (i == 2), limit && i == up);
            }
            if (!limit) {
                dp[pos][cnt] = res;
            }
            return res;
        };
        return f(0, 0, true);
    }
};
/*
给定一个按 非递减顺序 排列的数字数组 digits 。你可以用任意次数 digits[i] 来写的数字。
例如，如果 digits = ['1','3','5']，我们可以写数字，如 '13', '551', 和 '1351315'。

返回 可以生成的小于或等于给定整数 n 的正整数的个数 。
T902
 */
class Solution {
public:
    int atMostNGivenDigitSet(vector<string>& digits, int n) {
        string s = to_string(n);
        int m = s.size();
        vector<int> dp(m, -1);
        function<int(int, bool, bool)> f = [&](int pos, bool limit, bool isnum) -> int {
            if (pos >= m) {
                return 1;
            }
            if (!limit && isnum && dp[pos] != -1) {
                return dp[pos];
            }
            int up = limit ? s[pos] - '0' : 9;
            int res = 0;
            if (!isnum) {
                res = f(pos + 1, false, isnum);
            }
            for (auto c : digits) {
                int t = stoi(c);
                if (t > up) {
                    break;
                }
                res += f(pos + 1, limit && t == up, true);
            }
            if (!limit && isnum) {
                dp[pos] = res;
            }
            return res;
        };
        return f(0, true, false);
    }
};
/*
我们称一个数 X 为好数, 如果它的每位数字逐个地被旋转 180 度后，我们仍可以得到一个有效的，且和 X 不同的数。要求每位数字都要被旋转。

如果一个数的每位数字被旋转以后仍然还是一个数字， 则这个数是有效的。
0, 1, 和 8 被旋转后仍然是它们自己；2 和 5 可以互相旋转成对方（在这种情况下，它们以不同的方向旋转，换句话说，2 和 5 互为镜像）；6 和 9 同理，
除了这些以外其他的数字旋转以后都不再是有效的数字。

现在我们有一个正整数 N, 计算从 1 到 N 中有多少个数 X 是好数？
T788
 */
class Solution {
public:
    int rotatedDigits(int n) {
        vector<int> nums = {0, 1, 2, 5, 6, 8, 9};
        string s = to_string(n);
        int m = s.size();
        vector<vector<int>> dp(m, vector<int>(2, -1));
        function<int(int, bool, bool)> f = [&](int pos, bool flag, bool limit) -> int {
            if (pos >= m) {
                return flag;
            }
            if (!limit && dp[pos][flag] != -1) {
                return dp[pos][flag];
            }
            int res = 0;
            int up = limit ? s[pos] - '0' : 9;
            for (auto i : nums) {
                if (i > up) {
                    break;
                }
                res += f(pos + 1, flag || (i != 0 && i != 8 && i != 1), limit && i == up);
            }
            if (!limit) {
                dp[pos][flag] = res;
            }
            return res;
        };
        return f(0, false, true);
    }
};
/*
给定一个在 0 到 9 之间的整数 d，和两个正整数 low 和 high 分别作为上下界。返回 d 在 low 和 high 之间的整数中出现的次数，包括边界 low 和 high。
T1067
 */
class Solution {
public:
    int digitsCount(int d, int low, int high) {
        return help(d, high) - help(d, low - 1);
    }
    int help(int d, int n) {
        string s = to_string(n);
        int m = s.size();
        vector<vector<int>> dp(m, vector<int>(m, -1));
        function<int(int, int, bool, bool)> f = [&](int pos, int cnt, bool limit, bool isnum) -> int {
            if (pos >= m) {
                return cnt;
            }
            if (!limit && isnum && dp[pos][cnt] != -1) {
                return dp[pos][cnt];
            }
            int res = 0;
            if (!isnum) {
                res = f(pos + 1, cnt, false, false);
            }
            int up = limit ? s[pos] - '0' : 9;
            for (int i = 1 - isnum; i <= up; i++) {
                res += f(pos + 1, cnt + (i == d), limit && i == up, true);
            }
            if (!limit && isnum) {
                dp[pos][cnt] = res;
            }
            return res;
        };
        return f(0, 0, true, false);
    }
};
/*
给你两个长度为 n 的字符串 s1 和 s2 ，以及一个字符串 evil 。请你返回 好字符串 的数目。

好字符串 的定义为：它的长度为 n ，字典序大于等于 s1 ，字典序小于等于 s2 ，且不包含 evil 为子字符串。

由于答案可能很大，请你返回答案对 10^9 + 7 取余的结果。
too hard
 */
class Solution {
public:
    int findGoodStrings(int n, string s1, string s2, string evil) {
    }
};