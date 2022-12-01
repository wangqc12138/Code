package main

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
func minOperations(s string) int {
	cnt := 0
	for i, c := range s {
		if int(c-'0') == i%2 {
			cnt++
		}
	}
	if cnt < len(s)-cnt {
		return cnt
	}
	return len(s) - cnt
}

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
	for i, p := range points {
		if p[0] == x || p[1] == y {
			if abs(p[0]-x)+abs(p[1]-y) < len {
				res = i
			}
		}
	}
	return res
}
func abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}
