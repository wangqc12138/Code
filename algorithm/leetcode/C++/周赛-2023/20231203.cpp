#include "head.h"
class Solution {
public:
    vector<int> findPeaks(vector<int>& mountain) {
        int n = mountain.size();
        vector<int> res;
        for (int i = 1; i < n - 1; i++) {
            if (mountain[i] > mountain[i - 1] && mountain[i] > mountain[i + 1]) {
                res.emplace_back(i);
            }
        }
        return res;
    }
};
/*
给你一个下标从 0 开始的整数数组 coins，表示可用的硬币的面值，以及一个整数 target 。

如果存在某个 coins 的子序列总和为 x，那么整数 x 就是一个 可取得的金额 。

返回需要添加到数组中的 任意面值 硬币的 最小数量 ，使范围 [1, target] 内的每个整数都属于 可取得的金额 。

数组的 子序列 是通过删除原始数组的一些（可能不删除）元素而形成的新的 非空 数组，删除过程不会改变剩余元素的相对位置。
 */
class Solution {
public:
    int minimumAddedCoins(vector<int>& coins, int target) {
        sort(coins.begin(), coins.end());
        int res = 0, i = 0, n = 1;
        while (n <= target) {
            if (i < coins.size() && coins[i] <= n) {
                n += coins[i++];
            } else {
                n *= 2;
                res++;
            }
        }
        return res;
    }
};
/*
给你一个长度为 n 的整数数组 coins ，它代表你拥有的 n 个硬币。第 i 个硬币的值为 coins[i] 。如果你从这些硬币中选出一部分硬币，它们的和为 x ，那么称，你可以 构造 出 x 。

请返回从 0 开始（包括 0 ），你最多能 构造 出多少个连续整数。

你可能有多个相同值的硬币。
 */
class Solution {
public:
    int getMaximumConsecutive(vector<int>& coins) {
        sort(coins.begin(), coins.end());
        int i = 0, n = accumulate(coins.begin(), coins.end(), 0), s = 1;
        while (s <= n) {
            if (i < coins.size() && coins[i] <= s) {
                s += coins[i++];
            } else {
                break;
            }
        }
        return s;
    }
};
/*
给你一个字符串 word 和一个整数 k 。

如果 word 的一个子字符串 s 满足以下条件，我们称它是 完全字符串：

    s 中每个字符 恰好 出现 k 次。
    相邻字符在字母表中的顺序 至多 相差 2 。也就是说，s 中两个相邻字符 c1 和 c2 ，它们在字母表中的位置相差 至多 为 2 。

请你返回 word 中 完全 子字符串的数目。

子字符串 指的是一个字符串中一段连续 非空 的字符序列。
 */
class Solution {
public:
    int countCompleteSubstrings(string word, int k) {
        vector<string> vstr;
        string s = "";
        s += word[0];
        for (int i = 1; i < word.size(); i++) {
            if (abs(word[i] - word[i - 1]) <= 2) {
                s += word[i];
            } else {
                vstr.emplace_back(s);
                s = "";
                s += word[i];
            }
        }
        vstr.emplace_back(s);
        for (auto s : vstr) {
            cout << s << endl;
        }
        int res = 0;
        auto func = [&](int x) {
            int len = k * x;
            for (auto s : vstr) {
                if (s.size() <= len) {
                    res += s.size() == len;
                    continue;
                }
                map<int, int> mp;
                for (int i = 0; i < s.size(); i++) {
                    mp[s[i]]++;
                    if (i >= len) {
                        if (--mp[s[i - len]] == 0) {
                            mp.erase(s[i - len]);
                        }
                        if (mp.size() == x) {
                            cout << s.substr(i - len, len) << endl;
                            res++;
                        }
                    }
                }
            }
        };
        for (int i = 1; i <= 26; i++) {
            func(i);
        }
        return res;
    }
};