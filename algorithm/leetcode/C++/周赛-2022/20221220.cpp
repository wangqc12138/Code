#include "head.h"
/*
给你一个下标从 0 开始的字符串数组 words 。

如果两个字符串由相同的字符组成，则认为这两个字符串 相似 。

    例如，"abca" 和 "cba" 相似，因为它们都由字符 'a'、'b'、'c' 组成。
    然而，"abacba" 和 "bcfd" 不相似，因为它们不是相同字符组成的。

请你找出满足字符串 words[i] 和 words[j] 相似的下标对 (i, j) ，并返回下标对的数目，其中 0 <= i < j <= word.length - 1 。
 */
class Solution
{
public:
    int similarPairs(vector<string> &words)
    {
        map<vector<int>, int> mp;
        for (auto str : words)
        {
            vector<int> temp(26, 0);
            for (auto c : str)
            {
                temp[c - 'a'] = 1;
            }
            mp[temp]++;
        }
        int res = 0;
        for (auto [x, y] : mp)
        {
            res += (y - 1) * y / 2;
        }
        return res;
    }
};
/*
给你一个正整数 n 。

请你将 n 的值替换为 n 的 质因数 之和，重复这一过程。

    注意，如果 n 能够被某个质因数多次整除，则在求和时，应当包含这个质因数同样次数。

返回 n 可以取到的最小值。
 */
class Solution
{
public:
    int smallestValue(int n)
    {
        vector<int> prim(n + 1, 1), vec;
        for (int i = 2; i <= n; i++)
        {
            if (prim[i] != 1)
            {
                continue;
            }
            vec.emplace_back(i);
            for (int j = 2; j * i <= n; j++)
            {
                prim[i] = 0;
            }
        }
        while (!prim[n])
        {
            int t = n;
            n = 0;
            for (int i = 0; i < vec.size(); i++)
            {
                if (!t % vec[i])
                {
                    t /= vec[i];
                    n += vec[i];
                    i--;
                }
            }
        }
        return n;
    }
};