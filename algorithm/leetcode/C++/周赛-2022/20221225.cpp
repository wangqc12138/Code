#include "head.h"
/*
给你一个下标从 0 开始的 环形 字符串数组 words 和一个字符串 target 。环形数组 意味着数组首尾相连。

    形式上， words[i] 的下一个元素是 words[(i + 1) % n] ，而 words[i] 的前一个元素是 words[(i - 1 + n) % n] ，其中 n 是 words 的长度。

从 startIndex 开始，你一次可以用 1 步移动到下一个或者前一个单词。

返回到达目标字符串 target 所需的最短距离。如果 words 中不存在字符串 target ，返回 -1 。
 */
class Solution
{
public:
    int closetTarget(vector<string> &words, string target, int startIndex)
    {
        int n = words.size(), res = n;
        for (int i = 0; i < n; i++)
        {
            if (words[i] == target)
            {
                res = min(res, min(abs(startIndex - i), abs(n - startIndex + i)));
            }
        }
        return res;
    }
};
/*
给你一个由字符 'a'、'b'、'c' 组成的字符串 s 和一个非负整数 k 。每分钟，你可以选择取走 s 最左侧 还是 最右侧 的那个字符。

你必须取走每种字符 至少 k 个，返回需要的 最少 分钟数；如果无法取到，则返回 -1 。
 */
class Solution
{
public:
    int takeCharacters(string s, int k)
    {
        vector<int> need(3, -k);
        for (auto i : s)
        {
            need[i - 'a']++;
        }
        for (auto i : need)
        {
            if (i < 0)
            {
                return -1;
            }
        }
        int n = s.size(), left = 0, right = 0, res = n;
        vector<int> wind(3, 0);
        auto check = [&]()
        {for(int i=0;i<3;i++){if(need[i]<wind[i])return false;}return true; };
        while (right < n)
        {
            while (right < n)
            {
                wind[s[right++] - 'a']++;
                if (!check())
                {
                    break;
                }
                else
                {
                    res = min(res, n - (right - left));
                }
            }
            while (left < right)
            {
                wind[s[left++] - 'a']--;
                if (check())
                {
                    break;
                }
            }
        }
        return res;
    }
};
/*
几张卡牌 排成一行，每张卡牌都有一个对应的点数。点数由整数数组 cardPoints 给出。

每次行动，你可以从行的开头或者末尾拿一张卡牌，最终你必须正好拿 k 张卡牌。

你的点数就是你拿到手中的所有卡牌的点数之和。

给你一个整数数组 cardPoints 和整数 k，请你返回可以获得的最大点数。
1423
 */
class Solution
{
public:
    int maxScore(vector<int> &cardPoints, int k)
    {
        int n = cardPoints.size(), sum = 0, minn;
        for (int i = 0; i < n - k; i++)
        {
            sum += cardPoints[i];
        }
        minn = sum;
        for (int i = n - k; i < n; i++)
        {
            sum += cardPoints[i] - cardPoints[i - n + k];
            minn = min(minn, sum);
        }
        return accumulate(cardPoints.begin(), cardPoints.end(), 0) - minn;
    }
};
/*
给你一个正整数数组 price ，其中 price[i] 表示第 i 类糖果的价格，另给你一个正整数 k 。

商店组合 k 类 不同 糖果打包成礼盒出售。礼盒的 甜蜜度 是礼盒中任意两种糖果 价格 绝对差的最小值。

返回礼盒的 最大 甜蜜度。
 */
class Solution
{
public:
    int maximumTastiness(vector<int> &price, int k)
    {
        sort(price.begin(), price.end());
        int left = 0, right = price.back() - price[0];
        while (left < right)
        {
            int mid = (left + right) / 2;
            int pre = price[0], t = 1;
            for (int i : price)
            {
                if (i - pre >= mid)
                {
                    pre = i;
                    t++;
                }
            }
            if (t < k)
            {
                right = mid - 1;
            }
            else
            {
                left = mid;
            }
        }
        return left;
    }
};
/*
在代号为 C-137 的地球上，Rick 发现如果他将两个球放在他新发明的篮子里，它们之间会形成特殊形式的磁力。
Rick 有 n 个空的篮子，第 i 个篮子的位置在 position[i] ，Morty 想把 m 个球放到这些篮子里，使得任意两球间 最小磁力 最大。

已知两个球如果分别位于 x 和 y ，那么它们之间的磁力为 |x - y| 。

给你一个整数数组 position 和一个整数 m ，请你返回最大化的最小磁力。
1552
 */
class Solution
{
public:
    int maxDistance(vector<int> &position, int m)
    {
        sort(position.begin(), position.end());
        int left = 0, right = position.back() - position[0];
        while (left < right)
        {
            int mid = (left + right + 1) / 2;
            int t = 1, pre = position[0];
            for (int i : position)
            {
                if (i - pre >= mid)
                {
                    t++;
                    pre = i;
                }
            }
            if (t < m)
            {
                right = mid - 1;
            }
            else
            {
                left = mid;
            }
        }
        return left;
    }
};