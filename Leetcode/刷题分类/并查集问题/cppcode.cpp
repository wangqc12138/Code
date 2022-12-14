#include "head.h"
// 并查集问题
/*
n 块石头放置在二维平面中的一些整数坐标点上。每个坐标点上最多只能有一块石头。
如果一块石头的 同行或者同列 上有其他石头存在，那么就可以移除这块石头。
给你一个长度为 n 的数组 stones ，其中 stones[i] = [xi, yi] 表示第 i 块石头的位置，返回 可以移除的石子 的最大数量。
1 <= stones.length <= 1000
0 <= xi, yi <= 104
947
*/
// 将行列坐标视为个体，每个石头的行列则视为同一个集合，最后返回共有多少集合，再用总数减去即为所求
class Solution
{
public:
    int removeStones(vector<vector<int>> &stones)
    {
        UnionFindSet uset;
        uset.makeSet(stones);
        for (auto stone : stones)
        {
            if (!uset.isSameSet(stone[0], stone[1] + 10000))
            {
                uset.unionSet(stone[0], stone[1] + 10000);
            }
        }
        return stones.size() - uset.getCount();
    }

public:
    class UnionFindSet
    {
    public:
        UnionFindSet()
        {
            head.clear();
            size.clear();
            count = 0;
        }
        void makeSet(vector<vector<int>> &stones)
        {
            for (auto stone : stones)
            {
                if (!head.count(stone[0]))
                {
                    head[stone[0]] = stone[0];
                    size[stone[0]] = 1;
                    count++;
                }
                if (!head.count(stone[1] + 10000))
                {
                    head[stone[1] + 10000] = stone[1] + 10000;
                    size[stone[1] + 10000] = 1;
                    count++;
                }
            }
        }
        int findHead(int i)
        {
            int f = head[i];
            if (i != f)
            {
                f = findHead(f);
            }
            head[i] = f;
            return f;
        }
        bool isSameSet(int i, int j)
        {
            return findHead(i) == findHead(j);
        }
        void unionSet(int i, int j)
        {
            int ihead = findHead(i);
            int jhead = findHead(j);
            if (ihead != jhead)
            {
                int isize = size[ihead];
                int jsize = size[jhead];
                if (isize > jsize)
                {
                    head[jhead] = ihead;
                    size[ihead] = isize + jsize;
                }
                else
                {
                    head[ihead] = jhead;
                    size[jhead] = isize + jsize;
                }
                count--;
            }
        }
        int getCount()
        {
            return count;
        }

    private:
        map<int, int> head;
        map<int, int> size;
        int count;
    };
};
/*
给定一个列表 accounts，每个元素 accounts[i] 是一个字符串列表，其中第一个元素 accounts[i][0] 是 名称 (name)，其余元素是 emails 表示该账户的邮箱地址。
现在，我们想合并这些账户。如果两个账户都有一些共同的邮箱地址，则两个账户必定属于同一个人。请注意，即使两个账户具有相同的名称，它们也可能属于不同的人，因为人们可能具有相同的名称。一个人最初可以拥有任意数量的账户，但其所有账户都具有相同的名称。
合并账户后，按以下格式返回账户：每个账户的第一个元素是名称，其余元素是按字符 ASCII 顺序排列的邮箱地址。账户本身可以以任意顺序返回。
721
*/

/*
给你一个points 数组，表示 2D 平面上的一些点，其中 points[i] = [xi, yi] 。
连接点 [xi, yi] 和点 [xj, yj] 的费用为它们之间的 曼哈顿距离 ：|xi - xj| + |yi - yj| ，其中 |val| 表示 val 的绝对值。
请你返回将所有点连接的最小总费用。只有任意两点之间 有且仅有 一条简单路径时，才认为所有点都已连接。
1584
*/

/*
有一个 m x n 的二元网格，其中 1 表示砖块，0 表示空白。砖块 稳定（不会掉落）的前提是：
一块砖直接连接到网格的顶部，或者
至少有一块相邻（4 个方向之一）砖块 稳定 不会掉落时
给你一个数组 hits ，这是需要依次消除砖块的位置。每当消除 hits[i] = (rowi, coli) 位置上的砖块时，对应位置的砖块（若存在）会消失，然后其他的砖块可能因为这一消除操作而掉落。一旦砖块掉落，它会立即从网格中消失（即，它不会落在其他稳定的砖块上）。
返回一个数组 result ，其中 result[i] 表示第 i 次消除操作对应掉落的砖块数目。
注意，消除可能指向是没有砖块的空白位置，如果发生这种情况，则没有砖块掉落。
803
*/

/*
给你一个 n 个点的带权无向连通图，节点编号为 0 到 n-1 ，同时还有一个数组 edges ，其中 edges[i] = [fromi, toi, weighti] 表示在 fromi 和 toi 节点之间有一条带权无向边。最小生成树 (MST) 是给定图中边的一个子集，它连接了所有节点且没有环，而且这些边的权值和最小。
请你找到给定图中最小生成树的所有关键边和伪关键边。如果从图中删去某条边，会导致最小生成树的权值和增加，那么我们就说它是一条关键边。伪关键边则是可能会出现在某些最小生成树中但不会出现在所有最小生成树中的边。
请注意，你可以分别以任意顺序返回关键边的下标和伪关键边的下标。
1489
*/
/*

用以太网线缆将 n 台计算机连接成一个网络，计算机的编号从 0 到 n-1。线缆用 connections 表示，其中 connections[i] = [a, b] 连接了计算机 a 和 b。
网络中的任何一台计算机都可以通过网络直接或者间接访问同一个网络中其他任意一台计算机。
给你这个计算机网络的初始布线 connections，你可以拔开任意两台直连计算机之间的线缆，并用它连接一对未直连的计算机。请你计算并返回使所有计算机都连通所需的最少操作次数。如果不可能，则返回 -1 。
1319
*/
/*
在由 1 x 1 方格组成的 N x N 网格 grid 中，每个 1 x 1 方块由 /、\ 或空格构成。这些字符会将方块划分为一些共边的区域。

（请注意，反斜杠字符是转义的，因此 \ 用 "\\" 表示。）。

返回区域的数目。
959
*/
/*
Alice 和 Bob 共有一个无向图，其中包含 n 个节点和 3  种类型的边：

类型 1：只能由 Alice 遍历。
类型 2：只能由 Bob 遍历。
类型 3：Alice 和 Bob 都可以遍历。
给你一个数组 edges ，其中 edges[i] = [typei, ui, vi] 表示节点 ui 和 vi 之间存在类型为 typei 的双向边。请你在保证图仍能够被 Alice和 Bob 完全遍历的前提下，找出可以删除的最大边数。如果从任何节点开始，Alice 和 Bob 都可以到达所有其他节点，则认为图是可以完全遍历的。

返回可以删除的最大边数，如果 Alice 和 Bob 无法完全遍历图，则返回 -1 。
1579
*/
/*
如果交换字符串 X 中的两个不同位置的字母，使得它和字符串 Y 相等，那么称 X 和 Y 两个字符串相似。如果这两个字符串本身是相等的，那它们也是相似的。

例如，"tars" 和 "rats" 是相似的 (交换 0 与 2 的位置)； "rats" 和 "arts" 也是相似的，但是 "star" 不与 "tars"，"rats"，或 "arts" 相似。

总之，它们通过相似性形成了两个关联组：{"tars", "rats", "arts"} 和 {"star"}。注意，"tars" 和 "arts" 是在同一组中，即使它们并不相似。形式上，对每个组而言，要确定一个单词在组中，只需要这个词和该组中至少一个单词相似。

给你一个字符串列表 strs。列表中的每个字符串都是 strs 中其它所有字符串的一个字母异位词。请问 strs 中有多少个相似字符串组？
839
*/
/*
给你一个变量对数组 equations 和一个实数值数组 values 作为已知条件，其中 equations[i] = [Ai, Bi] 和 values[i] 共同表示等式 Ai / Bi = values[i] 。每个 Ai 或 Bi 是一个表示单个变量的字符串。

另有一些以数组 queries 表示的问题，其中 queries[j] = [Cj, Dj] 表示第 j 个问题，请你根据已知条件找出 Cj / Dj = ? 的结果作为答案。

返回 所有问题的答案 。如果存在某个无法确定的答案，则用 -1.0 替代这个答案。如果问题中出现了给定的已知条件中没有出现的字符串，也需要用 -1.0 替代这个答案。

注意：输入总是有效的。你可以假设除法运算中不会出现除数为 0 的情况，且不存在任何矛盾的结果。
399
*/
/*
684
 */
// 二分图检测
/*
存在一个 无向图 ，图中有 n 个节点。其中每个节点都有一个介于 0 到 n - 1 之间的唯一编号。
给你一个二维数组 graph ，其中 graph[u] 是一个节点数组，由节点 u 的邻接节点组成。
形式上，对于 graph[u] 中的每个 v ，都存在一条位于节点 u 和节点 v 之间的无向边。该无向图同时具有以下属性：

    不存在自环（graph[u] 不包含 u）。
    不存在平行边（graph[u] 不包含重复值）。
    如果 v 在 graph[u] 内，那么 u 也应该在 graph[v] 内（该图是无向图）
    这个图可能不是连通图，也就是说两个节点 u 和 v 之间可能不存在一条连通彼此的路径。

二分图 定义：如果能将一个图的节点集合分割成两个独立的子集 A 和 B ，
并使图中的每一条边的两个节点一个来自 A 集合，一个来自 B 集合，就将这个图称为 二分图 。

如果图是二分图，返回 true ；否则，返回 false 。
785
 */
class UnionFindSet
{
public:
    UnionFindSet()
    {
        head.clear();
        size.clear();
    }
    void makeSet(int n)
    {
        for (int i = 0; i < n; i++)
        {
            head[i] = i;
            size[i] = 1;
        }
    }
    int findHead(int i)
    {
        int f = head[i];
        if (f != i)
        {
            f = findHead(f);
        }
        head[i] = f;
        return f;
    }
    bool isSameSet(int i, int j)
    {
        return findHead(i) == findHead(j);
    }
    void unionSet(int i, int j)
    {
        int headi = findHead(i);
        int headj = findHead(j);
        if (headi != headj)
        {
            int sizei = size[headi];
            int sizej = size[headj];
            if (sizei > sizej)
            {
                head[headj] = headi;
                size[headi] += sizej;
            }
            else
            {
                head[headi] = headj;
                size[headj] += sizei;
            }
        }
    }

private:
    map<int, int> head, size;
};
class Solution
{
public:
    bool isBipartite(vector<vector<int>> &graph)
    {
        int n = graph.size();
        UnionFindSet ufs = UnionFindSet();
        ufs.makeSet(n);
        for (int i = 0; i < n; i++)
        {
            if (graph[i].empty())
            {
                continue;
            }
            for (int j = 1; j < graph[i].size(); j++)
            {
                ufs.unionSet(graph[i][0], graph[i][j]);
            }
            if (ufs.isSameSet(i, graph[i][0]))
            {
                return false;
            }
        }
        return true;
    }
};
/*
给你一个 n 个点组成的无向图边集 edgeList ，其中 edgeList[i] = [ui, vi, disi] 表示点 ui 和点 vi 之间有一条长度为 disi 的边。请注意，两个点之间可能有 超过一条边 。

给你一个查询数组queries ，其中 queries[j] = [pj, qj, limitj] ，
你的任务是对于每个查询 queries[j] ，判断是否存在从 pj 到 qj 的路径，且这条路径上的每一条边都 严格小于 limitj 。

请你返回一个 布尔数组 answer ，其中 answer.length == queries.length ，当 queries[j] 的查询结果为 true 时， answer 第 j 个值为 true ，否则为 false 。
1697
 */
class Solution
{
public:
    class UnionFindSet
    {
    public:
        UnionFindSet(int n)
        {
            for (int i = 0; i < n; i++)
            {
                head[i] = i;
                size[i] = 1;
            }
        }
        int findHead(int i)
        {
            int f = head[i];
            if (f != i)
            {
                f = findHead(f);
            }
            head[i] = f;
            return f;
        }
        bool isSameSet(int i, int j)
        {
            return findHead(i) == findHead(j);
        }
        void unionSet(int i, int j)
        {
            int hi = findHead(i);
            int hj = findHead(j);
            if (hi != hj)
            {
                int si = size[hi];
                int sj = size[hj];
                if (si > sj)
                {
                    head[hj] = hi;
                    size[hi] += size[hj];
                }
                else
                {
                    head[hi] = hj;
                    size[hj] += size[hi];
                }
            }
        }

    private:
        map<int, int> head, size;
    };
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>> &edgeList, vector<vector<int>> &queries)
    {
        for (int i = 0; auto &vec : queries)
        {
            vec.emplace_back(i++);
        }
        sort(queries.begin(), queries.end(), [](vector<int> &i, vector<int> &j)
             { return i[2] < j[2]; });
        sort(edgeList.begin(), edgeList.end(), [](vector<int> &i, vector<int> &j)
             { return i[2] < j[2]; });
        UnionFindSet ufs = UnionFindSet(n);
        int i = 0;
        vector<bool> res(queries.size(), false);
        for (auto &vec : queries)
        {
            int t = vec[2];
            for (; i < edgeList.size() && edgeList[i][2] < t; i++)
            {
                ufs.unionSet(edgeList[i][0], edgeList[i][1]);
            }
            if (ufs.isSameSet(vec[0], vec[1]))
            {
                res[vec[3]] = true;
            }
        }
        return res;
    }
};