#include "head.h"
//LIS-----------------------------------------
/* 
给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。

子序列 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。
300
 */
//dp-----时间过长！
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n=nums.size(),res=0;
        vector<int> dp(n,1);
        for(int i=0;i<n;i++){
            for(int j=0;j<i;j++){
                if(nums[i]>nums[j]){
                    dp[i]=max(dp[j]+1,dp[i]);
                }
            }
            res=max(dp[i],res);
        }
        return res;
    }
};
//*****
//贪心----better
//找增速最慢的
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int len=0,n=nums.size();
        vector<int> help(n);
        help[0]=nums[0];
        for(int i=1;i<n;i++){
            if(nums[i]>help[len]){
                help[++len]=nums[i];
            }else{
                int k=lower_bound(help.begin(),help.begin()+len,nums[i])-help.begin();
                help[k]=nums[i];
            }
        }
        return len+1;
    }
};
/* 
给定一个未排序的整数数组 nums ， 返回最长递增子序列的个数 。

注意 这个数列必须是 严格 递增的。
673
*/
//dp
//dp:记录最长序列的长度，dir:记录这个长度下的序列的数量
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n=nums.size(),maxn=0,res=0;
        vector<int> dp(n,1),dir(n,1);
        for(int i=0;i<n;i++){
            for(int j=0;j<i;j++){
                if(nums[i]>nums[j]){
                    if(dp[i]<dp[j]+1){
                        dp[i]=dp[j]+1;
                        dir[i]=dir[j];
                    }else if(dp[i]==dp[j]+1){
                        dir[i]+=dir[j];
                    }
                }
            }
            if(dp[i]>maxn){
                maxn=dp[i];
                res=dir[i];
            }else if(dp[i]==maxn){
                res+=dir[i];
            }
        }
        return res;
    }
};
//*****
//尝试用贪心
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n=nums.size(),len=0;
        vector<int> help(n),cnt();
        help[0]=nums[0];
        for(int i=1;i<n;i++){
            if(nums[i]>help[len]){
                help[++len]=nums[i];
                 
            }
        }
    }
};
/* 
给你一个二维整数数组 envelopes ，其中 envelopes[i] = [wi, hi] ，表示第 i 个信封的宽度和高度。

当另一个信封的宽度和高度都比这个信封大的时候，这个信封就可以放进另一个信封里，如同俄罗斯套娃一样。

请计算 最多能有多少个 信封能组成一组“俄罗斯套娃”信封（即可以把一个信封放到另一个信封里面）。
354
 */
//dp---TLE
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        auto cmp=[](auto &i,auto &j){return i[0]<j[0]||i[0]==j[0]&&i[1]>j[1];};
        sort(envelopes.begin(),envelopes.end(),cmp);
        int n=envelopes.size(),res=0;
        vector<int> dp(n,1);
        for(int i=0;i<n;i++){
            for(int j=0;j<i;j++){
                if(envelopes[i][1]>envelopes[j][1]){
                    dp[i]=max(dp[j]+1,dp[i]);
                }
            }
            res=max(res,dp[i]);
        }
        return res;
    }
};
//贪心---引用就不会超时
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        auto cmp=[](auto &i,auto &j){return i[0]<j[0]||i[0]==j[0]&&i[1]>j[1];};
        sort(envelopes.begin(),envelopes.end(),cmp);
        int n=envelopes.size(),len=0;
        vector<int> help(n);
        help[0]=envelopes[0][1];
        for(int i=1;i<n;i++){
            int k=lower_bound(help.begin(),help.begin()+len+1,envelopes[i][1])-help.begin();
            help[k]=envelopes[i][1];
            len=max(len,k);
        }
        return len+1;
    }
};
/* 
堆箱子。给你一堆n个箱子，箱子宽 wi、深 di、高 hi。箱子不能翻转，将箱子堆起来时，下面箱子的宽度、高度和深度必须大于上面的箱子。实现一种方法，搭出最高的一堆箱子。箱堆的高度为每个箱子高度的总和。

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
/* 
给出 n 个数对。 在每一个数对中，第一个数字总是比第二个数字小。

现在，我们定义一种跟随关系，当且仅当 b < c 时，数对(c, d) 才可以跟在 (a, b) 后面。我们用这种形式来构造一个数对链。

给定一个数对集合，找出能够形成的最长数对链的长度。你不需要用到所有的数对，你可以以任何顺序选择其中的一些数对来构造。
646
 */
/* 
有一些球形气球贴在一堵用 XY 平面表示的墙面上。墙面上的气球记录在整数数组 points ，其中points[i] = [xstart, xend] 表示水平直径在 xstart 和 xend之间的气球。你不知道气球的确切 y 坐标。

一支弓箭可以沿着 x 轴从不同点 完全垂直 地射出。在坐标 x 处射出一支箭，若有一个气球的直径的开始和结束坐标为 xstart，xend， 且满足  xstart ≤ x ≤ xend，则该气球会被 引爆 。可以射出的弓箭的数量 没有限制 。 弓箭一旦被射出之后，可以无限地前进。

给你一个数组 points ，返回引爆所有气球所必须射出的 最小 弓箭数 。
452
 */
/* 
给定由 n 个小写字母字符串组成的数组 strs ，其中每个字符串长度相等。

选取一个删除索引序列，对于 strs 中的每个字符串，删除对应每个索引处的字符。

比如，有 strs = ["abcdef","uvwxyz"] ，删除索引序列 {0, 2, 3} ，删除后为 ["bef", "vyz"] 。

假设，我们选择了一组删除索引 answer ，那么在执行删除操作之后，最终得到的数组的行中的 每个元素 都是按字典序排列的（即 (strs[0][0] <= strs[0][1] <= ... <= strs[0][strs[0].length - 1]) 和 (strs[1][0] <= strs[1][1] <= ... <= strs[1][strs[1].length - 1]) ，依此类推）。

请返回 answer.length 的最小可能值 。
960
 */
//最大子数组和-------------------------------------------------------------
/* 
给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

子数组 是数组中的一个连续部分。
53
 */
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n=nums.size(),res=nums[0];
        vector<int> dp=nums;
        for(int i=1;i<n;i++){
            dp[i]=max(dp[i],dp[i-1]+nums[i]);
            res=max(res,dp[i]);
        }
        return res;
    }
};