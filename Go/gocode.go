package main

import "fmt"

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
func largestSumOfAverages(nums []int, k int) float64 {
	n := len(nums)
	sum := nums
	dp := make([][]float64, n)
	println(n)
	for i := 0; i < n; i++ {
		if i != 0 {
			sum[i] += sum[i-1]
		}
		dp[i] = make([]float64, k+1)
		dp[i][1] = float64(sum[i]) / float64(i+1)
		fmt.Println(dp[i][1])
	}
	for t := 2; t <= k; t++ {
		for i := 0; i < n; i++ {
			for j := 0; j < i; j++ {
				dp[i][t] = max(dp[i][t], dp[j][t-1]+float64(sum[i]-sum[j])/float64(i-j))
			}
		}
	}
	return dp[n-1][k]
}
func max(i, j float64) float64 {
	if i >= j {
		return i
	}
	return j
}

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
