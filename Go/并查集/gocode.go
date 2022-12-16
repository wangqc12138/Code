package main

import "sort"

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
type UnionFindSet struct {
	head, size []int
}

func newUnionFindSet(n int) *UnionFindSet {
	ufs := UnionFindSet{}
	ufs.head, ufs.size = make([]int, n), make([]int, n)
	for i := 0; i < n; i++ {
		ufs.head[i] = i
		ufs.size[i] = 1
	}
	return &ufs
}
func (this *UnionFindSet) findHead(i int) int {
	f := this.head[i]
	if f != i {
		f = this.findHead(f)
	}
	this.head[i] = f
	return f
}
func (this *UnionFindSet) isSameSet(i, j int) bool {
	return this.findHead(i) == this.findHead(j)
}
func (this *UnionFindSet) unionSet(i, j int) {
	hi, hj := this.findHead(i), this.findHead(j)
	if hi != hj {
		if this.size[hi] > this.size[hj] {
			this.head[hj] = this.head[hi]
			this.size[hi] += this.size[hj]
		} else {
			this.head[hi] = this.head[hj]
			this.size[hj] += this.size[hi]
		}
	}
}
func isBipartite(graph [][]int) bool {
	n := len(graph)
	ufs := newUnionFindSet(n)
	for i := 0; i < n; i++ {
		for _, j := range graph[i] {
			if ufs.isSameSet(i, j) {
				return false
			}
			ufs.unionSet(graph[i][0], j)
		}
	}
	return true
}

/*
给你一个大小为 m x n 的整数矩阵 grid 和一个大小为 k 的数组 queries 。

找出一个大小为 k 的数组 answer ，且满足对于每个整数 queres[i] ，你从矩阵 左上角 单元格开始，重复以下过程：

    如果 queries[i] 严格 大于你当前所处位置单元格，如果该单元格是第一次访问，则获得 1 分，并且你可以移动到所有 4 个方向（上、下、左、右）上任一 相邻 单元格。
    否则，你不能获得任何分，并且结束这一过程。

在过程结束后，answer[i] 是你可以获得的最大分数。注意，对于每个查询，你可以访问同一个单元格 多次 。

返回结果数组 answer 。
2503
*/
func maxPoints(grid [][]int, queries []int) []int {
	m, n := len(grid), len(grid[0])
	mn := m * n
	head, size, g := make([]int, mn), make([]int, mn), make([][]int, mn)
	for i := 0; i < mn; i++ {
		head[i] = i
		size[i] = 1
		g[i] = []int{grid[i/n][i%n], i / n, i % n}
	}
	var find func(x int) int
	find = func(x int) int {
		if head[x] != x {
			head[x] = find(head[x])
		}
		return head[x]
	}
	res := make([]int, len(queries))
	id := res
	for i := 0; i < len(queries); i++ {
		id[i] = i
	}
	sort.Slice(id, func(i, j int) bool {
		return queries[i] < queries[j]
	})
	sort.Slice(g, func(i, j int) bool {
		return g[i][0] < g[j][0]
	})
	k := 0

	for _, i := range id {
		q := queries[i]
		for ; k < mn && q > grid[g[k][1]][g[k][2]]; k++ {

		}
		res[i] = size[find(0)]
	}
	return res
}
