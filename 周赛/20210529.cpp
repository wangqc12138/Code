#include "head.h"
//飞马杯
//leetcode双周赛
/* 
如果一个字符串不含有任何重复字符，我们称这个字符串为 好 字符串。

给你一个字符串 s ，请你返回 s 中长度为 3 的 好子字符串 的数量。

注意，如果相同的好子字符串出现多次，每一次都应该被记入答案之中。

子字符串 是一个字符串中连续的字符序列。
 */
class Solution {
public:
    int countGoodSubstrings(string s) {
        int res=0;
        for(int i=2;i<s.size();i++){
            set<char> set;
            for(int j=0;j<3;j++){
                set.insert(s[i-j]);
            }
            if(set.size()==3){
                res++;
            }
        }
        return res;
    }
};
/* 
一个数对 (a,b) 的 数对和 等于 a + b 。最大数对和 是一个数对数组中最大的 数对和 。

比方说，如果我们有数对 (1,5) ，(2,3) 和 (4,4)，最大数对和 为 max(1+5, 2+3, 4+4) = max(6, 5, 8) = 8 。
给你一个长度为 偶数 n 的数组 nums ，请你将 nums 中的元素分成 n / 2 个数对，使得：

nums 中每个元素 恰好 在 一个 数对中，且
最大数对和 的值 最小 。
请你在最优数对划分的方案下，返回最小的 最大数对和 。
 */
class Solution {
public:
    int minPairSum(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int n=nums.size(),res=0;
        for(int i=0;i<n/2;i++){
            res=max(res,nums[i]+nums[n-1-i]);
        }
        return res;
    }
};
/* 
给你一个 m x n 的整数矩阵 grid 。

菱形和 指的是 grid 中一个正菱形 边界 上的元素之和。
本题中的菱形必须为正方形旋转45度，且四个角都在一个格子当中。下图是四个可行的菱形，每个菱形和应该包含的格子都用了相应颜色标注在图中。
 */
class Solution {
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        int m=grid.size(),n=grid[0].size();
        vector<int> vec;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                vector<int> temp=getSum(grid,i,j);
                vec.insert(vec.end(),temp.begin(),temp.end());
            }
        }
        sort(vec.begin(),vec.end(),greater<int>());
        vector<int> res;
        int k=0;
        for(int i:vec){
            if(res.size()==0||i!=res.back()){
                res.push_back(i);
                k++;
            }
            if(k==3){
                break;
            }
        }
        return res;
    }
    vector<int> getSum(vector<vector<int>>& grid,int i,int j){
        int m=grid.size(),n=grid[0].size();
        int y=min(j,min(n-1-j,(m-1-i)/2));
        vector<int> res={grid[i][j]};
        if(y==0){
            return res;
        }
        for(int x=1;x<=y;x++){
            int t=grid[i][j];
            for(int k=1;k<=x;k++){
                t+=grid[i+k][j-k]+grid[i+k][j+k];
            }
            t+=grid[i+2*x][j];
            for(int k=1;k<x;k++){
                t+=grid[i+2*x-k][j+k]+grid[i+2*x-k][j-k];
            }
            res.push_back(t);
        }
        return res;
    }
};
/* 
给你两个整数数组 nums1 和 nums2 ，它们长度都为 n 。

两个数组的 异或值之和 为 (nums1[0] XOR nums2[0]) + (nums1[1] XOR nums2[1]) + ... + (nums1[n - 1] XOR nums2[n - 1]) （下标从 0 开始）。

比方说，[1,2,3] 和 [3,2,1] 的 异或值之和 等于 (1 XOR 3) + (2 XOR 2) + (3 XOR 1) = 2 + 0 + 2 = 4 。
请你将 nums2 中的元素重新排列，使得 异或值之和 最小 。

请你返回重新排列之后的 异或值之和 。
 */
class Solution {
public:
    int minimumXORSum(vector<int>& nums1, vector<int>& nums2) {
        int n=nums1.size();
        vector<vector<int>> t1(n,vector<int>(2));
        vector<vector<int>> t2(n,vector<int>(2));
        for(int i=0;i<n;i++){
            t1[i][0]=nums1[i];
            for(int j=0;j<32;j++){
                int k=(nums1[i]>>j)&1;
            }
        }
    }
};