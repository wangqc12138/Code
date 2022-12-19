package main

import (
	"sort"
	"strconv"
)

/*
有时候人们会用重复写一些字母来表示额外的感受，比如 "hello" -> "heeellooo", "hi" -> "hiii"。我们将相邻字母都相同的一串字符定义为相同字母组，例如："h", "eee", "ll", "ooo"。

对于一个给定的字符串 S ，如果另一个单词能够通过将一些字母组扩张从而使其和 S 相同，我们将这个单词定义为可扩张的（stretchy）。扩张操作定义如下：选择一个字母组（包含字母 c ），然后往其中添加相同的字母 c 使其长度达到 3 或以上。

例如，以 "hello" 为例，我们可以对字母组 "o" 扩张得到 "hellooo"，但是无法以同样的方法得到 "helloo" 因为字母组 "oo" 长度小于 3。此外，我们可以进行另一种扩张 "ll" -> "lllll" 以获得 "helllllooo"。如果 s = "helllllooo"，那么查询词 "hello" 是可扩张的，因为可以对它执行这两种扩张操作使得 query = "hello" -> "hellooo" -> "helllllooo" = s。

输入一组查询单词，输出其中可扩张的单词数量。
809
*/
func expressiveWords(s string, words []string) int {
	res := 0
	for _, str := range words {
		if help(s, str) {
			res++
		}
	}
	return res
}
func help(s string, t string) bool {
	var m, n int = len(s), len(t)
	var i, j int = 0, 0
	for i < m && j < n {
		c1, c2 := s[i], t[j]
		if c1 != c2 {
			return false
		}
		len1, len2 := 0, 0
		for i < m && s[i] == c1 {
			i++
			len1++
		}
		for j < n && t[j] == c2 {
			j++
			len2++
		}
		if len1 != len2 && (len1 < len2 || len1 < 3) {
			return false
		}
	}
	return i == m && j == n
}

/*
给定数组 nums 和一个整数 k 。我们将给定的数组 nums 分成 最多 k 个相邻的非空子数组 。 分数 由每个子数组内的平均值的总和构成。

注意我们必须使用 nums 数组中的每一个数进行分组，并且分数不一定需要是整数。

返回我们所能得到的最大 分数 是多少。答案误差在 10-6 内被视为是正确的。
813
*/
// func largestSumOfAverages(nums []int, k int) float64 {
// 	n := len(nums)
// 	sum := nums
// 	dp := make([][]float64, n)
// 	println(n)
// 	for i := 0; i < n; i++ {
// 		if i != 0 {
// 			sum[i] += sum[i-1]
// 		}
// 		dp[i] = make([]float64, k+1)
// 		dp[i][1] = float64(sum[i]) / float64(i+1)
// 		fmt.Println(dp[i][1])
// 	}
// 	for t := 2; t <= k; t++ {
// 		for i := 0; i < n; i++ {
// 			for j := 0; j < i; j++ {
// 				dp[i][t] = max(dp[i][t], dp[j][t-1]+float64(sum[i]-sum[j])/float64(i-j))
// 			}
// 		}
// 	}
// 	return dp[n-1][k]
// }
// func max(i, j float64) float64 {
// 	if i >= j {
// 		return i
// 	}
// 	return j
// }

/*
给你一个仅由字符 '0' 和 '1' 组成的字符串 s 。一步操作中，你可以将任一 '0' 变成 '1' ，或者将 '1' 变成 '0' 。

交替字符串 定义为：如果字符串中不存在相邻两个字符相等的情况，那么该字符串就是交替字符串。例如，字符串 "010" 是交替字符串，而字符串 "0100" 不是。

返回使 s 变成 交替字符串 所需的 最少 操作数。
*/
// func minOperations(s string) int {
// 	cnt := 0
// 	for i, c := range s {
// 		if int(c-'0') == i%2 {
// 			cnt++
// 		}
// 	}
// 	if cnt < len(s)-cnt {
// 		return cnt
// 	}
// 	return len(s) - cnt
// }

/*
设计一个类似堆栈的数据结构，将元素推入堆栈，并从堆栈中弹出出现频率最高的元素。

实现 FreqStack 类:

    FreqStack() 构造一个空的堆栈。
    void push(int val) 将一个整数 val 压入栈顶。
    int pop() 删除并返回堆栈中出现频率最高的元素。
        如果出现频率最高的元素不只一个，则移除并返回最接近栈顶的元素。
895
*/
// type Node struct {
// 	cnt, index, val int
// }
// type hp []Node
// type FreqStack struct {
// 	cnt   map[int]int
// 	h     hp
// 	index int
// }

// func Constructor() FreqStack {
// 	return FreqStack{map[int]int{}, hp{}, 0}
// }

// func (this *FreqStack) Push(val int) {
// 	this.cnt[val]++
// 	this.index++
// 	heap.Push(&this.h, Node{this.cnt[val], this.index, val})
// }

// func (this *FreqStack) Pop() int {
// 	val := heap.Pop(&this.h).(Node).val
// 	this.cnt[val]--
// 	return val
// }
// func (h hp) Len() int { return len(h) }
// func (h hp) Less(i, j int) bool {
// 	return h[i].cnt > h[j].cnt || h[i].cnt == h[j].cnt && h[i].index > h[j].index
// }
// func (h hp) Swap(i, j int)       { h[i], h[j] = h[j], h[i] }
// func (h *hp) Push(v interface{}) { *h = append(*h, v.(Node)) }
// func (h *hp) Pop() interface{}   { a := *h; v := a[len(a)-1]; *h = a[:len(a)-1]; return v }

// 不使用优先队列
type FreqStack struct {
	cnt  map[int]int
	data map[int][]int
	m    int
}

func Constructor() FreqStack {
	return FreqStack{map[int]int{}, map[int][]int{}, 0}
}

func (this *FreqStack) Push(val int) {
	this.cnt[val]++
	this.m = max(this.m, this.cnt[val])
	this.data[this.cnt[val]] = append(this.data[this.cnt[val]], val)
}

func (this *FreqStack) Pop() int {
	res := this.data[this.m][len(this.data[this.m])-1]
	this.cnt[res]--
	this.data[this.m] = this.data[this.m][:len(this.data[this.m])-1]
	if len(this.data[this.m]) == 0 {
		this.m--
	}
	return res
}
func max(x, y int) int {
	if x > y {
		return x
	}
	return y
}

/**
 * Your FreqStack object will be instantiated and called as such:
 * obj := Constructor();
 * obj.Push(val);
 * param_2 := obj.Pop();
 */
/*
给你两个整数 x 和 y ，表示你在一个笛卡尔坐标系下的 (x, y) 处。同时，在同一个坐标系下给你一个数组 points ，其中 points[i] = [ai, bi] 表示在 (ai, bi) 处有一个点。当一个点与你所在的位置有相同的 x 坐标或者相同的 y 坐标时，我们称这个点是 有效的 。

请返回距离你当前位置 曼哈顿距离 最近的 有效 点的下标（下标从 0 开始）。如果有多个最近的有效点，请返回下标 最小 的一个。如果没有有效点，请返回 -1 。

两个点 (x1, y1) 和 (x2, y2) 之间的 曼哈顿距离 为 abs(x1 - x2) + abs(y1 - y2) 。
1779
*/
func nearestValidPoint(x int, y int, points [][]int) int {
	res := -1
	len := 10000
	abs := func(x int) int {
		if x < 0 {
			return -x
		}
		return x
	}
	for i, p := range points {
		if p[0] == x || p[1] == y {
			if abs(p[0]-x)+abs(p[1]-y) < len {
				res = i
			}
		}
	}
	return res
}

/*

有 n 个盒子。给你一个长度为 n 的二进制字符串 boxes ，其中 boxes[i] 的值为 '0' 表示第 i 个盒子是 空 的，而 boxes[i] 的值为 '1' 表示盒子里有 一个 小球。

在一步操作中，你可以将 一个 小球从某个盒子移动到一个与之相邻的盒子中。第 i 个盒子和第 j 个盒子相邻需满足 abs(i - j) == 1 。
注意，操作执行后，某些盒子中可能会存在不止一个小球。

返回一个长度为 n 的数组 answer ，其中 answer[i] 是将所有小球移动到第 i 个盒子所需的 最小 操作数。

每个 answer[i] 都需要根据盒子的 初始状态 进行计算。
1769
*/
// func minOperations(boxes string) []int {
// 	n, t, p := len(boxes), 0, 0
// 	sum := make([]int, n)
// 	if boxes[0] == '1' {
// 		sum[0] = 1
// 	}
// 	for i := 1; i < n; i++ {
// 		sum[i] = sum[i-1]
// 		if boxes[i] == '1' {
// 			sum[i]++
// 			t += i
// 		}
// 	}
// 	res := make([]int, n)
// 	for i := 0; i < n; i++ {
// 		res[i] = p + t
// 		p += sum[i]
// 		t -= sum[n-1] - sum[i]
// 	}
// 	return res
// }
/*
给你两个长度可能不等的整数数组 nums1 和 nums2 。两个数组中的所有值都在 1 到 6 之间（包含 1 和 6）。

每次操作中，你可以选择 任意 数组中的任意一个整数，将它变成 1 到 6 之间 任意 的值（包含 1 和 6）。

请你返回使 nums1 中所有数的和与 nums2 中所有数的和相等的最少操作次数。如果无法使两个数组的和相等，请返回 -1 。
1775
*/
func minOperations_help(v1, v2 []int, diff int) int {
	vec := make([]int, 7)
	for i := 1; i <= 6; i++ {
		vec[i] = v1[i] + v2[7-i]
	}
	res := 0
	for i := 1; i <= 6; i++ {
		if diff <= vec[i]*(6-i) {
			res += (diff + 5 - i) / (6 - i)
			diff = 0
			break
		} else {
			res += vec[i]
			diff -= vec[i] * (6 - i)
		}
	}
	if diff > 0 {
		res = -1
	}
	return res
}
func minOperations(nums1, nums2 []int) int {
	v1, v2, s1, s2 := make([]int, 7), make([]int, 7), 0, 0
	for _, i := range nums1 {
		v1[i]++
		s1 += i
	}
	for _, i := range nums2 {
		v2[i]++
		s2 += i
	}
	if s1 < s2 {
		return minOperations_help(v1, v2, s2-s1)
	}
	return minOperations_help(v2, v1, s1-s2)
}

/*
一个字符串的 美丽值 定义为：出现频率最高字符与出现频率最低字符的出现次数之差。

    比方说，"abaacc" 的美丽值为 3 - 1 = 2 。

给你一个字符串 s ，请你返回它所有子字符串的 美丽值 之和。
1781
*/
func beautySum(s string) int {
	res := 0
	for i := 0; i < len(s); i++ {
		cnt := make(map[byte]int)
		for j := i; j < len(s); j++ {
			cnt[s[j]]++
			maxn, minn := 0, len(s)
			for _, y := range cnt {
				if y > maxn {
					maxn = y
				}
				if y < minn {
					minn = y
				}
			}
			res += maxn - minn
		}
	}
	return res
}

/*
给你一个 n 个点组成的无向图边集 edgeList ，其中 edgeList[i] = [ui, vi, disi] 表示点 ui 和点 vi 之间有一条长度为 disi 的边。请注意，两个点之间可能有 超过一条边 。

给你一个查询数组queries ，其中 queries[j] = [pj, qj, limitj] ，
你的任务是对于每个查询 queries[j] ，判断是否存在从 pj 到 qj 的路径，且这条路径上的每一条边都 严格小于 limitj 。

请你返回一个 布尔数组 answer ，其中 answer.length == queries.length ，当 queries[j] 的查询结果为 true 时， answer 第 j 个值为 true ，否则为 false 。
1697
*/
func distanceLimitedPathsExist(n int, edgeList [][]int, queries [][]int) []bool {
	head, size := make(map[int]int), make((map[int]int))
	for i := 0; i < n; i++ {
		head[i] = i
		size[i] = 1
	}
	var findHead func(i int) int
	findHead = func(x int) int {
		if head[x] != x {
			head[x] = findHead(head[x])
		}
		return head[x]
	}
	isSameSet := func(i, j int) bool {
		return findHead(i) == findHead(j)
	}
	unionSet := func(i, j int) {
		hi, hj := findHead(i), findHead(j)
		if hi != hj {
			if size[hi] > size[hj] {
				head[hj] = hi
				size[hi] += size[hj]
			} else {
				head[hi] = hj
				size[hj] += size[hi]
			}
		}
	}
	res := make([]bool, len(queries))
	sort.Slice(edgeList, func(i, j int) bool { return edgeList[i][2] < edgeList[j][2] })
	for i := range queries {
		queries[i] = append(queries[i], i)
	}
	sort.Slice(queries, func(i, j int) bool { return queries[i][2] < queries[j][2] })
	i := 0

	for _, vec := range queries {
		t := vec[2]
		for ; i < len(edgeList) && edgeList[i][2] < t; i++ {
			unionSet(edgeList[i][0], edgeList[i][1])
		}
		res[vec[3]] = isSameSet(vec[0], vec[1])
	}
	return res
}

/*
给你一个由小写字母组成的字符串 s ，以及一个整数 k 。

首先，用字母在字母表中的位置替换该字母，将 s 转化 为一个整数（也就是，'a' 用 1 替换，'b' 用 2 替换，... 'z' 用 26 替换）。接着，将整数 转换 为其 各位数字之和 。共重复 转换 操作 k 次 。

例如，如果 s = "zbax" 且 k = 2 ，那么执行下述步骤后得到的结果是整数 8 ：

    转化："zbax" ➝ "(26)(2)(1)(24)" ➝ "262124" ➝ 262124
    转换 #1：262124 ➝ 2 + 6 + 2 + 1 + 2 + 4 ➝ 17
    转换 #2：17 ➝ 1 + 7 ➝ 8

返回执行上述操作后得到的结果整数。
1945
*/
func getLucky(s string, k int) int {
	for i := 0; i < k; i++ {
		t := 0
		for _, ch := range s {
			if i == 0 {
				temp := int(ch - 'a' + 1)
				t += temp % 10
				t += temp / 10
			} else {
				t += int(ch - '0')
			}

		}
		s = strconv.Itoa(t)
	}
	res, _ := strconv.Atoi(s)
	return res
}

/*
给你一个整数数组 nums ，和两个整数 limit 与 goal 。数组 nums 有一条重要属性：abs(nums[i]) <= limit 。

返回使数组元素总和等于 goal 所需要向数组中添加的 最少元素数量 ，添加元素 不应改变 数组中 abs(nums[i]) <= limit 这一属性。

注意，如果 x >= 0 ，那么 abs(x) 等于 x ；否则，等于 -x 。
1785
*/
func minElements(nums []int, limit int, goal int) int {
	t := 0
	for _, i := range nums {
		t += i
	}
	abs := func(x int) int {
		if x < 0 {
			return -x
		}
		return x
	}
	return (abs(t-goal) + limit - 1) / limit
}

/*
有一个具有 n 个顶点的 双向 图，其中每个顶点标记从 0 到 n - 1（包含 0 和 n - 1）。图中的边用一个二维整数数组 edges 表示，其中 edges[i] = [ui, vi] 表示顶点 ui 和顶点 vi 之间的双向边。 每个顶点对由 最多一条 边连接，并且没有顶点存在与自身相连的边。

请你确定是否存在从顶点 source 开始，到顶点 destination 结束的 有效路径 。

给你数组 edges 和整数 n、source 和 destination，如果从 source 到 destination 存在 有效路径 ，则返回 true，否则返回 false 。
1971
*/
//bfs
// func validPath(n int, edges [][]int, source int, destination int) bool {
// 	queue, visit := []int{}, make([]int, n)
// 	queue = append(queue, source)
// 	visit[source] = 1
// 	next := make(map[int][]int)
// 	for _, vec := range edges {
// 		next[vec[0]] = append(next[vec[0]], vec[1])
// 		next[vec[1]] = append(next[vec[1]], vec[1])
// 	}
// 	for len(queue) > 0 {
// 		now := queue[0]
// 		queue = queue[1:]
// 		if now == destination {
// 			return true
// 		}
// 		for _, i := range next[now] {
// 			if visit[i] == 0 {
// 				visit[i] = 1
// 				queue = append(queue, i)
// 			}
// 		}
// 	}
// 	return false
// }

//dfs
// func validPath(n int, edges [][]int, source int, destination int) bool {
// 	next, visit := make([][]int, n), make([]int, n)
// 	for _, e := range edges {
// 		x, y := e[0], e[1]
// 		next[x] = append(next[x], y)
// 		next[y] = append(next[y], x)
// 	}
// 	var dfs func(int) bool
// 	dfs = func(i int) bool {
// 		if i == destination {
// 			return true
// 		}
// 		visit[i] = 1
// 		for _, t := range next[i] {
// 			if visit[t] == 0 && dfs(t) {
// 				return true
// 			}
// 		}
// 		return false
// 	}
// 	return dfs(source)
// }

//ufs
func validPath(n int, edges [][]int, source int, destination int) bool {
	head := make([]int, n)
	for i := 0; i < n; i++ {
		head[i] = i
	}
	var find func(int) int
	find = func(i int) int {
		if i != head[i] {
			head[i] = find(head[i])
		}
		return head[i]
	}
	connect := func(i, j int) {
		head[find(i)] = find(j)
	}
	for _, e := range edges {
		x, y := e[0], e[1]
		connect(x, y)
	}
	return find(source) == find(destination)
}
