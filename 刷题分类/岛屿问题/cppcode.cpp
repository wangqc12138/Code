#include "head.h"
/*
在二维地图上， 0代表海洋， 1代表陆地，我们最多只能将一格 0 海洋变成 1变成陆地。
进行填海之后，地图上最大的岛屿面积是多少？（上、下、左、右四个方向相连的 1 可形成岛屿）
827------欠优
*/
class Solution {
public:
    vector<pair<int,int>> dir={{0,1},{0,-1},{1,0},{-1,0}};
    int largestIsland(vector<vector<int>>& grid) {
        int k=2,res=0;
        map<int,int> mapS;
        for(int i=0;i<grid.size();++i){
            for(int j=0;j<grid[0].size();++j){
                if(grid[i][j]==1){
                    int s=0;
                    dfs(grid,i,j,k++,s);
                    mapS[k-1]=s;
                    res=max(s,res);
                }
            }
        }
        for(int i=0;i<grid.size();++i){
            for(int j=0;j<grid[0].size();++j){
                if(grid[i][j]==0){
                    set<int> setIndex;
                    for(auto[x,y]:dir){
                        setIndex.insert(nextS(grid,i+x,j+y));
                    }
                    int S=0;
                    for(auto index:setIndex){
                        S+=mapS[index];
                    }
                    res=max(res,S+1);
                }
            }
        }
        return res;
    }
    int nextS(vector<vector<int>>& grid,int i,int j){
        if(i<0||i>=grid.size()||j<0||j>=grid[0].size()||grid[i][j]==0){
            return 0;
        }
        return grid[i][j];
    }
    void dfs(vector<vector<int>>& grid,int i,int j,int k,int &s){
        if(i<0||i>=grid.size()||j<0||j>=grid[0].size()||grid[i][j]!=1){
            return;
        }
        grid[i][j]=k;
        s++;
        for(auto[x,y]:dir){
            dfs(grid,i+x,j+y,k,s);
        }
    }
};
/*
给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
此外，你可以假设该网格的四条边均被水包围。
200
*/
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int res=0;
        for(int i=0;i<grid.size();++i){
            for(int j=0;j<grid[0].size();++j){
                if(grid[i][j]=='1'){
                    res++;
                    dfs(grid,i,j);
                }
            }
        }
        return res;
    }
    vector<pair<int,int>> dir={{0,1},{0,-1},{1,0},{-1,0}};
    void dfs(vector<vector<char>>& grid,int i,int j){
        if(i<0||i>=grid.size()||j<0||j>=grid[0].size()||grid[i][j]!='1'){
            return;
        }
        grid[i][j]='2';
        for(auto[x,y]:dir){
            dfs(grid,i+x,j+y);
        }
    }
};
/*
给定一个 row x col 的二维网格地图 grid ，其中：grid[i][j] = 1 表示陆地， grid[i][j] = 0 表示水域。
网格中的格子 水平和垂直 方向相连（对角线方向不相连）。整个网格被水完全包围，但其中恰好有一个岛屿（或者说，一个或多个表示陆地的格子相连组成的岛屿）。
岛屿中没有“湖”（“湖” 指水域在岛屿内部且不和岛屿周围的水相连）。格子是边长为 1 的正方形。网格为长方形，且宽度和高度均不超过 100 。计算这个岛屿的周长
463
*/
class Solution {
public:
    vector<pair<int,int>> dir={{0,1},{0,-1},{1,0},{-1,0}};
    int islandPerimeter(vector<vector<int>>& grid) {
        int res=0;
        for(int i=0;i<grid.size();++i){
            for(int j=0;j<grid[0].size();++j){
                if(grid[i][j]==1){
                    dfs(grid,i,j,res);
                    return res;
                }
            }
        }
        return 0;
    }
    void dfs(vector<vector<int>>& grid,int i,int j,int &C){
        if(i<0||i>=grid.size()||j<0||j>=grid[0].size()||grid[i][j]!=1){
            return;
        }
        grid[i][j]=2;
        C+=4;
        for(auto[x,y]:dir){
            if(next(grid,i+x,j+y)){
                C--;
            }
        }
        for(auto[x,y]:dir){
            dfs(grid,i+x,j+y,C);
        }
    }
    bool next(vector<vector<int>>& grid,int i,int j){
        if(i<0||i>=grid.size()||j<0||j>=grid[0].size()||grid[i][j]==0){
            return false;
        }
        return true;
    }
};
/*
给定一个包含了一些 0 和 1 的非空二维数组 grid 。
一个 岛屿 是由一些相邻的 1 (代表土地) 构成的组合，这里的「相邻」要求两个 1 必须在水平或者竖直方向上相邻。你可以假设 grid 的四个边缘都被 0（代表水）包围着。
找到给定的二维数组中最大的岛屿面积。(如果没有岛屿，则返回面积为 0 。)
695
*/
class Solution {
public:
    vector<pair<int,int>> dir={{0,1},{0,-1},{1,0},{-1,0}};
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int res=0;
        for(int i=0;i<grid.size();++i){
            for(int j=0;j<grid[0].size();++j){
                if(grid[i][j]==1){
                    int s=0;
                    dfs(grid,i,j,s);
                    res=max(s,res);
                }
            }
        }
        return res;
    }
    void dfs(vector<vector<int>>& grid,int i,int j,int &s){
        if(i<0||i>=grid.size()||j<0||j>=grid[0].size()||grid[i][j]!=1){
            return;
        }
        grid[i][j]=2;
        s++;
        for(auto[x,y]:dir){
            dfs(grid,i+x,j+y,s);
        }
    }
};