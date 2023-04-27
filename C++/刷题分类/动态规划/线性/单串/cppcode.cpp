#include "head.h"
// LIS-----------------------------------------
/*
给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。

子序列 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。
300
 */
// dp-----时间过长！
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size(), res = 0;
        vector<int> dp(n, 1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[j] + 1, dp[i]);
                }
            }
            res = max(dp[i], res);
        }
        return res;
    }
};
//*****
// 贪心----better
// 找增速最慢的
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int len = 0, n = nums.size();
        vector<int> help(n);
        help[0] = nums[0];
        for (int i = 1; i < n; i++) {
            if (nums[i] > help[len]) {
                help[++len] = nums[i];
            } else {
                int k = lower_bound(help.begin(), help.begin() + len, nums[i]) - help.begin();
                help[k] = nums[i];
            }
        }
        return len + 1;
    }
};
/*
给定一个未排序的整数数组 nums ， 返回最长递增子序列的个数 。

注意 这个数列必须是 严格 递增的。
673
*/
// dp
// dp:记录最长序列的长度，dir:记录这个长度下的序列的数量
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size(), maxn = 0, res = 0;
        vector<int> dp(n, 1), dir(n, 1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    if (dp[i] < dp[j] + 1) {
                        dp[i] = dp[j] + 1;
                        dir[i] = dir[j];
                    } else if (dp[i] == dp[j] + 1) {
                        dir[i] += dir[j];
                    }
                }
            }
            if (dp[i] > maxn) {
                maxn = dp[i];
                res = dir[i];
            } else if (dp[i] == maxn) {
                res += dir[i];
            }
        }
        return res;
    }
};
//*****
// 尝试用贪心-----比较麻烦！
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size(), len = 0, res = 0;
        vector<int> help(n);
        for (int i = 0; i < n; i++) {
            int k = lower_bound(help.begin(), help.begin() + len + 1, nums[i]) - help.begin();
            help[k] = nums[i];
            if (k > len) {
                res = 1;
                len = k;
            } else if (k == len) {
                res++;
            }
        }
        return res;
    }
};
/*
给你一个二维整数数组 envelopes ，其中 envelopes[i] = [wi, hi] ，表示第 i 个信封的宽度和高度。

当另一个信封的宽度和高度都比这个信封大的时候，这个信封就可以放进另一个信封里，如同俄罗斯套娃一样。

请计算 最多能有多少个 信封能组成一组“俄罗斯套娃”信封（即可以把一个信封放到另一个信封里面）。
354
 */
// dp---TLE
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        auto cmp = [](auto& i, auto& j) { return i[0] < j[0] || i[0] == j[0] && i[1] > j[1]; };
        sort(envelopes.begin(), envelopes.end(), cmp);
        int n = envelopes.size(), res = 0;
        vector<int> dp(n, 1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (envelopes[i][1] > envelopes[j][1]) {
                    dp[i] = max(dp[j] + 1, dp[i]);
                }
            }
            res = max(res, dp[i]);
        }
        return res;
    }
};
//[1,7],[2,6],[5,9],[6,8],[7,8]
//[2,3],[5,4],[6,4],[6,7];
// 贪心---引用就不会超时
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        auto cmp = [](auto& i, auto& j) { return i[0] < j[0] || i[0] == j[0] && i[1] > j[1]; };
        sort(envelopes.begin(), envelopes.end(), cmp);
        int n = envelopes.size(), len = 0;
        vector<int> help(n);
        help[0] = envelopes[0][1];
        for (int i = 1; i < n; i++) {
            int k = lower_bound(help.begin(), help.begin() + len + 1, envelopes[i][1]) - help.begin();
            help[k] = envelopes[i][1];
            len = max(len, k);
        }
        return len + 1;
    }
};
/*
堆箱子。给你一堆n个箱子，箱子宽 wi、深 di、高 hi。箱子不能翻转，将箱子堆起来时，下面箱子的宽度、高度和深度必须大于上面的箱子。
实现一种方法，搭出最高的一堆箱子。箱堆的高度为每个箱子高度的总和。

输入使用数组[wi, di, hi]表示每个箱子。
面试题 08.13. 堆箱子
 */
class Solution {
public:
    int pileBox(vector<vector<int>>& box) {
    }
};
/*
给定一个区间的集合 intervals ，其中 intervals[i] = [starti, endi] 。返回 需要移除区间的最小数量，使剩余区间互不重叠 。
435
 */
// 普通做法--贪心找“瘦”的区间
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        auto cmp = [](auto& i, auto& j) { return i[0] < j[0] || i[0] == j[0] && i[1] < j[1]; };
        sort(intervals.begin(), intervals.end(), cmp);
        int R = -100000, ans = 0;
        for (auto vec : intervals) {
            int l = vec[0], r = vec[1];
            if (l >= R) {
                R = r;
                continue;
            }
            if (r < R) {
                R = r;
            }
            ans++;
        }
        return ans;
    }
};
//[1,7],[2,6],[5,9],[6,8],[7,8]
//[1,4],[2,3],[5,6],[5,7],[6,8]
// dp做法--最长子序列---TLE
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        auto cmp = [](auto& i, auto& j) { return i[0] < j[0] || i[0] == j[0] && i[1] < j[1]; };
        sort(intervals.begin(), intervals.end(), cmp);
        int n = intervals.size();
        vector<int> dp(n, 1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (intervals[i][0] >= intervals[j][1]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        return n - dp[n - 1];
    }
};
// dp做法用贪心二分就可以！
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        // 如果边界可以包含则第二元素递增
        auto cmp = [](auto& i, auto& j) { return i[0] < j[0] || i[0] == j[0] && i[1] < j[1]; };
        sort(intervals.begin(), intervals.end(), cmp);
        int n = intervals.size(), len = 0;
        vector<int> help(n, -50001);
        help[0] = intervals[0][1];
        for (int i = 1; i < n; i++) {
            // 相邻
            int k = upper_bound(help.begin(), help.begin() + len + 1, intervals[i][0]) - help.begin();
            if (k > len || help[k] > intervals[i][1]) {
                help[k] = intervals[i][1];
            }
            len = max(k, len);
        }
        return n - 1 - len;
    }
};
/*
给出 n 个数对。 在每一个数对中，第一个数字总是比第二个数字小。

现在，我们定义一种跟随关系，当且仅当 b < c 时，数对(c, d) 才可以跟在 (a, b) 后面。我们用这种形式来构造一个数对链。

给定一个数对集合，找出能够形成的最长数对链的长度。你不需要用到所有的数对，你可以以任何顺序选择其中的一些数对来构造。
646
 */
// 与上题唯一不同就是不允许相邻
// 贪心
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        auto cmp = [](auto& i, auto& j) { return i[0] < j[0] || i[0] == j[0] && i[1] < j[1]; };
        sort(pairs.begin(), pairs.end(), cmp);
        int R = INT_MIN, res = 0;
        for (auto vec : pairs) {
            int l = vec[0], r = vec[1];
            if (l > R) {
                res++;
                R = r;
            } else {
                R = min(r, R);
            }
        }
        return res;
    }
};
// dp--没超时
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        auto cmp = [](auto& i, auto& j) { return i[0] < j[0] || i[0] == j[0] && i[1] < j[1]; };
        sort(pairs.begin(), pairs.end(), cmp);
        int n = pairs.size();
        vector<int> dp(n, 1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (pairs[i][0] > pairs[j][1]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        return dp[n - 1];
    }
};
// dp做法用贪心二分就可以！
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        auto cmp = [](auto& i, auto& j) { return i[0] < j[0] || i[0] == j[0] && i[1] < j[1]; };
        sort(pairs.begin(), pairs.end(), cmp);
        int n = pairs.size(), len = 0;
        vector<int> help(n, -50001);
        help[0] = pairs[0][1];
        for (int i = 1; i < n; i++) {
            // 不相邻
            int k = lower_bound(help.begin(), help.begin() + len + 1, pairs[i][0]) - help.begin();
            if (k > len || help[k] > pairs[i][1]) {
                help[k] = pairs[i][1];
            }
            len = max(k, len);
        }
        return len + 1;
    }
};
/*
有一些球形气球贴在一堵用 XY 平面表示的墙面上。墙面上的气球记录在整数数组 points ，其中points[i] = [xstart, xend] 表示水平直径在 xstart 和 xend之间的气球。你不知道气球的确切 y 坐标。

一支弓箭可以沿着 x 轴从不同点 完全垂直 地射出。在坐标 x 处射出一支箭，若有一个气球的直径的开始和结束坐标为 xstart，xend， 且满足  xstart ≤ x ≤ xend，则该气球会被 引爆 。可以射出的弓箭的数量 没有限制 。 弓箭一旦被射出之后，可以无限地前进。

给你一个数组 points ，返回引爆所有气球所必须射出的 最小 弓箭数 。
452
 */
// 贪心：只要找出有最多有多少不重叠的气球即可，类似435
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        auto cmp = [](auto& i, auto& j) { return i[0] < j[0] || i[0] == j[0] && i[1] < j[1]; };
        sort(points.begin(), points.end(), cmp);
        int R = points[0][1], res = 1;
        for (int i = 1; i < points.size(); i++) {
            int l = points[i][0], r = points[i][1];
            if (l > R) {
                res++;
                R = r;
            }
            R = min(r, R);
        }
        return res;
    }
};
// dp--------TLE
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        int n = points.size();
        auto cmp = [](auto& i, auto& j) { return i[0] < j[0] || i[0] == j[0] && i[1] < j[1]; };
        sort(points.begin(), points.end(), cmp);
        vector<int> dp(n, 1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (points[i][0] > points[j][1]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        return dp[n - 1];
    }
};
// 贪心+二分
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        int n = points.size(), len = 0;
        auto cmp = [](auto& i, auto& j) { return i[0] < j[0] || i[0] == j[0] && i[1] < j[1]; };
        sort(points.begin(), points.end(), cmp);
        vector<int> help(n);
        help[0] = points[0][1];
        for (int i = 1; i < n; i++) {
            int k = lower_bound(help.begin(), help.begin() + len + 1, points[i][0]) - help.begin();
            if (k > len || help[k] > points[i][1]) {
                help[k] = points[i][1];
            }
            len = max(len, k);
        }
        return len + 1;
    }
};
/*
给定由 n 个小写字母字符串组成的数组 strs ，其中每个字符串长度相等。

选取一个删除索引序列，对于 strs 中的每个字符串，删除对应每个索引处的字符。

比如，有 strs = ["abcdef","uvwxyz"] ，删除索引序列 {0, 2, 3} ，删除后为 ["bef", "vyz"] 。

假设，我们选择了一组删除索引 answer ，那么在执行删除操作之后，最终得到的数组的行中的 每个元素 都是按字典序排列的（即 (strs[0][0] <= strs[0][1] <= ... <= strs[0][strs[0].length - 1]) 和 (strs[1][0] <= strs[1][1] <= ... <= strs[1][strs[1].length - 1]) ，依此类推）。

请返回 answer.length 的最小可能值 。
960
 */
class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
    }
};
// 最大子数组和-------------------------------------------------------------
/*
给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

子数组 是数组中的一个连续部分。
53
 */
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size(), res = nums[0];
        vector<int> dp = nums;
        for (int i = 1; i < n; i++) {
            dp[i] = max(dp[i], dp[i - 1] + nums[i]);
            res = max(res, dp[i]);
        }
        return res;
    }
};
/*
给你一个整数数组 nums ，请你找出数组中乘积最大的非空连续子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。

测试用例的答案是一个 32-位 整数。

子数组 是数组的连续子序列。
152
 */
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int minn = nums[0], maxn = nums[0], n = nums.size(), res = nums[0];
        for (int i = 1; i < n; i++) {
            int m1 = max(nums[i], max(maxn * nums[i], minn * nums[i]));
            int m2 = min(nums[i], min(maxn * nums[i], minn * nums[i]));
            maxn = m1, minn = m2;
            res = max(maxn, res);
        }
        return res;
    }
};
/*
给你一个整数数组，返回它的某个 非空 子数组（连续元素）在执行一次可选的删除操作后，所能得到的最大元素总和。
换句话说，你可以从原数组中选出一个子数组，并可以决定要不要从中删除一个元素（只能删一次哦），（删除后）子数组中至少应当有一个元素，
然后该子数组（剩下）的元素总和是所有子数组之中最大的。

注意，删除一个元素后，子数组 不能为空。
1186
 */
//[11,-10,-11,8,7,-6,9,4,11,6,5,0]
// 假设已经删除过了
class Solution {
public:
    int maximumSum(vector<int>& arr) {
        int n = arr.size(), del = 0, res = arr[0];
        // M为未删元素的最大值，m为删除一个元素的最大值
        int M = arr[0], m = arr[0];
        for (int i = 1; i < n; i++) {
            // 删除一个元素后最大值可能为：不删除元素的最大值、删除自身的最大值、删除前面元素的最大值
            m = max(max(arr[i], M + arr[i]), max(M, m + arr[i]));
            M = max(arr[i], M + arr[i]);
            if (arr[i] < del) {
                del = arr[i];
            }
            // cout<<M<<" "<<m<<endl;
            res = max(max(M, m), res);
        }
        return res;
    }
};

/*
给定一个整数数组 arr 和一个整数 k ，通过重复 k 次来修改数组。

例如，如果 arr = [1, 2] ， k = 3 ，那么修改后的数组将是 [1, 2, 1, 2, 1, 2] 。

返回修改后的数组中的最大的子数组之和。注意，子数组长度可以是 0，在这种情况下它的总和也是 0。

由于 结果可能会很大，需要返回的 109 + 7 的 模 。
1191**********************************
 */
class Solution {
public:
    int kConcatenationMaxSum(vector<int>& arr, int k) {
        int sum = accumulate(arr.begin(), arr.end(), 0);
        int res = 0, n = arr.size();
        int maxn = 0, m = 0;
        for (int i = 0; i < n * 2; i++) {
            m = max(m + arr[i % n], arr[i % n]);
            maxn = max(maxn, m);
            if (i == n - 1 && k == 1) {
                return maxn;
            }
        }
        if (sum < 0) {
            return maxn;
        }
        if (maxn == 0) {
            return 0;
        }
        return ((long long)(k - 2) * sum + maxn) % 1000000007;
    }
};
/*
给定一个长度为 n 的环形整数数组 nums ，返回 nums 的非空 子数组 的最大可能和 。

环形数组 意味着数组的末端将会与开头相连呈环状。形式上， nums[i] 的下一个元素是 nums[(i + 1) % n] ， nums[i] 的前一个元素是 nums[(i - 1 + n) % n] 。

子数组 最多只能包含固定缓冲区 nums 中的每个元素一次。形式上，对于子数组 nums[i], nums[i + 1], ..., nums[j] ，不存在 i <= k1, k2 <= j 其中 k1 % n == k2 % n 。
918
 */
// 两重循环--超时！
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int res = nums[0];
        for (int i = 0; i < nums.size(); i++) {
            int maxn = nums[i];
            for (int j = 1; j < nums.size(); j++) {
                maxn = max(nums[(j + i) % nums.size()], maxn + nums[(j + i) % nums.size()]);
                res = max(res, maxn);
            }
        }
        return res;
    }
};
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int maxn = nums[0], minn = nums[0], M = maxn, m = minn;
        for (int i = 1; i < nums.size(); i++) {
            maxn = max(nums[i], maxn + nums[i]);
            minn = min(nums[i], minn + nums[i]);
            M = max(maxn, M);
            m = min(minn, m);
        }
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum == m) {
            return M;
        }
        return max(M, sum - m);
    }
};
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
// ------------------打家劫舍------------------------
/*
你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，
如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。
198
 */
// 数组
class Solution {
public:
    int rob(vector<int>& nums) {
        vector<int> dp = nums;
        for (int i = 1; i < nums.size(); i++) {
            if (i == 1) {
                dp[i] = max(dp[0], dp[1]);
            } else {
                dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
            }
        }
        return dp[nums.size() - 1];
    }
};
// 不使用 数组
class Solution {
public:
    int rob(vector<int>& nums) {
        int p = nums[0], q = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            if (i == 1) {
                q = max(nums[0], nums[1]);
            } else {
                int m = max(p + nums[i], q);
                p = q;
                q = m;
            }
        }
        return q;
    }
};
/*
你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。这个地方所有的房屋都 围成一圈 ，这意味着第一个房屋和最后一个房屋是紧挨着的。
同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警 。

给定一个代表每个房屋存放金额的非负整数数组，计算你 在不触动警报装置的情况下 ，今晚能够偷窃到的最高金额。
213
 */
class Solution {
public:
    int rob(vector<int>& nums) {
        vector<int> t1(nums.begin(), nums.end() - 1), t2(nums.begin() + 1, nums.end());
        return max(rob_help(t1), rob_help(t2));
    }
    int rob_help(vector<int>& nums) {
        int p = nums[0], q = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            if (i == 1) {
                q = max(nums[0], nums[1]);
            } else {
                int m = max(p + nums[i], q);
                p = q;
                q = m;
            }
        }
        return q;
    }
};
/*
小偷又发现了一个新的可行窃的地区。这个地区只有一个入口，我们称之为 root 。

除了 root 之外，每栋房子有且只有一个“父“房子与之相连。一番侦察之后，聪明的小偷意识到“这个地方的所有房屋的排列类似于一棵二叉树”。
如果 两个直接相连的房子在同一天晚上被打劫 ，房屋将自动报警。

给定二叉树的 root 。返回 在不触动警报的情况下 ，小偷能够盗取的最高金额 。
337
 */
class Solution {
public:
    int rob(TreeNode* root) {
        auto [f, s] = dfs(root);
        return max(f, s);
    }
    // 返回值：不偷的最大值，偷的最大值
    pair<int, int> dfs(TreeNode* root) {
        if (root == NULL) {
            return {0, 0};
        }
        auto [lf, ls] = dfs(root->left);
        auto [rf, rs] = dfs(root->right);
        // 不偷：左、右孩子不偷/偷的最大值之和
        //  偷：左右孩子不偷加上本身偷的
        return {max(lf, ls) + max(rf, rs), lf + rf + root->val};
    }
};
/*
给你一个整数数组 nums ，你可以对它进行一些操作。

每次操作中，选择任意一个 nums[i] ，删除它并获得 nums[i] 的点数。之后，你必须删除 所有 等于 nums[i] - 1 和 nums[i] + 1 的元素。

开始你拥有 0 个点数。返回你能通过这些操作获得的最大点数。
740
 */
// 打家劫舍的换皮
class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        int maxn = *max_element(nums.begin(), nums.end());
        int n[maxn + 1];
        memset(n, 0, sizeof(n));
        for (int i : nums) {
            n[i]++;
        }
        // p不取当前元素，q取当前元素
        int p = 0, q = 0;
        for (int i = 1; i <= maxn; i++) {
            int m = q;
            q = n[i] * i + p;
            p = max(p, m);
        }
        return max(p, q);
    }
};

class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        map<int, int> mp;
        for (int i : nums) {
            mp[i] += i;
        }
        // p不取当前元素，q取当前元素
        int p = 0, q = 0, pre = -1;
        for (auto [x, y] : mp) {
            if (x - 1 != pre) {
                int m = p, n = q;
                p = max(p, q);
                q = max(m, n) + y;
            } else {
                int m = q;
                q = p + y;
                p = max(p, q);
            }
            pre = x;
        }
        return max(p, q);
    }
};
/*
给你一个披萨，它由 3n 块不同大小的部分组成，现在你和你的朋友们需要按照如下规则来分披萨：

    你挑选 任意 一块披萨。
    Alice 将会挑选你所选择的披萨逆时针方向的下一块披萨。
    Bob 将会挑选你所选择的披萨顺时针方向的下一块披萨。
    重复上述过程直到没有披萨剩下。

每一块披萨的大小按顺时针方向由循环数组 slices 表示。

请你返回你可以获得的披萨大小总和的最大值。
1388
 */
// 环形打家劫舍的换皮
// 还是有区别的，因为最多拿到n/3块
class Solution {
public:
    int maxSizeSlices(vector<int>& nums) {
        vector<int> t1(nums.begin(), nums.end() - 1);
        vector<int> t2(nums.begin() + 1, nums.end());
        return max(help(t1), help(t2));
    }
    int help(vector<int>& nums) {
        int n = nums.size(), k = (n + 1) / 3;
        // 第n个位置拿k个披萨的最大值
        int dp[n][k + 1];
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= k; j++) {
                if (i == 0) {
                    dp[i][j] = nums[i];
                } else if (i == 1) {
                    dp[i][j] = max(nums[i], nums[i - 1]);
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i - 2][j - 1] + nums[i]);
                }
            }
        }
        return dp[n - 1][k];
    }
};
//-----------变形考虑两个位置
/*
如果序列 X_1, X_2, ..., X_n 满足下列条件，就说它是 斐波那契式 的：

    n >= 3
    对于所有 i + 2 <= n，都有 X_i + X_{i+1} = X_{i+2}

给定一个严格递增的正整数数组形成序列 arr ，找到 arr 中最长的斐波那契式的子序列的长度。如果一个不存在，返回  0 。

（回想一下，子序列是从原序列 arr 中派生出来的，它从 arr 中删掉任意数量的元素（也可以不删），而不改变其余元素的顺序。例如， [3, 5, 8] 是 [3, 4, 5, 6, 7, 8] 的一个子序列）
873
 */
class Solution {
public:
    int lenLongestFibSubseq(vector<int>& arr) {
        int n = arr.size(), ans = 0;
        // j,k
        int dp[n - 1][n];
        memset(dp, 0, sizeof(dp));
        unordered_map<int, int> ump;
        for (int j = 0; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                int diff = arr[k] - arr[j];
                if (ump.count(diff)) {
                    dp[j][k] = dp[ump[diff]][j] + 1;
                    ans = max(ans, dp[j][k]);
                }
            }
            ump[arr[j]] = j;
        }
        return ans == 0 ? 0 : 2 + ans;
    }
};
/*
给你一个整数数组 nums，返回 nums 中最长等差子序列的长度。

回想一下，nums 的子序列是一个列表 nums[i1], nums[i2], ..., nums[ik] ，且 0 <= i1 < i2 < ... < ik <= nums.length - 1。
并且如果 seq[i+1] - seq[i]( 0 <= i < seq.length - 1) 的值都相同，那么序列 seq 是等差的。
1027
0 <= nums[i] <= 500
 */
class Solution {
public:
    int longestArithSeqLength(vector<int>& nums) {
        int n = nums.size(), res = 0;
        int dp[n - 1][n];
        memset(dp, 0, sizeof(dp));
        unordered_map<int, int> ump;
        for (int j = 0; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                int p = 2 * nums[j] - nums[k];
                if (ump.count(p)) {
                    dp[j][k] = dp[ump[p]][j] + 1;
                    res = max(res, dp[j][k]);
                }
            }
            ump[nums[j]] = j;
        }
        return res + 2;
    }
};
// 还有一种方法
// 上一种是以位置为维度，dp[i][j]是以i,j位置结尾的等差最长
// 因为是等差数列，所以可以dp[i][j]以i位置结尾j是公差
class Solution {
public:
    int longestArithSeqLength(vector<int>& nums) {
        int n = nums.size(), res = 0;
        int dp[n][2000];
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < n; i++) {
            // 要从0->i，因为后续可能比前面长，反过来就会被覆盖
            for (int j = 0; j < i; j++) {
                int diff = nums[i] - nums[j] + 1000;
                dp[i][diff] = dp[j][diff] + 1;
                res = max(res, dp[i][diff]);
            }
        }
        return res + 1;
    }
};
/*
给你一个整数数组 arr 和一个整数 difference，请你找出并返回 arr 中最长等差子序列的长度，该子序列中相邻元素之间的差等于 difference 。

子序列 是指在不改变其余元素顺序的情况下，通过删除一些元素或不删除任何元素而从 arr 派生出来的序列。

1218
很像，但是会超时！
 */
class Solution {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
    }
};
/*
给你一个整数数组 nums，返回 nums 中最长等差子序列的长度。

回想一下，nums 的子序列是一个列表 nums[i1], nums[i2], ..., nums[ik] ，且 0 <= i1 < i2 < ... < ik <= nums.length - 1。并且如果 seq[i+1] - seq[i]( 0 <= i < seq.length - 1) 的值都相同，那么序列 seq 是等差的。
T1027
 */
class Solution {
public:
    int longestArithSeqLength(vector<int>& A) {
        int n = A.size(), res = 0;
        int dp[n][2000];
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < n; i++) {
            for (int j = i - 1; j >= 0; j--) {
                int sub = A[i] - A[j] + 1000;
                dp[i][sub] = max(dp[i][sub], dp[j][sub] + 1);
                res = max(res, dp[i][sub]);
            }
        }
        return res + 1;
    }
};