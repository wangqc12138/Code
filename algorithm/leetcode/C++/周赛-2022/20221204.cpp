#include "head.h"
class Solution
{
public:
    bool isCircularSentence(string sentence)
    {
        if (sentence[0] != sentence.back())
        {
            return false;
        }
        char p;
        bool flag = false;
        for (auto c : sentence)
        {
            if (c == ' ')
            {
                flag = true;
                continue;
            }
            if (flag)
            {
                flag = false;
                if (c != p)
                {
                    return false;
                }
            }
            p = c;
        }
        return true;
    }
};
class Solution
{
public:
    long long dividePlayers(vector<int> &skill)
    {
        int sum = accumulate(skill.begin(), skill.end(), 0);
        int n = skill.size() / 2;
        if (sum % n != 0)
        {
            return -1;
        }
        n = sum / n;
        long long res = 0;
        map<int, int> mp;
        for (int i : skill)
        {
            if (mp[n - i] > 0)
            {
                mp[n - i]--;
                res += (long long)(i * (n - i));
            }
            else
            {
                mp[i]++;
            }
        }
        for (auto [x, y] : mp)
        {
            if (y > 0)
            {
                return -1;
            }
        }
        return res;
    }
};
// 并查集--sb
// 只要找到1联通最小值就行了！！！
class UnionFindSet
{
public:
    UnionFindSet(int n)
    {
        for (int i = 1; i <= n; i++)
        {
            head[i] = i;
            size[i] = 1;
        }
    }
    void makeSet(vector<vector<int>> &roads)
    {
        for (auto vec : roads)
        {
            if (minn.count(vec[0]))
            {
                minn[vec[0]] = min(minn[vec[0]], vec[2]);
            }
            else
            {
                minn[vec[0]] = vec[2];
            }
            if (minn.count(vec[1]))
            {
                minn[vec[1]] = min(minn[vec[1]], vec[2]);
            }
            else
            {
                minn[vec[1]] = vec[2];
            }
        }
    }
    int findFather(int i)
    {
        if (head[i] != i)
        {
            head[i] = findFather(head[i]);
        }
        return head[i];
    }
    bool isSameSet(int i, int j)
    {
        return findFather(i) == findFather(j);
    }
    void unionSet(int i, int j)
    {
        int headi = findFather(i);
        int headj = findFather(j);
        while (headi != headj)
        {
            int sizei = size[headi];
            int sizej = size[headj];
            int mini = minn[headi];
            int minj = minn[headj];
            if (sizei >= sizej)
            {
                head[headj] = headi;
                size[headi] += sizej;
                minn[headi] = min(mini, minj);
            }
            else
            {
                head[headi] = headj;
                size[headj] += sizei;
                minn[headj] = min(mini, minj);
            }
        }
    }
    int getMin(int i)
    {
        int headi = findFather(i);
        return minn[headi];
    }

private:
    map<int, int> head, size, minn;
};
class Solution
{
public:
    int minScore(int n, vector<vector<int>> &roads)
    {
        UnionFindSet ufs = UnionFindSet(n);
        ufs.makeSet(roads);
        for (auto vec : roads)
        {
            if (!ufs.isSameSet(vec[0], vec[1]))
            {
                ufs.unionSet(vec[0], vec[1]);
            }
        }
        return ufs.getMin(1);
    }
};