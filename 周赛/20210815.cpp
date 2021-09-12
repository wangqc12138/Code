#include "head.h"
/* 
给你一个字符串数组 patterns 和一个字符串 word ，统计 patterns 中有多少个字符串是 word 的子字符串。返回字符串数目。

子字符串 是字符串中的一个连续字符序列。
 */
class Solution {
public:
    int numOfStrings(vector<string>& patterns, string word) {
        int res=0;
        for(string str:patterns){
            if(word.find(str)!=word.npos){
                res++;
            }
        }
        return res;
    }
};
/* 
给你一个 下标从 0 开始 的数组 nums ，数组由若干 互不相同的 整数组成。你打算重新排列数组中的元素以满足：重排后，数组中的每个元素都 不等于 其两侧相邻元素的 平均值 。

更公式化的说法是，重新排列的数组应当满足这一属性：对于范围 1 <= i < nums.length - 1 中的每个 i ，(nums[i-1] + nums[i+1]) / 2 不等于 nums[i] 均成立 。

返回满足题意的任一重排结果。
 */
class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        int n=nums.size();
        sort(nums.begin(),nums.end());
        vector<int> res(n);
        int j=0;
        for(int i=0;i<n;i+=2){
            res[i]=nums[j++];
        }
        for(int i=1;i<n;i+=2){
            res[i]=nums[j++];
        }
        return res;
    }
};
/* 
给你一个正整数 p 。你有一个下标从 1 开始的数组 nums ，这个数组包含范围 [1, 2p - 1] 内所有整数的二进制形式（两端都 包含）。你可以进行以下操作 任意 次：

从 nums 中选择两个元素 x 和 y  。
选择 x 中的一位与 y 对应位置的位交换。对应位置指的是两个整数 相同位置 的二进制位。
比方说，如果 x = 1101 且 y = 0011 ，交换右边数起第 2 位后，我们得到 x = 1111 和 y = 0001 。

请你算出进行以上操作 任意次 以后，nums 能得到的 最小非零 乘积。将乘积对 109 + 7 取余 后返回。
 */
class Solution {
public:
    int minNonZeroProduct(int p) {

    }
};
/* 
给你一个下标从 1 开始的二进制矩阵，其中 0 表示陆地，1 表示水域。同时给你 row 和 col 分别表示矩阵中行和列的数目。

一开始在第 0 天，整个 矩阵都是 陆地 。但每一天都会有一块新陆地被 水 淹没变成水域。
给你一个下标从 1 开始的二维数组 cells ，其中 cells[i] = [ri, ci] 表示在第 i 天，第 ri 行 ci 列（下标都是从 1 开始）的陆地会变成 水域 （也就是 0 变成 1 ）。

你想知道从矩阵最 上面 一行走到最 下面 一行，且只经过陆地格子的 最后一天 是哪一天。你可以从最上面一行的 任意 格子出发，到达最下面一行的 任意 格子。你只能沿着 四个 基本方向移动（也就是上下左右）。

请返回只经过陆地格子能从最 上面 一行走到最 下面 一行的 最后一天 。
 */
class Solution {
public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        vector<vector<int>> nums(row,vector<int>(col,0));
        vector<vector<int>> dir={{0,1},{0,-1},{1,0}};
        queue<pair<int,int>> mq;
        int res=1;
        for(auto vec:cells){
            vec[0]--;
            vec[1]--;
        }
        nums[cells[0][0]][cells[0][1]]=1;
        for(int i=0;i<col;i++){
            if(nums[0][i]==0){
                mq.emplace(0,i);
                nums[0][i]=2;
            }
        }
        while(mq.empty()){
            int len=mq.size();
            nums[cells[res][0]][cells[res][1]]=1;
            for(int i=0;i<len;i++){
                int x=mq.front().first;
                int y=mq.front().second;
                mq.pop();
                if(x==row-1){
                    return res;
                }
                for(auto vec:dir){
                    if(y+vec[1]<0||y+vec[1]>=col||nums[x+vec[0]][y+vec[1]]!=0){
                        continue;
                    }
                    if(x+vec[0]==row-1){
                        return res+1;
                    }
                    nums[x+vec[0]][y+vec[1]]=2;
                    mq.emplace(x+vec[0],y+vec[1]);
                }
            }
            res++;
        }
        return -1;
    }
};