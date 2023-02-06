#include "head.h"
/*
给你一个整数数组 gifts ，表示各堆礼物的数量。每一秒，你需要执行以下操作：

    选择礼物数量最多的那一堆。
    如果不止一堆都符合礼物数量最多，从中选择任一堆即可。
    选中的那一堆留下平方根数量的礼物（向下取整），取走其他的礼物。

返回在 k 秒后剩下的礼物数量。
 */
class Solution
{
public:
    long long pickGifts(vector<int> &gifts, int k)
    {
        long long res = 0;
        priority_queue<int> mpq;
        for (int i : gifts)
        {
            res += i;
            mpq.emplace(i);
        }
        while (!mpq.empty() && k--)
        {
            auto t = mpq.top();
            mpq.pop();
            res -= t - sqrt(t);
            mpq.emplace(sqrt(t));
        }
        return res;
    }
};
/*
给你一个下标从 0 开始的字符串数组 words 以及一个二维整数数组 queries 。

每个查询 queries[i] = [li, ri] 会要求我们统计在 words 中下标在 li 到 ri 范围内（包含 这两个值）并且以元音开头和结尾的字符串的数目。

返回一个整数数组，其中数组的第 i 个元素对应第 i 个查询的答案。

注意：元音字母是 'a'、'e'、'i'、'o' 和 'u' 。
 */
class Solution
{
public:
    vector<int> vowelStrings(vector<string> &words, vector<vector<int>> &queries)
    {
        int n = words.size();
        vector<int> pre(n, 0);
        set<char> st = {'a', 'e', 'i', 'o', 'u'};
        for (int i = 0; i < n; i++)
        {
            pre[i] = (i == 0 ? 0 : pre[i - 1]) + (st.count(words[i][0]) && st.count(words[i].back()));
        }
        vector<int> res;
        for (auto vec : queries)
        {
            res.emplace_back(pre[vec[1]] - vec[0] == 0 ? 0 : pre[vec[0] - 1]);
        }
        return res;
    }
};
/*
沿街有一排连续的房屋。每间房屋内都藏有一定的现金。现在有一位小偷计划从这些房屋中窃取现金。

由于相邻的房屋装有相互连通的防盗系统，所以小偷 不会窃取相邻的房屋 。

小偷的 窃取能力 定义为他在窃取过程中能从单间房屋中窃取的 最大金额 。

给你一个整数数组 nums 表示每间房屋存放的现金金额。形式上，从左起第 i 间房屋中放有 nums[i] 美元。

另给你一个整数数组 k ，表示窃贼将会窃取的 最少 房屋数。小偷总能窃取至少 k 间房屋。

返回小偷的 最小 窃取能力。
 */
class Solution
{
public:
    int minCapability(vector<int> &nums, int k)
    {
        int l = 0, r = *max_element(nums.begin(), nums.end());
        auto check = [&](int mid)
        {
            int pre = -2, t = 0;
            for (int i = 0; i < nums.size(); i++)
            {
                if (nums[i] <= mid && i - pre > 1)
                {
                    t++;
                    pre = i;
                }
            }
            return t >= k;
        };
        while (l < r)
        {
            int mid = (l + r) / 2;
            if (!check(mid))
            {
                l = mid + 1;
            }
            else
            {
                r = mid;
            }
        }
        return l;
    }
};