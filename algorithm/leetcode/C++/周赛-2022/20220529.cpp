#include "head.h"
class Solution {
public:
    int totalSteps(vector<int>& nums) {
        int n=nums.size();
        for(int i=n-1;i>=0;i--){
            if(nums[i]<nums[i-1]){

            }else{

            }
        }
    }
};
/*
给你一个下标从 0 开始的二维整数数组 grid ，数组大小为 m x n 。每个单元格都是两个值之一：

    0 表示一个 空 单元格，
    1 表示一个可以移除的 障碍物 。

你可以向上、下、左、右移动，从一个空单元格移动到另一个空单元格。

现在你需要从左上角 (0, 0) 移动到右下角 (m - 1, n - 1) ，返回需要移除的障碍物的 最小 数目。
 */
using pii=pair<int,int>;
using ppi=pair<pii,int>;
class Solution {
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int m=grid.size(),n=grid[0].size();
        vector<vector<int>> p(m,vector<int>(n,100001));
        vector<pii> dir={{0,1},{0,-1},{1,0},{-1,0}};
        auto cmp=[](auto i,auto j){return i.second>j.second;};
        priority_queue<ppi,vector<ppi>,decltype(cmp)> mpq(cmp);
        p[0][0]=0;
        mpq.emplace(ppi({{0,0},0}));
        while(!mpq.empty()){
            ppi t=mpq.top();
            int x=t.first.first,y=t.first.second,z=t.second;
            mpq.pop();
            if(x==m-1&&y==n-1){
                return z;
            }
            for(auto [i,j]:dir){
                if(x+i<0||x+i>=m||y+j<0||y+j>=n||z+grid[x+i][y+j]>=p[x+i][y+j]){
                    continue;
                }
                p[x+i][y+j]=z+grid[x+i][y+j];
                mpq.emplace(ppi({x+i,y+j},z+grid[x+i][y+j]));
            }
        }
        return 0;
    }
};
