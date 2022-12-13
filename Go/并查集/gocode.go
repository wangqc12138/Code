package main

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
