package main

/*
给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。

你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。

返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。
交易1次！
*/
// func maxProfit(prices []int) int {
// 	max := func(a, b int) int {
// 		if a > b {
// 			return a
// 		} else {
// 			return b
// 		}
// 	}
// 	n := len(prices)
// 	dp := make([][]int, n)
// 	for i := range dp {
// 		dp[i] = make([]int, 2)
// 	}
// 	dp[0][1] = -prices[0]
// 	dp[0][0] = 0
// 	for i := 1; i < n; i++ {
// 		dp[i][1] = max(dp[i-1][1], -prices[i])
// 		dp[i][0] = max(dp[i-1][0], dp[i-1][1]+prices[i])
// 	}
// 	return dp[n-1][0]
// }
/*
给你一个整数数组 prices ，其中 prices[i] 表示某支股票第 i 天的价格。

在每一天，你可以决定是否购买和/或出售股票。你在任何时候 最多 只能持有 一股 股票。你也可以先购买，然后在 同一天 出售。

返回 你能获得的 最大 利润 。
122
*/
// func maxProfit(prices []int) int {
// 	max := func(a, b int) int {
// 		if a > b {
// 			return a
// 		} else {
// 			return b
// 		}
// 	}
// 	n := len(prices)
// 	dp := make([][]int, n)
// 	for i := range dp {
// 		dp[i] = make([]int, 2)
// 	}
// 	dp[0][1] = -prices[0]
// 	dp[0][0] = 0
// 	for i := 1; i < n; i++ {
// 		dp[i][1] = max(dp[i-1][1], dp[i-1][0]-prices[i])
// 		dp[i][0] = max(dp[i-1][0], dp[i-1][1]+prices[i])
// 	}
// 	return dp[n-1][0]
// }
/*
给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
123
*/
// func maxProfit(prices []int) int {
// 	max := func(a, b int) int {
// 		if a > b {
// 			return a
// 		} else {
// 			return b
// 		}
// 	}
// 	n := len(prices)
// 	dp := make([][2][3]int, n)
// 	dp[0][1][1] = -prices[0]
// 	dp[0][1][2] = -prices[0]
// 	for i := 1; i < n; i++ {
// 		dp[i][1][1] = max(dp[i-1][1][1], -prices[i])
// 		dp[i][1][2] = max(dp[i-1][1][2], dp[i-1][0][1]-prices[i])
// 		dp[i][0][1] = max(dp[i-1][0][1], dp[i-1][1][1]+prices[i])
// 		dp[i][0][2] = max(dp[i-1][0][2], dp[i-1][1][2]+prices[i])
// 	}
// 	return max(dp[n-1][0][1], dp[n-1][0][2])
// }
/*
给定一个整数数组 prices ，它的第 i 个元素 prices[i] 是一支给定的股票在第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
188
*/
// func maxProfit(k int, prices []int) int {
// 	max := func(a, b int) int {
// 		if a > b {
// 			return a
// 		} else {
// 			return b
// 		}
// 	}
// 	n := len(prices)
// 	dp := make([][2][]int, n)
// }
