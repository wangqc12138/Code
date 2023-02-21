#include "head.h"
/*
给定一个整数数组  nums，求出数组从索引 i 到 j（i ≤ j）范围内元素的总和，包含 i、j 两点。
实现 NumArray 类：
    NumArray(int[] nums) 使用数组 nums 初始化对象
    int sumRange(int i, int j) 返回数组 nums 从索引 i 到 j（i ≤ j）范围内元素的总和，包含 i、j 两点（也就是 sum(nums[i], nums[i + 1], ... , nums[j])）
303
*/
class NumArray {
public:
    vector<int> vec;
    NumArray(vector<int>& nums) {
        vec.resize(nums.size());

        for (int i = 0; i < nums.size(); i++) {
            if (i == 0) {
                vec[0] = nums[0];
            } else {
                vec[i] = vec[i - 1] + nums[i];
            }
        }
    }

    int sumRange(int i, int j) {
        return i == 0 ? vec[j] : vec[j] - vec[i - 1];
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(i,j);
 */
/*
给定一个二维矩阵，计算其子矩形范围内元素的总和，该子矩阵的左上角为 (row1, col1) ，右下角为 (row2, col2) 。
304
*/
class NumMatrix {
public:
    NumMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        sumMatrix = vector<vector<int>>(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i > 0 && j > 0) {
                    sumMatrix[i][j] = sumMatrix[i - 1][j] + sumMatrix[i][j - 1] - sumMatrix[i - 1][j - 1] + matrix[i][j];
                } else if (i > 0) {
                    sumMatrix[i][j] = sumMatrix[i - 1][j] + matrix[i][j];
                } else if (j > 0) {
                    sumMatrix[i][j] = sumMatrix[i][j - 1] + matrix[i][j];
                } else {
                    sumMatrix[i][j] = matrix[i][j];
                }
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        if (row1 == 0 && col1 == 0) {
            return sumMatrix[row2][col2];
        } else if (row1 == 0) {
            return sumMatrix[row2][col2] - sumMatrix[row2][col1 - 1];
        } else if (col1 == 0) {
            return sumMatrix[row2][col2] - sumMatrix[row1 - 1][col2];
        } else {
            return sumMatrix[row2][col2] - sumMatrix[row2][col1 - 1] - sumMatrix[row1 - 1][col2] + sumMatrix[row1 - 1][col1 - 1];
        }
        return 0;
    }

private:
    vector<vector<int>> sumMatrix;
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */
/*
给你一个 m x n 的矩阵 matrix 和一个整数 k ，找出并返回矩阵内部矩形区域的不超过 k 的最大数值和。

题目数据保证总会存在一个数值和不超过 k 的矩形区域。
363
*/
// 使用vector会超时
class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int m = matrix.size(), n = matrix[0].size(), res = INT_MIN;
        int sumMatrix[m][n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i > 0 && j > 0) {
                    sumMatrix[i][j] = sumMatrix[i - 1][j] + sumMatrix[i][j - 1] - sumMatrix[i - 1][j - 1] + matrix[i][j];
                } else if (i > 0) {
                    sumMatrix[i][j] = sumMatrix[i - 1][j] + matrix[i][j];
                } else if (j > 0) {
                    sumMatrix[i][j] = sumMatrix[i][j - 1] + matrix[i][j];
                } else {
                    sumMatrix[i][j] = matrix[i][j];
                }
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int a = i; a < m; a++) {
                    for (int b = j; b < n; b++) {
                        int sum = 0;
                        if (i == 0 && j == 0) {
                            sum = sumMatrix[a][b];
                        } else if (i == 0) {
                            sum = sumMatrix[a][b] - sumMatrix[a][j - 1];
                        } else if (j == 0) {
                            sum = sumMatrix[a][b] - sumMatrix[i - 1][b];
                        } else {
                            sum = sumMatrix[a][b] - sumMatrix[a][j - 1] - sumMatrix[i - 1][b] + sumMatrix[i - 1][j - 1];
                        }
                        if (sum < k) {
                            res = max(res, sum);
                        } else if (sum == k) {
                            return k;
                        }
                    }
                }
            }
        }
        return res;
    }
};
/*
给定一个正整数、负整数和 0 组成的 N × M 矩阵，编写代码找出元素总和最大的子矩阵。

返回一个数组 [r1, c1, r2, c2]，其中 r1, c1 分别代表子矩阵左上角的行号和列号，r2, c2 分别代表右下角的行号和列号。若有多个满足条件的子矩阵，返回任意一个均可。

面试题 17.24. 最大子矩阵
*/
// 暴力解--超时
class Solution {
public:
    vector<int> getMaxMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size(), k = INT_MIN;
        vector<int> res;
        int sumMatrix[m + 1][n + 1];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                sumMatrix[i + 1][j + 1] = sumMatrix[i][j + 1] + sumMatrix[i + 1][j] - sumMatrix[i][j] + matrix[i][j];
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int a = i; a < m; a++) {
                    for (int b = j; b < n; b++) {
                        int sum = sumMatrix[a + 1][b + 1] - sumMatrix[a + 1][j] - sumMatrix[i][b + 1] + sumMatrix[i][j];
                        if (sum > k) {
                            k = sum;
                            res = vector<int>{i, j, a, b};
                        }
                    }
                }
            }
        }
        return res;
    }
};
class Solution {
public:
    vector<int> getMaxMatrix(vector<vector<int>>& matrix) {
        vector<int> res;
        int m = matrix.size(), n = matrix[0].size(), sum, maxsum = INT_MIN, row1, col1;
        vector<int> colsum(n, 0);
        for (int i = 0; i < m; i++) {
            for (int& cs : colsum) {
                cs = 0;
            }
            for (int j = i; j < m; j++) {
                sum = 0;
                for (int k = 0; k < n; k++) {
                    colsum[k] += matrix[j][k];
                    if (sum + colsum[k] > colsum[k]) {
                        sum += colsum[k];
                    } else {
                        row1 = i;
                        col1 = k;
                        sum = colsum[k];
                    }
                    if (sum > maxsum) {
                        maxsum = sum;
                        res = {row1, col1, j, k};
                    }
                }
            }
        }
        return res;
    }
};
//----------------------------------20220513
// 以下两题是结合了前缀和的，与其说动态规划，不如说跟前缀和的模板更像
/*
给定一个正整数、负整数和 0 组成的 N × M 矩阵，编写代码找出元素总和最大的子矩阵。

返回一个数组 [r1, c1, r2, c2]，其中 r1, c1 分别代表子矩阵左上角的行号和列号，r2, c2 分别代表右下角的行号和列号。若有多个满足条件的子矩阵，返回任意一个均可。

注意：本题相对书上原题稍作改动

面试题 17.24. 最大子矩阵
 */
/*
[9,-8,1,3,-2]
[-3,7,6,-2,4]
[6,-4,-4,8,-7]
 */
class Solution {
public:
    vector<int> getMaxMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size(), maxn = INT_MIN;
        int temp[n];
        vector<int> res(4);
        for (int i = 0; i < m; i++) {
            memset(temp, 0, sizeof(temp));
            for (int k = i; k < m; k++) {
                int c = 0, M = 0;
                for (int j = 0; j < n; j++) {
                    temp[j] += matrix[k][j];
                    if (M < 0) {
                        M = temp[j];
                        c = j;
                    } else {
                        M += temp[j];
                    }
                    if (M > maxn) {
                        res[0] = k, res[1] = c, res[2] = i, res[3] = j;
                        maxn = M;
                    }
                }
            }
        }
        return res;
    }
};
/*
给你一个 m x n 的矩阵 matrix 和一个整数 k ，找出并返回矩阵内部矩形区域的不超过 k 的最大数值和。

题目数据保证总会存在一个数值和不超过 k 的矩形区域。
363
 */
class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int dest) {
        int m = matrix.size(), n = matrix[0].size();
        int presum[m][n];
        memset(presum, 0, sizeof(presum));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i != 0) {
                    presum[i][j] = presum[i - 1][j];
                }
                presum[i][j] += matrix[i][j];
            }
        }
        int ans = INT_MIN;
        for (int i = 0; i < m; i++) {
            for (int k = i; k < m; k++) {
                set<int> st;
                st.emplace(0);
                int now = 0;
                for (int j = 0; j < n; j++) {
                    now += presum[k][j] - ((i == 0) ? 0 : presum[i - 1][j]);
                    // cout<<now<<endl;
                    auto itr = st.lower_bound(now - dest);
                    if (now - *itr <= dest) {
                        ans = max(ans, now - *itr);
                    }
                    if (ans == dest) {
                        return dest;
                    }
                    st.emplace(now);
                }
            }
        }
        return ans;
    }
};
/*
给定一个数组 nums 和一个目标值 k，找到和等于 k 的最长子数组长度。如果不存在任意一个符合要求的子数组，则返回 0。
注意:
 nums 数组的总和是一定在 32 位有符号整数范围之内的。
 map插入数据
 使用insert：包含key不更新value
 使用【】：直接更新
 325
*/
class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        map<int, int> m;
        m[0] = -1;
        int sum = 0, res = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            if (m.count(sum - k)) {
                res = max(res, i - m[sum - k]);
            }
            if (!m.count(sum)) {
                m[sum] = i;
            }
        }
        return res;
    }
};
/*
给定一个二进制数组, 找到含有相同数量的 0 和 1 的最长连续子数组（的长度）。
525
*/
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        map<int, int> m;
        m[0] = -1;
        int sum = 0, res = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i] == 0 ? -1 : 1;
            if (m.count(sum)) {
                res = max(res, i - m[sum]);
            }
            if (!m.count(sum)) {
                m[sum] = i;
            }
        }
        return res;
    }
};
/*
给你一份工作时间表 hours，上面记录着某一位员工每天的工作小时数。

我们认为当员工一天中的工作小时数大于 8 小时的时候，那么这一天就是「劳累的一天」。

所谓「表现良好的时间段」，意味在这段时间内，「劳累的天数」是严格 大于「不劳累的天数」。

请你返回「表现良好时间段」的最大长度。
1124
 */
class Solution {
public:
    int longestWPI(vector<int>& hours) {
        int res = 0, n = hours.size(), sum = 0;
        map<int, int> mp;
        for (int i = 0; i < n; i++) {
            sum += hours[i] > 8 ? 1 : -1;
            if (sum > 0) {
                res = max(res, i + 1);
            } else if (mp.count(sum - 1)) {
                res = max(res, i - mp[sum - 1]);
            }
            if (!mp.count(sum)) {
                mp[sum] = i;
            }
        }
        return res;
    }
};
/*
给你一个字符串 s ，请你返回满足以下条件的最长子字符串的长度：每个元音字母，即 'a'，'e'，'i'，'o'，'u' ，在子字符串中都恰好出现了偶数次。
1371

    1 <= s.length <= 5 x 10^5
    s 只包含小写英文字母。

*/
class Solution {
public:
    int findTheLongestSubstring(string s) {
    }
};
/*
给你一个整数数组 nums 和一个整数 k。
如果某个 连续 子数组中恰好有 k 个奇数数字，我们就认为这个子数组是「优美子数组」。
请返回这个数组中「优美子数组」的数目。
1248
*/
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        unordered_map<int, int> um;
        int res = 0, sum = 0;
        um[0] = 1;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i] % 2;
            if (um.count(sum - k)) {
                //+前面sum-k个奇数的子数组
                res += um[sum - k];
            }
            // sum个奇数的数组+1
            um[sum]++;
            // 求最长的子数组
            /*
            if(um.count(sum-k)){
                res=max(res,i-um[sum-k]);
            }
            if(!um.count(sum)){
                um[sum]=i;
            }
            */
        }
        return res;
    }
};
/*
给你一个整数数组 nums，请编写一个能够返回数组 “中心下标” 的方法。

数组 中心下标 是数组的一个下标，其左侧所有元素相加的和等于右侧所有元素相加的和。

如果数组不存在中心下标，返回 -1 。如果数组有多个中心下标，应该返回最靠近左边的那一个。

注意：中心下标可能出现在数组的两端。
724
 */
class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        int tmp = 0;
        map<int, int> m;
        for (int i = 0; i < nums.size(); i++) {
            if (tmp == sum - tmp - nums[i]) {
                return m[sum - tmp];
            }
            tmp += nums[i];
        }
        return -1;
    }
};
/*
给定一个整数数组和一个整数 k，你需要找到该数组中和为 k 的连续的子数组的个数。
560
 */
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        map<int, int> m;
        int sum = 0, res = 0;
        m[0] = 1;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            if (m.count(k - sum)) {
                res += m[k - sum];
            }
            m[sum]++;
        }
        return res;
    }
};
/*
给出矩阵 matrix 和目标值 target，返回元素总和等于目标值的非空子矩阵的数量。

子矩阵 x1, y1, x2, y2 是满足 x1 <= x <= x2 且 y1 <= y <= y2 的所有单元 matrix[x][y] 的集合。

如果 (x1, y1, x2, y2) 和 (x1', y1', x2', y2') 两个子矩阵中部分坐标不同（如：x1 != x1'），那么这两个子矩阵也不同。

1074
上题的二维版本
 */
class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
    }
};
/*
给定一个整数数组 A，返回其中元素之和可被 K 整除的（连续、非空）子数组的数目。
974
 */
class Solution {
public:
    int subarraysDivByK(vector<int>& A, int K) {
        int sum = 0, res = 0;
        map<int, int> m;
        m[0] = 1;
        for (int i = 0; i < A.size(); i++) {
            sum += A[i];
            int tmp = (sum % K + K) % K;
            if (m.count(tmp)) {
                res += m[tmp];
            }
            m[tmp]++;
        }
        return res;
    }
};
/*
给定一个包含 非负数 的数组和一个目标 整数 k .
编写一个函数来判断该数组是否含有连续的子数组，其大小至少为 2，且总和为 k 的倍数，即总和为 n * k ，其中 n 也是一个整数。
大小是指数组大小！！！
523
 */
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        long sum = 0;
        map<long, int> m;
        m[0] = -1;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            long tmp = (sum % k + k) % k;
            if (m.count(tmp)) {
                if (i - m[tmp] >= 2) {
                    return true;
                }
            }
            if (!m.count(tmp)) {
                m[tmp] = i;
            }
        }
        return false;
        /*
        数组总和不小于2
        int sum=0,res=0;
        map<int,vector<int>> m;
        m[0].push_back(0);
        for(int i=0;i<nums.size();i++){
            sum+=nums[i];
            int tmp=(sum%k+k)%k;
            if(m.count(tmp)){
                for(int s:m[tmp]){
                    if(sum-s>=2){
                        return true;
                    }
                }
            }
            m[tmp].push_back(sum);
        }
        return false; */
    }
};
/*
在由若干 0 和 1  组成的数组 A 中，有多少个和为 S 的非空子数组。
930
 */
class Solution {
public:
    int numSubarraysWithSum(vector<int>& A, int S) {
        map<int, int> m;
        int sum = 0, res = 0;
        m[0] = 1;
        for (int i = 0; i < A.size(); i++) {
            sum += A[i];
            if (m.count(sum - S)) {
                res += m[sum - S];
            }
            m[sum]++;
        }
        return res;
    }
};
/*
给你一份工作时间表 hours，上面记录着某一位员工每天的工作小时数。

我们认为当员工一天中的工作小时数大于 8 小时的时候，那么这一天就是「劳累的一天」。

所谓「表现良好的时间段」，意味在这段时间内，「劳累的天数」是严格 大于「不劳累的天数」。

请你返回「表现良好时间段」的最大长度。
前缀和+单调栈 -----------------
1124
 */
class Solution {
public:
    int longestWPI(vector<int>& hours) {
        int sum = 0;  // 劳累天数-不劳累天数
        unordered_map<int, int> ump;
        for (int i = 0; i < hours.size(); i++) {
            sum += hours[i] > 8 ? 1 : -1;
        }
    }
};
/*
给定一个正整数数组 w ，其中 w[i] 代表下标 i 的权重（下标从 0 开始），
请写一个函数 pickIndex ，它可以随机地获取下标 i，选取下标 i 的概率与 w[i] 成正比。

例如，对于 w = [1, 3]，挑选下标 0 的概率为 1 / (1 + 3) = 0.25 （即，25%），而选取下标 1 的概率为 3 / (1 + 3) = 0.75（即，75%）。

也就是说，选取下标 i 的概率为 w[i] / sum(w) 。
528
类似于函数piecewise_constant_distribution();
 */
class Solution {
public:
    Solution(vector<int>& w) {
        dis = uniform_int_distribution<int>(1, accumulate(w.begin(), w.end(), 0));
        partial_sum(w.begin(), w.end(), pre);
        rm = (mt19937)random_device{}();
    }
    int pickIndex() {
        int x = dis(rm);
        return lower_bound(pre.begin(), pre.end(), x) - pre.begin();
    }

private:
    vector<int> pre;
    uniform_int_distribution<int> dis;
    mt19937 rm;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
/*
给定一个非重叠轴对齐矩形的列表 rects，写一个函数 pick 随机均匀地选取矩形覆盖的空间中的整数点。

提示：

    整数点是具有整数坐标的点。
    矩形周边上的点包含在矩形覆盖的空间中。
    第 i 个矩形 rects [i] = [x1，y1，x2，y2]，其中 [x1，y1] 是左下角的整数坐标，[x2，y2] 是右上角的整数坐标。
    每个矩形的长度和宽度不超过 2000。
    1 <= rects.length <= 100
    pick 以整数坐标数组 [p_x, p_y] 的形式返回一个点。
    pick 最多被调用10000次。
497
 */
class Solution {
public:
    Solution(vector<int>& w) {
    }

    int pickIndex() {
        return 0;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
/*
给你一个整数数组 arr 。
现需要从数组中取三个下标 i、j 和 k ，其中 (0 <= i < j <= k < arr.length) 。
a 和 b 定义如下：
    a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]
    b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k]
注意：^ 表示 按位异或 操作。
请返回能够令 a == b 成立的三元组 (i, j , k) 的数目。
1442
 */
// 前缀异或
class Solution {
public:
    int countTriplets(vector<int>& arr) {
        int res = 0;
        vector<int> preXor(arr.size() + 1, 0);
        for (int i = 0; i < arr.size(); i++) {
            preXor[i + 1] = preXor[i] ^ arr[i];
        }
        for (int i = 0; i < arr.size(); i++) {
            for (int j = i + 1; j < arr.size(); j++) {
                for (int k = j; k < arr.size(); k++) {
                    if (preXor[i] == preXor[k + 1]) {
                        res++;
                    }
                }
            }
        }
        return res;
    }
};
class Solution {
public:
    int countTriplets(vector<int>& arr) {
        int res = 0;
        vector<int> preXor(arr.size() + 1, 0);
        for (int i = 0; i < arr.size(); i++) {
            preXor[i + 1] = preXor[i] ^ arr[i];
        }
        for (int i = 0; i < arr.size(); i++) {
            for (int k = i + 1; k < arr.size(); k++) {
                if (preXor[i] == preXor[k + 1]) {
                    res += k - i;
                }
            }
        }
        return res;
    }
};
// 还有一重循环的，！
/*
给你一个二维矩阵 matrix 和一个整数 k ，矩阵大小为 m x n 由非负整数组成。

矩阵中坐标 (a, b) 的 值 可由对所有满足 0 <= i <= a < m 且 0 <= j <= b < n 的元素 matrix[i][j]（下标从 0 开始计数）执行异或运算得到。

请你找出 matrix 的所有坐标中第 k 大的值（k 的值从 1 开始计数）。
1738
 */
class Solution {
public:
    int kthLargestValue(vector<vector<int>>& matrix, int k) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> preXor(m, vector<int>(n, 0));
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) {
                    preXor[i][j] = matrix[i][j];
                } else if (i == 0) {
                    preXor[i][j] = matrix[i][j] ^ preXor[i][j - 1];
                } else if (j == 0) {
                    preXor[i][j] = matrix[i][j] ^ preXor[i - 1][j];
                } else {
                    preXor[i][j] = matrix[i][j] ^ preXor[i - 1][j] ^ preXor[i][j - 1] ^ preXor[i - 1][j - 1];
                }
                pq.push(preXor[i][j]);
            }
        }
        for (int i = 1; i < k; i++) {
            pq.pop();
        }
        return pq.top();
    }
};
/*
给你一个长桌子，桌子上盘子和蜡烛排成一列。给你一个下标从 0 开始的字符串 s ，
它只包含字符 '*' 和 '|' ，其中 '*' 表示一个 盘子 ，'|' 表示一支 蜡烛 。

同时给你一个下标从 0 开始的二维整数数组 queries ，
其中 queries[i] = [lefti, righti] 表示 子字符串 s[lefti...righti] （包含左右端点的字符）。
对于每个查询，你需要找到 子字符串中 在 两支蜡烛之间 的盘子的 数目 。
如果一个盘子在 子字符串中 左边和右边 都 至少有一支蜡烛，那么这个盘子满足在 两支蜡烛之间 。

    比方说，s = "||**||**|*" ，查询 [3, 8] ，表示的是子字符串 "*||**|" 。
    子字符串中在两支蜡烛之间的盘子数目为 2 ，子字符串中右边两个盘子在它们左边和右边 都 至少有一支蜡烛。

请你返回一个整数数组 answer ，其中 answer[i] 是第 i 个查询的答案。
2055
 */
class Solution {
public:
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
        map<int, int> pre;
        vector<int> vec;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '|') {
                if (!vec.empty()) {
                    pre[i] += pre[vec.back()] + i - vec.back() - 1;
                } else {
                    pre[i] = 0;
                }
                vec.emplace_back(i);
            }
        }
        // for(auto [x,y]:pre){
        //     cout<<x<<" "<<y<<endl;
        // }
        // for(auto i:vec){
        //     cout<<i<<endl;
        // }
        vector<int> res;
        for (auto v : queries) {
            if (vec.empty() || v[0] >= vec.back() || v[1] <= vec[0]) {
                res.emplace_back(0);
                continue;
            }
            auto l = lower_bound(vec.begin(), vec.end(), v[0]) - vec.begin();
            auto r = upper_bound(vec.begin(), vec.end(), v[1]) - vec.begin() - 1;
            // cout<<vec[l]<<" "<<vec[r]<<endl;
            if (l >= r) {
                res.emplace_back(0);
                continue;
            }
            res.emplace_back(pre[vec[r]] - pre[vec[l]]);
        }
        return res;
    }
};
class Solution {
public:
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
        int n = s.size();
        vector<int> Left(n), Right(n), pre(n);
        int L = -1, R = -1;
        for (int i = 0, j = n - 1; i < n; i++, j--) {
            if (s[i] == '*') {
                pre[i] = i == 0 ? 1 : pre[i - 1] + 1;
            } else {
                L = i;
                pre[i] = i == 0 ? 0 : pre[i - 1];
            }
            if (s[j] == '|') {
                R = j;
            }
            Left[i] = L;
            Right[j] = R;
        }
        vector<int> res;
        for (auto vec : queries) {
            L = Right[vec[0]], R = Left[vec[1]];
            if (L == -1 || R == -1 || R <= L) {
                res.emplace_back(0);
            } else {
                res.emplace_back(pre[R] - pre[L]);
            }
        }
        return res;
    }
};
/*
给你一个 m x n 的矩阵 mat 和一个整数 k ，请你返回一个矩阵 answer ，其中每个 answer[i][j] 是所有满足下述条件的元素 mat[r][c] 的和：

    i - k <= r <= i + k,
    j - k <= c <= j + k 且
    (r, c) 在矩阵内。
1314
 */
class Solution {
public:
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k) {
    }
};
/*
给出矩阵 matrix 和目标值 target，返回元素总和等于目标值的非空子矩阵的数量。

子矩阵 x1, y1, x2, y2 是满足 x1 <= x <= x2 且 y1 <= y <= y2 的所有单元 matrix[x][y] 的集合。

如果 (x1, y1, x2, y2) 和 (x1', y1', x2', y2') 两个子矩阵中部分坐标不同（如：x1 != x1'），那么这两个子矩阵也不同。
1074
 */
class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
    }
};