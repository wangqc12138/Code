#include "head.h"
/*
树是一个无向图，其中任何两个顶点只通过一条路径连接。 换句话说，一个任何没有简单环路的连通图都是一棵树。

给你一棵包含 n 个节点的树，标记为 0 到 n - 1 。给定数字 n 和一个有 n - 1 条无向边的 edges 列表（每一个边都是一对标签），其中 edges[i] = [ai, bi] 表示树中节点 ai 和 bi 之间存在一条无向边。

可选择树中任何一个节点作为根。当选择节点 x 作为根节点时，设结果树的高度为 h 。在所有可能的树中，具有最小高度的树（即，min(h)）被称为 最小高度树 。

请你找到所有的 最小高度树 并按 任意顺序 返回它们的根节点标签列表。
树的 高度 是指根节点和叶子节点之间最长向下路径上边的数量。
310
 */
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
    }
};
/*
给你一个 n 个节点的无向无根图，节点编号为 0 到 n - 1 。给你一个整数 n 和一个长度为 n - 1 的二维整数数组 edges ，其中 edges[i] = [ai, bi] 表示树中节点 ai 和 bi 之间有一条边。

每个节点都有一个价值。给你一个整数数组 price ，其中 price[i] 是第 i 个节点的价值。

一条路径的 价值和 是这条路径上所有节点的价值之和。

你可以选择树中任意一个节点作为根节点 root 。选择 root 为根的 开销 是以 root 为起点的所有路径中，价值和 最大的一条路径与最小的一条路径的差值。

请你返回所有节点作为根节点的选择中，最大 的 开销 为多少。
2538
 */
class Solution {
public:
    long long maxOutput(int n, vector<vector<int>>& edges, vector<int>& price) {
    }
};
/*
给定一个无向、连通的树。树中有 n 个标记为 0...n-1 的节点以及 n-1 条边 。

给定整数 n 和数组 edges ， edges[i] = [ai, bi]表示树中的节点 ai 和 bi 之间有一条边。

返回长度为 n 的数组 answer ，其中 answer[i] 是树中第 i 个节点与所有其他节点之间的距离之和。
834
 */
class Solution {
public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
    }
};
/*
Alice 有一棵 n 个节点的树，节点编号为 0 到 n - 1 。树用一个长度为 n - 1 的二维整数数组 edges 表示，其中 edges[i] = [ai, bi] ，表示树中节点 ai 和 bi 之间有一条边。

Alice 想要 Bob 找到这棵树的根。她允许 Bob 对这棵树进行若干次 猜测 。每一次猜测，Bob 做如下事情：

    选择两个 不相等 的整数 u 和 v ，且树中必须存在边 [u, v] 。
    Bob 猜测树中 u 是 v 的 父节点 。

Bob 的猜测用二维整数数组 guesses 表示，其中 guesses[j] = [uj, vj] 表示 Bob 猜 uj 是 vj 的父节点。

Alice 非常懒，她不想逐个回答 Bob 的猜测，只告诉 Bob 这些猜测里面 至少 有 k 个猜测的结果为 true 。

给你二维整数数组 edges ，Bob 的所有猜测和整数 k ，请你返回可能成为树根的 节点数目 。如果没有这样的树，则返回 0。
2581
 */
class Solution {
public:
    int rootCount(vector<vector<int>>& edges, vector<vector<int>>& guesses, int k) {
    }
};