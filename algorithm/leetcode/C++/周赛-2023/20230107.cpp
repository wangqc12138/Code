#include "head.h"
/*
给你四个整数 length ，width ，height 和 mass ，分别表示一个箱子的三个维度和质量，请你返回一个表示箱子 类别 的字符串。

    如果满足以下条件，那么箱子是 "Bulky" 的：
        箱子 至少有一个 维度大于等于 104 。
        或者箱子的 体积 大于等于 109 。
    如果箱子的质量大于等于 100 ，那么箱子是 "Heavy" 的。
    如果箱子同时是 "Bulky" 和 "Heavy" ，那么返回类别为 "Both" 。
    如果箱子既不是 "Bulky" ，也不是 "Heavy" ，那么返回类别为 "Neither" 。
    如果箱子是 "Bulky" 但不是 "Heavy" ，那么返回类别为 "Bulky" 。
    如果箱子是 "Heavy" 但不是 "Bulky" ，那么返回类别为 "Heavy" 。

注意，箱子的体积等于箱子的长度、宽度和高度的乘积。
 */
class Solution
{
public:
    string categorizeBox(int length, int width, int height, int mass)
    {
        bool Bulky = false, Heavy = false;
        if (length >= pow(10, 4) || width >= pow(10, 4) || height >= pow(10, 4) || (long long)length * width * height >= pow(10, 9))
        {
            Bulky = true;
        }
        if (mass >= 100)
        {
            Heavy = true;
        }
        if (Bulky && Heavy)
        {
            return "Both";
        }
        else if (Bulky)
        {
            return "Bulky";
        }
        else if (Heavy)
        {
            return "Heavy";
        }
        return "Neither";
    }
};
/*
给你一个整数数据流，请你实现一个数据结构，检查数据流中最后 k 个整数是否 等于 给定值 value 。

请你实现 DataStream 类：

    DataStream(int value, int k) 用两个整数 value 和 k 初始化一个空的整数数据流。
    boolean consec(int num) 将 num 添加到整数数据流。
    如果后 k 个整数都等于 value ，返回 true ，否则返回 false 。如果少于 k 个整数，条件不满足，所以也返回 false 。

 */

/**
 * Your DataStream object will be instantiated and called as such:
 * DataStream* obj = new DataStream(value, k);
 * bool param_1 = obj->consec(num);
 */

/*
给你一个下标从 0 开始的整数数组 nums 。

三个下标 i ，j 和 k 的 有效值 定义为 ((nums[i] | nums[j]) & nums[k]) 。

一个数组的 xor 美丽值 是数组中所有满足 0 <= i, j, k < n  的三元组 (i, j, k) 的 有效值 的异或结果。

请你返回 nums 的 xor 美丽值。

注意：

    val1 | val2 是 val1 和 val2 的按位或。
    val1 & val2 是 val1 和 val2 的按位与。

 */
class Solution
{
public:
    int xorBeauty(vector<int> &nums)
    {
    }
};