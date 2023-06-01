#include "head.h"
/*
给你一个整数 num ，返回 num 中能整除 num 的数位的数目。

如果满足 nums % val == 0 ，则认为整数 val 可以整除 nums 。
 */
class Solution
{
public:
    int countDigits(int num)
    {
        vector<int> dig(10, 0);
        for (auto c : to_string(num))
        {
            dig[c - '0']++;
        }
        int res = 0;
        for (int i = 1; i <= 9; i++)
        {
            if (num % i == 0)
            {
                res += dig[i];
            }
        }
        return res;
    }
};
/*
给你一个正整数数组 nums ，对 nums 所有元素求积之后，找出并返回乘积中 不同质因数 的数目。

注意：

    质数 是指大于 1 且仅能被 1 及自身整除的数字。
    如果 val2 / val1 是一个整数，则整数 val1 是另一个整数 val2 的一个因数。

 */
class Solution
{
public:
    int distinctPrimeFactors(vector<int> &nums)
    {
        set<int> st(nums.begin(), nums.end());
        int maxn = *max_element(nums.begin(), nums.end());
        vector<int> temp(maxn + 1, 1);
        int res = 0;
        for (int i = 2; i <= maxn; i++)
        {
            if (temp[i] == 0)
            {
                continue;
            }
            int t = 0;
            for (int j = 1; j * i <= maxn; j++)
            {
                temp[j * i] = 0;
                if (st.count(j * i) && !t)
                {
                    t = 1;
                }
            }
            res += t;
        }
        return res;
    }
};
/*
给你一个字符串 s ，它每一位都是 1 到 9 之间的数字组成，同时给你一个整数 k 。

如果一个字符串 s 的分割满足以下条件，我们称它是一个 好 分割：

    s 中每个数位 恰好 属于一个子字符串。
    每个子字符串的值都小于等于 k 。

请你返回 s 所有的 好 分割中，子字符串的 最少 数目。如果不存在 s 的 好 分割，返回 -1 。

注意：

    一个字符串的 值 是这个字符串对应的整数。比方说，"123" 的值为 123 ，"1" 的值是 1 。
    子字符串 是字符串中一段连续的字符序列。

 */
class Solution
{
public:
    int minimumPartition(string s, int k)
    {
        auto tp = *max_element(s.begin(), s.end());
        if (tp - '0' > k)
        {
            return -1;
        }
        if (k < 10)
        {
            return s.size();
        }
        int res = 1;
        string t;
        for (int i = 0; i < s.size(); i++)
        {
            t += s[i];
            long long temp = stoll(t);
            if (temp > k)
            {
                res++;
                t = "" + s[i];
            }
        }
        return res;
    }
};
/*
给你两个正整数 left 和 right ，请你找到两个整数 num1 和 num2 ，它们满足：

    left <= nums1 < nums2 <= right  。
    nums1 和 nums2 都是 质数 。
    nums2 - nums1 是满足上述条件的质数对中的 最小值 。

请你返回正整数数组 ans = [nums1, nums2] 。如果有多个整数对满足上述条件，请你返回 nums1 最小的质数对。如果不存在符合题意的质数对，请你返回 [-1, -1] 。

如果一个整数大于 1 ，且只能被 1 和它自己整除，那么它是一个质数。
 */
class Solution
{
public:
    vector<int> closestPrimes(int left, int right)
    {
        vector<int> dig(right + 1, 1), prim;
        for (int i = 2; i <= right; i++)
        {
            if (dig[i] == 0)
            {
                continue;
            }
            if (i >= left)
            {
                prim.emplace_back(i);
            }
            for (int j = 2; i * j <= right; j++)
            {
                dig[j * i] = 0;
            }
        }
        int minn = INT_MAX;
        vector<int> res = {-1, -1};
        for (int i = 1; i < prim.size(); i++)
        {
            if (prim[i] - prim[i - 1] < minn)
            {
                res[0] = prim[i - 1];
                res[1] = prim[i];
                minn = prim[i] - prim[i - 1];
            }
        }
        return res;
    }
};