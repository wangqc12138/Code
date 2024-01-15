#include "../../head.h"
/*
给你三个字符串 s1、s2 和 s3。 你可以根据需要对这三个字符串执行以下操作 任意次数 。

在每次操作中，你可以选择其中一个长度至少为 2 的字符串 并删除其 最右位置上 的字符。

如果存在某种方法能够使这三个字符串相等，请返回使它们相等所需的 最小 操作次数；否则，返回 -1。
 */
class Solution {
public:
    int findMinimumOperations(string s1, string s2, string s3) {
        int len1 = s1.size(), len2 = s2.size(), len3 = s3.size(), len = 0;
        for (int i = 0; i < min({len1, len2, len3}); i++) {
            if (s1[i] == s2[i] && s1[i] == s3[i]) {
                len += 3;
            } else {
                break;
            }
        }
        return len == 0 ? -1 : len1 + len2 + len3 - len;
    }
};
/*
桌子上有 n 个球，每个球的颜色不是黑色，就是白色。

给你一个长度为 n 、下标从 0 开始的二进制字符串 s，其中 1 和 0 分别代表黑色和白色的球。

在每一步中，你可以选择两个相邻的球并交换它们。

返回「将所有黑色球都移到右侧，所有白色球都移到左侧所需的 最小步数」。
 */
class Solution {
public:
    long long minimumSteps(string s) {
        int sum = 0;
        for (auto i : s) {
            sum += i - '0';
        }
        long long res = 0;
        for (int i = 0; i < s.size() && sum; i++) {
            if (s[i] == '1') {
                res += s.size() - sum - i;
                sum--;
            }
        }
        return res;
    }
};
/*
给你三个整数 a ，b 和 n ，请你返回 (a XOR x) * (b XOR x) 的 最大值 且 x 需要满足 0 <= x < 2n。

由于答案可能会很大，返回它对 109 + 7 取余 后的结果。

注意，XOR 是按位异或操作。
 */
class Solution {
public:
    int maximumXorProduct(long long a, long long b, int n) {
        if (a == b && a == 0) {
            return n * n % 1000000007;
        }
        auto help = [=](long long x) {
            string str;
            int k = 0;
            while (x) {
                str += (x & 1) + '0';
                x = x >> 1;
                k++;
            }
            while (k < 3) {
                k++;
                str += '0';
            }
            reverse(str.begin(), str.end());
            cout << str << endl;
        };
        help(a);
        help(b);
        long long at = 0, bt = 0;
        int k = 0;
        vector<int> diff;
        while (a || b) {
            int ai = a & 1, bi = b & 1;
            if (ai == bi) {
                if (k > n) {
                    at += 1 << a;
                    bt += 1 << b;
                } else {
                    at += 1 << k;
                    bt += 1 << k;
                }

            } else {
                if (k > n) {
                    at += 1 << a;
                    bt += 1 << b;
                } else {
                    diff.emplace_back(k);
                }
            }
            a = a >> 1, b = b >> 1;
            k++;
        }
        int res = 0;
        long long c = min(at, bt), d = max(at, bt);
        help(c);
        help(d);
        if (n > k) {
            for (int i = n - 1; i >= k; i--) {
                d += (long long)1 << i;
                c += (long long)1 << i;
            }
        }
        if (diff.size()) {
            c += 1 << diff.back();
            diff.pop_back();
            for (auto i : diff) {
                d += 1 << i;
            }
        }

        help(c);
        help(d);
        c = c % 1000000007;
        d = d % 1000000007;
        res = c * d % 1000000007;
        return res;
    }
};