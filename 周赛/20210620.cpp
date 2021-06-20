#include "head.h"
/* 
一款新的在线电子游戏在近期发布，在该电子游戏中，以 刻钟 为周期规划若干时长为 15 分钟 的游戏对局。这意味着，在 HH:00、HH:15、HH:30 和 HH:45 ，将会开始一个新的对局，其中 HH 用一个从 00 到 23 的整数表示。游戏中使用 24 小时制的时钟 ，所以一天中最早的时间是 00:00 ，最晚的时间是 23:59 。

给你两个字符串 startTime 和 finishTime ，均符合 "HH:MM" 格式，分别表示你 进入 和 退出 游戏的确切时间，请计算在整个游戏会话期间，你完成的 完整对局的对局数 。

例如，如果 startTime = "05:20" 且 finishTime = "05:59" ，这意味着你仅仅完成从 05:30 到 05:45 这一个完整对局。而你没有完成从 05:15 到 05:30 的完整对局，因为你是在对局开始后进入的游戏；同时，你也没有完成从 05:45 到 06:00 的完整对局，因为你是在对局结束前退出的游戏。
如果 finishTime 早于 startTime ，这表示你玩了个通宵（也就是从 startTime 到午夜，再从午夜到 finishTime）。

假设你是从 startTime 进入游戏，并在 finishTime 退出游戏，请计算并返回你完成的 完整对局的对局数 。
 */
class Solution {
public:
    int numberOfRounds(string startTime, string finishTime) {
        int starth=atoi(startTime.substr(0,2).c_str());
        int startm=atoi(startTime.substr(3,2).c_str());
        int finishh=atoi(finishTime.substr(0,2).c_str());
        int finishm=atoi(finishTime.substr(3,2).c_str());
        if(starth>finishh||starth==finishh&&startm>finishm){
            int i1=(60-startm)/15;
            starth++;
            int i2=(24-starth)*4;
            int i3=finishh*4;
            int i4=finishm/15;
            return i1+i2+i3+i4;
        }else if(starth==finishh){
            int i1=(60-startm)/15;
            int i2=(60-finishm)/15;
            if(finishm%15!=0){
                i2++;
            }
            return i1-i2;
        }else{
            int i1=(60-startm)/15;
            int i2=(finishh-starth+1)*4;
            int i3=finishm/15;
            return i1+i2+i3;
        }
        return 0;
    }
};
/* 
给你两个 m x n 的二进制矩阵 grid1 和 grid2 ，它们只包含 0 （表示水域）和 1 （表示陆地）。一个 岛屿 是由 四个方向 （水平或者竖直）上相邻的 1 组成的区域。任何矩阵以外的区域都视为水域。

如果 grid2 的一个岛屿，被 grid1 的一个岛屿 完全 包含，也就是说 grid2 中该岛屿的每一个格子都被 grid1 中同一个岛屿完全包含，那么我们称 grid2 中的这个岛屿为 子岛屿 。

请你返回 grid2 中 子岛屿 的 数目 。
 */
class Solution {
public:
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        unordered_map<int,int> umap;
        int count=1;
        for(int i=0;i<grid2.size();i++){
            for(int j=0;j<grid2[0].size();j++){
                if(grid2[i][j]==1){
                    dfs(grid2,i,j,++count);
                    umap.emplace(count,1);
                }
            }
        }
        for(int i=0;i<grid2.size();i++){
            for(int j=0;j<grid2[0].size();j++){
                if(grid2[i][j]!=0&&grid1[i][j]==1){
                    umap[grid2[i][j]]=0;
                }
            }
        }
        int res=0;
        for(int i=2;i<=count;i++){
            if(umap[i]==1){
                res++;
            }
        }
        return res;
    }
    void dfs(vector<vector<int>>& grid,int i,int j,int n){
        if(i<0||j<0||i>=grid.size()||j>=grid[0].size()||grid[i][j]!=1){
            return;
        }
        grid[i][j]=n;
        dfs(grid,i+1,j,n);
        dfs(grid,i-1,j,n);
        dfs(grid,i,j+1,n);
        dfs(grid,i,j-1,n);
    }
};
/* 
一个数组 a 的 差绝对值的最小值 定义为：0 <= i < j < a.length 且 a[i] != a[j] 的 |a[i] - a[j]| 的 最小值。如果 a 中所有元素都 相同 ，那么差绝对值的最小值为 -1 。

比方说，数组 [5,2,3,7,2] 差绝对值的最小值是 |2 - 3| = 1 。注意答案不为 0 ，因为 a[i] 和 a[j] 必须不相等。
给你一个整数数组 nums 和查询数组 queries ，其中 queries[i] = [li, ri] 。
对于每个查询 i ，计算 子数组 nums[li...ri] 中 差绝对值的最小值 ，子数组 nums[li...ri] 包含 nums 数组（下标从 0 开始）中下标在 li 和 ri 之间的所有元素（包含 li 和 ri 在内）。

请你返回 ans 数组，其中 ans[i] 是第 i 个查询的答案。

子数组 是一个数组中连续的一段元素。

|x| 的值定义为：

如果 x >= 0 ，那么值为 x 。
如果 x < 0 ，那么值为 -x 。
 */
class Solution {
public:
    vector<int> minDifference(vector<int>& nums, vector<vector<int>>& queries) {
        vector<int> res;
        for(auto vec:queries){
            set<int> temp(nums.begin()+vec[0],nums.begin()+vec[1]+1);
            if(temp.size()==1){
                res.emplace_back(-1);
                continue;
            }
            int m=INT_MAX,pre;
            int count=0;
            for(int i:temp){
                if(count!=0){
                    m=min(m,i-pre);  
                }
                pre=i;
                count++;
            }
            res.emplace_back(m);
        }
        return res;
    }
};