#include "head.h"
/* 
给你一个大小为 n x n 的整数矩阵 grid 。

生成一个大小为 (n - 2) x (n - 2) 的整数矩阵  maxLocal ，并满足：

    maxLocal[i][j] 等于 grid 中以 i + 1 行和 j + 1 列为中心的 3 x 3 矩阵中的 最大值 。

换句话说，我们希望找出 grid 中每个 3 x 3 矩阵中的最大值。

返回生成的矩阵。
 */
class Solution {
public:
    vector<vector<int>> largestLocal(vector<vector<int>>& grid) {
        int n=grid.size();
        vector<vector<int>> res;
        auto getMax=[&](int i,int j){
            int re=INT_MIN;
            for(int a=i-1;a<=i+1;a++){
                for(int b=j-1;b<=j+1;b++){
                    re=max(re,grid[a][b]);
                }
            }
            return re;
        };
        for(int i=1;i<=n-2;i++){
            vector<int> temp;
            for(int j=1;j<=n-2;j++){
                temp.emplace_back((i,j));
            }
            res.emplace_back(temp);
        }
        return res;
    }
};
/* 
给你一个有向图，图中有 n 个节点，节点编号从 0 到 n - 1 ，其中每个节点都 恰有一条 出边。

图由一个下标从 0 开始、长度为 n 的整数数组 edges 表示，其中 edges[i] 表示存在一条从节点 i 到节点 edges[i] 的 有向 边。

节点 i 的 边积分 定义为：所有存在一条指向节点 i 的边的节点的 编号 总和。

返回 边积分 最高的节点。如果多个节点的 边积分 相同，返回编号 最小 的那个。

 */
class Solution {
public:
    int edgeScore(vector<int>& edges) {
        int n=edges.size();
        vector<long long> score(n,0);
        for(int i=0;i<n;i++){
            score[edges[i]]+=i;
        }
        long long maxn=*max_element(score.begin(),score.end());
        for(int i=0;i<n;i++){
            if(score[i]==maxn){
                return i;
            }
        }
        return -1;
    }
};
/* 
给你下标从 0 开始、长度为 n 的字符串 pattern ，它包含两种字符，'I' 表示 上升 ，'D' 表示 下降 。

你需要构造一个下标从 0 开始长度为 n + 1 的字符串，且它要满足以下条件：

    num 包含数字 '1' 到 '9' ，其中每个数字 至多 使用一次。
    如果 pattern[i] == 'I' ，那么 num[i] < num[i + 1] 。
    如果 pattern[i] == 'D' ，那么 num[i] > num[i + 1] 。

请你返回满足上述条件字典序 最小 的字符串 num。
 */
class Solution {
public:
    string smallestNumber(string pattern) {
        int n=pattern.size();
        vector<int> temp(n+1);
        
    }
};