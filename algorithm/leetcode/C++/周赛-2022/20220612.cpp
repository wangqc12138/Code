#include "head.h"
/* 
给你一个下标从 0 开始的二维整数数组 brackets ，其中 brackets[i] = [upperi, percenti] ，表示第 i 个税级的上限是 upperi ，征收的税率为 percenti 。
税级按上限 从低到高排序（在满足 0 < i < brackets.length 的前提下，upperi-1 < upperi）。

税款计算方式如下：

    不超过 upper0 的收入按税率 percent0 缴纳
    接着 upper1 - upper0 的部分按税率 percent1 缴纳
    然后 upper2 - upper1 的部分按税率 percent2 缴纳
    以此类推

给你一个整数 income 表示你的总收入。返回你需要缴纳的税款总额。与标准答案误差不超 10-5 的结果将被视作正确答案。
 */
class Solution {
public:
    double calculateTax(vector<vector<int>>& brackets, int income) {
        double res=0;
        int pre=0;
        for(int i=0;i<brackets.size();i++){
            if(income<=brackets[i][0]){
                res+=(income-pre)*brackets[i][1];
            }else{
                res+=(brackets[i][0]-pre)*brackets[i][1];
            }
        }     
        res=res/100.00;
        return res; 
    }
};
/* 
给你一个下标从 0 开始的整数矩阵 grid ，矩阵大小为 m x n ，由从 0 到 m * n - 1 的不同整数组成。你可以在此矩阵中，从一个单元格移动到 下一行 的任何其他单元格。
如果你位于单元格 (x, y) ，且满足 x < m - 1 ，你可以移动到 (x + 1, 0), (x + 1, 1), ..., (x + 1, n - 1) 中的任何一个单元格。注意： 在最后一行中的单元格不能触发移动。

每次可能的移动都需要付出对应的代价，代价用一个下标从 0 开始的二维数组 moveCost 表示，该数组大小为 (m * n) x n ，
其中 moveCost[i][j] 是从值为 i 的单元格移动到下一行第 j 列单元格的代价。从 grid 最后一行的单元格移动的代价可以忽略。

grid 一条路径的代价是：所有路径经过的单元格的 值之和 加上 所有移动的 代价之和 。从 第一行 任意单元格出发，返回到达 最后一行 任意单元格的最小路径代价。

2304
 */
using pii=pair<int,int>;
using ppi=pair<pii,int>;
class Solution {
public:
    int minPathCost(vector<vector<int>>& grid, vector<vector<int>>& moveCost) {
        int m=grid.size(),n=grid[0].size();
        auto cmp=[](ppi a,ppi b){return a.second>b.second;};
        priority_queue<ppi,vector<ppi>,decltype(cmp)> mpq(cmp);
        mpq.emplace(pii(-1,-1),0);
        vector<vector<int>> visit(m,vector<int>(n,0));
        while(!mpq.empty()){
            ppi t=mpq.top();
            mpq.pop();
            if(t.first.first==m-1){
                return t.second;
            }
            int i=t.first.first;
            if(i!=-1){
                if(visit[i][t.first.second]==1){
                    continue;
                }
                visit[i][t.first.second]=1;
            }
            for(int j=0;j<n;j++){
                if(visit[i+1][j]==1){
                    continue;
                }
                int k=grid[i+1][j];
                mpq.emplace(pii(i+1,j),t.second+k+((i==-1)?0:moveCost[grid[i][t.first.second]][j]));
            }
        }
        return -1;
    }
};
//dp---------------待定
/* 
给你一个整数数组 cookies ，其中 cookies[i] 表示在第 i 个零食包中的饼干数量。另给你一个整数 k 表示等待分发零食包的孩子数量，所有 零食包都需要分发。
在同一个零食包中的所有饼干都必须分发给同一个孩子，不能分开。

分发的 不公平程度 定义为单个孩子在分发过程中能够获得饼干的最大总数。

返回所有分发的最小不公平程度。
2305
 */
class Solution {
public:
    int distributeCookies(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        int L=nums[0];
        int R=accumulate(nums.begin(),nums.end(),0);
        while(L<R){
            int mid=(L+R)/2;
            int t=0,sum=0;
            for(auto i:nums){
                if(sum+i>=mid){
                    sum=0;
                    t++;
                }else{
                    sum+=i;
                }
            }
            if(t>=k){
                R=mid;
            }else{
                L=mid+1;
            }
        }
        return L;
    }
};