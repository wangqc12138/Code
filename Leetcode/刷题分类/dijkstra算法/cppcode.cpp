#include "head.h"
/*
有 n 个城市通过 m 个航班连接。每个航班都从城市 u 开始，以价格 w 抵达 v。
现在给定所有的城市和航班，以及出发城市 src 和目的地 dst，你的任务是找到从 src 到 dst 最多经过 k 站中转的最便宜的价格。
如果没有这样的路线，则输出 -1。
787
*/
class Solution
{
public:
    class Node
    {
    public:
        Node(int c, int s, int w) : city(c), step(s), weight(w){};
        bool operator>(const Node &n) const
        {
            return weight > n.weight;
        }
        int city;
        int step;
        int weight;
    };
    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k)
    {
        unordered_map<int, unordered_map<int, int>> ump;
        for (auto flight : flights)
        {
            ump[flight[0]].emplace(flight[1], flight[2]);
        }
        vector<vector<int>> price(n, vector<int>(k + 2, INT_MAX)); // 每个城市经过a次航班的最小花费
        priority_queue<Node, vector<Node>, greater<Node>> mpq;
        mpq.emplace(Node(src, 0, 0));
        while (!mpq.empty())
        {
            Node node = mpq.top();
            mpq.pop();
            if (node.city == dst)
            {
                return node.weight;
            }
            if (node.step > k)
            {
                continue;
            }
            for (auto [next, cost] : ump[node.city])
            {
                if (price[next][node.step + 1] > node.weight + cost)
                { // 不加会超时！
                    price[next][node.step + 1] = node.weight + cost;
                    mpq.emplace(Node(next, node.step + 1, node.weight + cost));
                }
            }
        }
        return -1;
    }
};

/*
有 n 个网络节点，标记为 1 到 n。
给你一个列表 times，表示信号经过 有向 边的传递时间。 times[i] = (ui, vi, wi)，其中 ui 是源节点，vi 是目标节点， wi 是一个信号从源节点传递到目标节点的时间。
现在，从某个节点 K 发出一个信号。需要多久才能使所有节点都收到信号？如果不能使所有节点收到信号，返回 -1 。
743
把k到每个节点的最短路径算出来，答案=max(l1,l2,l3,...);
*/
class Solution
{
public:
    class Node
    {
    public:
        int cost;
        int node;
        Node(int c, int n) : cost(c), node(n){};
        bool operator>(const Node &n) const
        {
            return cost > n.cost;
        }
    };
    int networkDelayTime(vector<vector<int>> &times, int n, int k)
    {
        unordered_map<int, unordered_map<int, int>> graph;
        vector<int> price(n + 1, INT_MAX);
        for (auto vec : times)
        {
            graph[vec[0]][vec[1]] = vec[2];
        }
        priority_queue<Node, vector<Node>, greater<Node>> mpq;
        mpq.emplace(Node(0, k));
        price[k] = 0;
        while (!mpq.empty())
        {
            Node i = mpq.top();
            mpq.pop();
            for (auto [next, cost] : graph[i.node])
            {
                if (price[next] <= cost + i.cost)
                {
                    continue;
                }
                price[next] = cost + i.cost;
                mpq.emplace(Node(cost + i.cost, next));
            }
        }
        for (int i : price)
        {
            cout << i << " ";
        }
        int res = *max_element(price.begin() + 1, price.end());
        return res == INT_MAX ? -1 : res;
    }
};
/*
由空地和墙组成的迷宫中有一个球。球可以向上下左右四个方向滚动，但在遇到墙壁前不会停止滚动。当球停下时，可以选择下一个方向。
给定球的起始位置，目的地和迷宫，找出让球停在目的地的最短距离。距离的定义是球从起始位置（不包括）到目的地（包括）经过的空地个数。如果球无法停在目的地，返回 -1。
迷宫由一个0和1的二维数组表示。 1表示墙壁，0表示空地。你可以假定迷宫的边缘都是墙壁。起始位置和目的地的坐标通过行号和列号给出。
505
*/
/*
给你一个 R 行 C 列的整数矩阵 A。矩阵上的路径从 [0,0] 开始，在 [R-1,C-1] 结束。
路径沿四个基本方向（上、下、左、右）展开，从一个已访问单元格移动到任一相邻的未访问单元格。
路径的得分是该路径上的 最小 值。例如，路径 8 →  4 →  5 →  9 的值为 4 。
找出所有路径中得分 最高 的那条路径，返回其得分。
1102
*/
/*
给你一个 m * n 的矩阵 mat，以及一个整数 k ，矩阵中的每一行都以非递减的顺序排列。
你可以从每一行中选出 1 个元素形成一个数组。返回所有可能数组中的第 k 个 最小 数组和。
1439
*/
/*
给你一个 m x n 的矩阵，其中的值均为非负整数，代表二维高度图每个单元的高度，请计算图中形状最多能接多少体积的雨水。
407
*/
/*
你准备参加一场远足活动。给你一个二维 rows x columns 的地图 heights ，其中 heights[row][col] 表示格子 (row, col) 的高度。一开始你在最左上角的格子 (0, 0) ，且你希望去最右下角的格子 (rows-1, columns-1) （注意下标从 0 开始编号）。你每次可以往 上，下，左，右 四个方向之一移动，你想要找到耗费 体力 最小的一条路径。
一条路径耗费的 体力值 是路径上相邻格子之间 高度差绝对值 的 最大值 决定的。
请你返回从左上角走到右下角的最小 体力消耗值 。
1631
*/
/*
给定两个以升序排列的整形数组 nums1 和 nums2, 以及一个整数 k。
定义一对值 (u,v)，其中第一个元素来自 nums1，第二个元素来自 nums2。
找到和最小的 k 对数字 (u1,v1), (u2,v2) ... (uk,vk)。
373
*/
/*
在一个 n x n 的整数矩阵 grid 中，每一个方格的值 grid[i][j] 表示位置 (i, j) 的平台高度。

当开始下雨时，在时间为 t 时，水池中的水位为 t 。你可以从一个平台游向四周相邻的任意一个平台，但是前提是此时水位必须同时淹没这两个平台。假定你可以瞬间移动无限距离，也就是默认在方格内部游动是不耗时的。当然，在你游泳的时候你必须待在坐标方格里面。

你从坐标方格的左上平台 (0，0) 出发。返回 你到达坐标方格的右下平台 (n-1, n-1) 所需的最少时间 。
778
*/
/*
欢迎各位勇者来到力扣城，本次试炼主题为「信物传送」。

本次试炼场地设有若干传送带，matrix[i][j] 表示第 i 行 j 列的传送带运作方向，"^","v","<",">" 这四种符号分别表示 上、下、左、右 四个方向。
信物会随传送带的方向移动。勇者每一次施法操作，可临时变更一处传送带的方向，在物品经过后传送带恢复原方向。

通关信物初始位于坐标 start处，勇者需要将其移动到坐标 end 处，请返回勇者施法操作的最少次数。

注意：

    start 和 end 的格式均为 [i,j]
LCP56
 */
using pii = pair<int, int>;
using ppi = pair<pii, int>;
class Solution
{
public:
    vector<vector<int>> dir = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    vector<char> vstr = {'^', 'v', '<', '>'};
    int conveyorBelt(vector<string> &matrix, vector<int> &start, vector<int> &end)
    {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> visit(m, vector<int>(n, 10001));
        auto cmp = [](ppi a, ppi b)
        { return a.second > b.second; };
        priority_queue<ppi, vector<ppi>, decltype(cmp)> mpq(cmp);
        mpq.emplace(ppi({{start[0], start[1]}, 0}));
        visit[start[0]][start[1]] = 0;
        while (!mpq.empty())
        {
            int x = mpq.top().first.first, y = mpq.top().first.second, z = mpq.top().second;
            mpq.pop();
            if (x == end[0] && y == end[1])
            {
                return z;
            }
            for (int k = 0; k < 4; k++)
            {
                int p = (vstr[k] == matrix[x][y]) ? 0 : 1;
                int i = x + dir[k][0], j = y + dir[k][1];
                if (i < 0 || j < 0 || i >= m || j >= n || visit[i][j] <= visit[x][y] + p)
                {
                    continue;
                }
                visit[i][j] = visit[x][y] + p;
                mpq.emplace(ppi({i, j}, visit[i][j]));
            }
        }
        return 0;
    }
};
/*
给你一个 m x n 的网格图 grid 。 grid 中每个格子都有一个数字，对应着从该格子出发下一步走的方向。 grid[i][j] 中的数字可能为以下几种情况：

    1 ，下一步往右走，也就是你会从 grid[i][j] 走到 grid[i][j + 1]
    2 ，下一步往左走，也就是你会从 grid[i][j] 走到 grid[i][j - 1]
    3 ，下一步往下走，也就是你会从 grid[i][j] 走到 grid[i + 1][j]
    4 ，下一步往上走，也就是你会从 grid[i][j] 走到 grid[i - 1][j]

注意网格图中可能会有 无效数字 ，因为它们可能指向 grid 以外的区域。

一开始，你会从最左上角的格子 (0,0) 出发。
我们定义一条 有效路径 为从格子 (0,0) 出发，每一步都顺着数字对应方向走，最终在最右下角的格子 (m - 1, n - 1) 结束的路径。
有效路径 不需要是最短路径 。

你可以花费 cost = 1 的代价修改一个格子中的数字，但每个格子中的数字 只能修改一次 。

请你返回让网格图至少有一条有效路径的最小代价。
1368
 */
using pii = pair<int, int>;
using ppi = pair<pii, int>;
class Solution
{
public:
    vector<vector<int>> dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int minCost(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> visit(m, vector<int>(n, 0));
        auto cmp = [](ppi a, ppi b)
        { return a.second > b.second; };
        priority_queue<ppi, vector<ppi>, decltype(cmp)> mpq(cmp);
        mpq.emplace(ppi({{0, 0}, 0}));
        while (!mpq.empty())
        {
            int x = mpq.top().first.first, y = mpq.top().first.second, z = mpq.top().second;
            mpq.pop();
            if (x == m - 1 && y == n - 1)
            {
                return z;
            }
            if (visit[x][y])
            {
                continue;
            }
            // cout<<x<<" "<<y<<" "<<z<<endl;
            visit[x][y] = 1;
            for (int k = 0; k < 4; k++)
            {
                int p = grid[x][y] == k + 1 ? 0 : 1;
                int i = x + dir[k][0], j = y + dir[k][1];
                if (i < 0 || j < 0 || i >= m || j >= n || visit[i][j])
                {
                    continue;
                }
                mpq.emplace(ppi({{i, j}, z + p}));
            }
        }
        return 0;
    }
};
/*
给你一个下标从 0 开始的二维整数数组 grid ，数组大小为 m x n 。每个单元格都是两个值之一：

    0 表示一个 空 单元格，
    1 表示一个可以移除的 障碍物 。

你可以向上、下、左、右移动，从一个空单元格移动到另一个空单元格。

现在你需要从左上角 (0, 0) 移动到右下角 (m - 1, n - 1) ，返回需要移除的障碍物的 最小 数目。
2290
 */
using pii = pair<int, int>;
using ppi = pair<pii, int>;
class Solution
{
public:
    int minimumObstacles(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> p(m, vector<int>(n, 100001));
        vector<pii> dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        auto cmp = [](auto i, auto j)
        { return i.second > j.second; };
        priority_queue<ppi, vector<ppi>, decltype(cmp)> mpq(cmp);
        p[0][0] = 0;
        mpq.emplace(ppi({{0, 0}, 0}));
        while (!mpq.empty())
        {
            ppi t = mpq.top();
            int x = t.first.first, y = t.first.second, z = t.second;
            mpq.pop();
            if (x == m - 1 && y == n - 1)
            {
                return z;
            }
            for (auto [i, j] : dir)
            {
                if (x + i < 0 || x + i >= m || y + j < 0 || y + j >= n || z + grid[x + i][y + j] >= p[x + i][y + j])
                {
                    continue;
                }
                p[x + i][y + j] = z + grid[x + i][y + j];
                mpq.emplace(ppi({x + i, y + j}, z + grid[x + i][y + j]));
            }
        }
        return 0;
    }
};
/*
给你一个大小为 m x n 的整数矩阵 grid 和一个大小为 k 的数组 queries 。

找出一个大小为 k 的数组 answer ，且满足对于每个整数 queres[i] ，你从矩阵 左上角 单元格开始，重复以下过程：

    如果 queries[i] 严格 大于你当前所处位置单元格，如果该单元格是第一次访问，则获得 1 分，并且你可以移动到所有 4 个方向（上、下、左、右）上任一 相邻 单元格。
    否则，你不能获得任何分，并且结束这一过程。

在过程结束后，answer[i] 是你可以获得的最大分数。注意，对于每个查询，你可以访问同一个单元格 多次 。

返回结果数组 answer 。
2503
 */
using ppi = pair<pair<int, int>, int>;
class Solution
{
public:
    vector<int> maxPoints(vector<vector<int>> &grid, vector<int> &queries)
    {
        auto cmp = [](auto i, auto j)
        { return i.second < j.second; };
        priority_queue<ppi, vector<ppi>, decltype(cmp)> mpq(cmp);
        mpq.emplace(ppi({0, 0}, grid[0][0]));
        int n = queries.size();
        vector<int> index(n), res(n);
        iota(index.begin(), index.end(), 0);
        sort(index.begin(), index.end(), [&](int i, int j)
             { return queries[i] < queries[j]; });
        sort(queries.begin(), queries.end());
        int sum = 0;
        vector<pair<int, int>> dir = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
        for (int i = 0; i < n; i++)
        {
            int t = queries[i];
            while (!mpq.empty() && t > mpq.top().second)
            {
                auto [x, y] = mpq.top().first;
                mpq.pop();
                for (auto [a, b] : dir)
                {
                    if (x + a < 0 || x + a >= grid.size() || y + b < 0 || y + b >= grid[0].size() || grid[x + a][y + b] == 0)
                    {
                        continue;
                    }
                    mpq.emplace(ppi({x + a, y + b}, grid[x + a][y + b]));
                    grid[x + a][y + b] = 0;
                    sum++;
                }
            }
            res[index[i]] = sum;
        }
        return res;
    }
};