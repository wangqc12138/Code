#include "head.h"
/*
实现支持下列接口的「快照数组」- SnapshotArray：

    SnapshotArray(int length) - 初始化一个与指定长度相等的 类数组 的数据结构。初始时，每个元素都等于 0。
    void set(index, val) - 会将指定索引 index 处的元素设置为 val。
    int snap() - 获取该数组的快照，并返回快照的编号 snap_id（快照号是调用 snap() 的总次数减去 1）。
    int get(index, snap_id) - 根据指定的 snap_id 选择快照，并返回该快照指定索引 index 的值。
1146
二分的需要看一下！
 */
class SnapshotArray
{
public:
    SnapshotArray(int length)
    {
    }

    void set(int index, int val)
    {
        data[s][index] = val;
    }

    int snap()
    {
        s++;
        data[s] = data[s - 1];
        return s - 1;
    }

    int get(int index, int snap_id)
    {
        return data[snap_id][index];
    }

private:
    map<int, map<int, int>> data;
    int s = 0;
};
/*
你会得到一个字符串 text 。你应该把它分成 k 个子字符串 (subtext1, subtext2，…， subtextk) ，要求满足:

    subtexti 是 非空 字符串
    所有子字符串的连接等于 text ( 即subtext1 + subtext2 + ... + subtextk == text )
    subtexti == subtextk - i + 1 表示所有 i 的有效值( 即 1 <= i <= k )

返回k可能最大值。
1147
 */
class Solution
{
public:
    int longestDecomposition(string text)
    {
    }
};
/*
给你一个整数数组 nums 。「数组值」定义为所有满足 0 <= i < nums.length-1 的 |nums[i]-nums[i+1]| 的和。

你可以选择给定数组的任意子数组，并将该子数组翻转。但你只能执行这个操作 一次 。

请你找到可行的最大 数组值 。
1330
 */
// 超时
class Solution
{
public:
    int maxValueAfterReverse(vector<int> &nums)
    {
        int n = nums.size(), sum = 0;
        vector<int> temp(n - 1);
        for (int i = 0; i < n - 1; i++)
        {
            sum += temp[i] = abs(nums[i] - nums[i + 1]);
        }
        int res = sum;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                res = max(res, sum - ((i > 0) ? temp[i - 1] : 0) - ((j < n - 1) ? temp[j] : 0) + ((i > 0) ? abs(nums[j] - nums[i - 1]) : 0) + ((j < n - 1) ? abs(nums[i] - nums[j + 1]) : 0));
            }
        }
        return res;
    }
};
/*
给你一个 n x n 整数矩阵 arr ，请你返回 非零偏移下降路径 数字和的最小值。

非零偏移下降路径 定义为：从 arr 数组中的每一行选择一个数字，且按顺序选出来的数字中，相邻数字不在原数组的同一列。
1289
 */
class Solution
{
public:
    int minFallingPathSum(vector<vector<int>> &grid)
    {
        int n = grid.size();
        vector<int> dp = grid[0];
        for (int i = 0; i < n - 1; i++)
        {
            vector<int> temp(n, INT_MAX);
            for (int j = 0; j < n; j++)
            {
                for (int k = 0; k < n; k++)
                {
                    if (j != k)
                    {
                        temp[k] = min(temp[k], dp[j] + grid[i + 1][k]);
                    }
                }
            }
            dp = temp;
        }
        return *min_element(dp.begin(), dp.end());
    }
};
// 优化
class Solution
{
public:
    int minFallingPathSum(vector<vector<int>> &grid)
    {
        int n = grid.size();
        vector<int> dp = grid[0];
        for (int i = 0; i < n - 1; i++)
        {
            int m1 = INT_MAX, m2 = INT_MAX, i1, i2;
            for (int j = 0; j < n; j++)
            {
                if (m1 >= dp[j])
                {
                    m2 = m1;
                    i2 = i1;
                    m1 = dp[j];
                    i1 = j;
                }
                else if (m2 > dp[j])
                {
                    m2 = dp[j];
                    i2 = j;
                }
            }
            for (int j = 0; j < n; j++)
            {
                if (j != i1)
                {
                    dp[j] = grid[i + 1][j] + m1;
                }
                else
                {
                    dp[j] = grid[i + 1][j] + m2;
                }
            }
        }
        return *min_element(dp.begin(), dp.end());
    }
};