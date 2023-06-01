#include "head.h"
/* 
给你一个整数 n ，表示一个国家里的城市数目。城市编号为 0 到 n - 1 。

给你一个二维整数数组 roads ，其中 roads[i] = [ai, bi] 表示城市 ai 和 bi 之间有一条 双向 道路。

你需要给每个城市安排一个从 1 到 n 之间的整数值，且每个值只能被使用 一次 。道路的 重要性 定义为这条道路连接的两座城市数值 之和 。

请你返回在最优安排下，所有道路重要性 之和 最大 为多少。
 */
class Solution {
public:
    long long maximumImportance(int n, vector<vector<int>>& roads) {
        map<int,int> mp;
        map<int,vector<int>,greater<int>> mpv;
        for(auto vec:roads){
            mp[vec[0]]++;
            mp[vec[1]]++;
        }
        for(auto [x,y]:mp){
            mpv[y].emplace_back(x);
        }
        long long index=1;
        long long res=0;
        for(auto [x,y]:mpv){
            long long n=y.size();
            res+=x*(index+index+n-1)*n/2;
            index+=n;
        }
        return res;
    }
};