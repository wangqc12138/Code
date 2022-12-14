from typing import List
""" 
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
"""


class Solution:
    def isBipartite(self, graph: List[List[int]]) -> bool:
        n = len(graph)
        head = [i for i in range(0, n)]
        size = [1]*n

        def findHead(i: int) -> int:
            f = head[i]
            if f != i:
                f = findHead(f)
            head[i] = f
            return f

        def unionSet(i, j: int):
            hi, hj = findHead(i), findHead(j)
            if hi != hj:
                if size[hi] > size[hj]:
                    head[hj] = hi
                    size[hi] += size[hj]
                else:
                    head[hi] = hj
                    size[hj] += size[hi]

        def isSameSet(i, j: int) -> bool:
            return findHead(i) == findHead(j)

        for i in range(0, n):
            for j in graph[i]:
                if (isSameSet(i, j)):
                    return False
                unionSet(j, graph[i][0])
        return True


""" 
给你一个 n 个点组成的无向图边集 edgeList ，其中 edgeList[i] = [ui, vi, disi] 表示点 ui 和点 vi 之间有一条长度为 disi 的边。请注意，两个点之间可能有 超过一条边 。

给你一个查询数组queries ，其中 queries[j] = [pj, qj, limitj] ，你的任务是对于每个查询 queries[j] ，判断是否存在从 pj 到 qj 的路径，且这条路径上的每一条边都 严格小于 limitj 。

请你返回一个 布尔数组 answer ，其中 answer.length == queries.length ，当 queries[j] 的查询结果为 true 时， answer 第 j 个值为 true ，否则为 false 。
1697

 """
""" 
给你一个大小为 m x n 的整数矩阵 grid 和一个大小为 k 的数组 queries 。

找出一个大小为 k 的数组 answer ，且满足对于每个整数 queres[i] ，你从矩阵 左上角 单元格开始，重复以下过程：

    如果 queries[i] 严格 大于你当前所处位置单元格，如果该单元格是第一次访问，则获得 1 分，并且你可以移动到所有 4 个方向（上、下、左、右）上任一 相邻 单元格。
    否则，你不能获得任何分，并且结束这一过程。

在过程结束后，answer[i] 是你可以获得的最大分数。注意，对于每个查询，你可以访问同一个单元格 多次 。

返回结果数组 answer 。
2503
 """


class Solution:
    def maxPoints(self, grid: List[List[int]], queries: List[int]) -> List[int]:
        