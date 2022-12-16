#include "head.h"
/* 
一个 平方和三元组 (a,b,c) 指的是满足 a2 + b2 = c2 的 整数 三元组 a，b 和 c 。

给你一个整数 n ，请你返回满足 1 <= a, b, c <= n 的 平方和三元组 的数目。
 */
class Solution {
public:
    int countTriples(int n) {
        int res=0;
        for(int i=1;i<n;i++){
            for(int j=1;j<n;j++){
                if(i==j){
                    continue;
                }
                int k=pow(i,2)+pow(j,2);
                if(k<=pow(n,2)&&sqrt(k)==int(sqrt(k))){
                    res++;
                }
            }
        }
        return res;
    }
};
/* 
给你一个 m x n 的迷宫矩阵 maze （下标从 0 开始），矩阵中有空格子（用 '.' 表示）和墙（用 '+' 表示）。
同时给你迷宫的入口 entrance ，用 entrance = [entrancerow, entrancecol] 表示你一开始所在格子的行和列。

每一步操作，你可以往 上，下，左 或者 右 移动一个格子。你不能进入墙所在的格子，你也不能离开迷宫。
你的目标是找到离 entrance 最近 的出口。出口 的含义是 maze 边界 上的 空格子。entrance 格子 不算 出口。

请你返回从 entrance 到最近出口的最短路径的 步数 ，如果不存在这样的路径，请你返回 -1 。
 */
class Solution {
public:
    vector<pair<int,int>> dir={{0,1},{1,0},{0,-1},{-1,0}};
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int m=maze.size(),n=maze[0].size();
        queue<pair<int,int>> mq;
        mq.emplace(entrance[0],entrance[1]);
        maze[entrance[0]][entrance[1]]='#';
        int res=0;
        while(!mq.empty()){
            int len=mq.size();
            for(int i=0;i<len;i++){
                int x=mq.front().first;
                int y=mq.front().second;
                mq.pop();
                if(maze[x][y]=='.'&&x==m-1||y==n-1){
                    return res;
                }
                for(auto [c,d]:dir){
                    int a=c+x;
                    int b=d+y;
                    if(a<0||a>=m||b<0||b>=n||maze[a][b]!='.'){
                        continue;
                    }
                    maze[a][b]='#';
                    mq.emplace(a,b);
                }
            }
            res++;
        }
        return -1;
    }
};
/* 
Alice 和 Bob 玩一个游戏，两人轮流行动，Alice 先手 。

给你一个 偶数长度 的字符串 num ，每一个字符为数字字符或者 '?' 。每一次操作中，如果 num 中至少有一个 '?' ，那么玩家可以执行以下操作：

选择一个下标 i 满足 num[i] == '?' 。
将 num[i] 用 '0' 到 '9' 之间的一个数字字符替代。
当 num 中没有 '?' 时，游戏结束。

Bob 获胜的条件是 num 中前一半数字的和 等于 后一半数字的和。Alice 获胜的条件是前一半的和与后一半的和 不相等 。

比方说，游戏结束时 num = "243801" ，那么 Bob 获胜，因为 2+4+3 = 8+0+1 。如果游戏结束时 num = "243803" ，那么 Alice 获胜，因为 2+4+3 != 8+0+3 。
在 Alice 和 Bob 都采取 最优 策略的前提下，如果 Alice 获胜，请返回 true ，如果 Bob 获胜，请返回 false 。
 */
class Solution {
public:
    bool sumGame(string num) {
        int m=0,n=0,len=num.size();
        int sum1=0,sum2=0;
        for(int i=0;i<len;i++){
            if(i<len/2){
                if(num[i]=='?'){
                    ++m;
                }else{
                    sum1+=num[i]-'0';
                }
            }else{
                if(num[i]=='?'){
                    ++n;
                }else{
                    sum2+=num[i]-'0';
                }
            }
        }
        if(sum1==sum2){
            if(m==n){
                return false;
            }else{
                return true;
            }
        }else{
            
        }
    }
};

/* 
一个国家有 n 个城市，城市编号为 0 到 n - 1 ，题目保证 所有城市 都由双向道路 连接在一起 。
道路由二维整数数组 edges 表示，其中 edges[i] = [xi, yi, timei] 表示城市 xi 和 yi 之间有一条双向道路，耗费时间为 timei 分钟。两个城市之间可能会有多条耗费时间不同的道路，但是不会有道路两头连接着同一座城市。

每次经过一个城市时，你需要付通行费。通行费用一个长度为 n 且下标从 0 开始的整数数组 passingFees 表示，其中 passingFees[j] 是你经过城市 j 需要支付的费用。

一开始，你在城市 0 ，你想要在 maxTime 分钟以内 （包含 maxTime 分钟）到达城市 n - 1 。旅行的 费用 为你经过的所有城市 通行费之和 （包括 起点和终点城市的通行费）。

给你 maxTime，edges 和 passingFees ，请你返回完成旅行的 最小费用 ，如果无法在 maxTime 分钟以内完成旅行，请你返回 -1 。
 */
class Solution {
public:
    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        
    }
};
class Solution {
public:
	class Node {
        public:
        int city;
        int cost;
        int step;
        Node(int city, int cost, int step) {
            this->city = city;
            this->cost = cost;
            this->step = step;
        }
        bool operator < (const Node &a)const{
        	return cost>a.cost;
        }
    };
    int minCost(int K, vector<vector<int>>& flights, vector<int>& passingFees) {
        int src=0,n=passingFees.size(),dst=n-1;
        map<int, map<int, int>> graph;
        priority_queue<Node> pq;
        for(int i = 0; i < flights.size(); i++) {
            graph[flights[i][0]][flights[i][1]]=passingFees[i];
        }
        Node inode=Node(src, 0, K + 1);
        pq.push(inode);
        
        while(!pq.empty()) {
            Node node = pq.top();
            pq.pop();
            if(node.city == dst) {
                return node.cost;
            }
            if(node.step > 0) {
                if(graph.count(node.city)) {
                    for(auto &[neighbor,cost] : graph[node.city]) {
                    	inode=Node(neighbor, node.cost + cost, node.step - 1);
                        pq.push(inode);
                    }
                }
            }
        }
        return -1;
    }
};