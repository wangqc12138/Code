package main

import "sort"

/*
给你一个正整数数组 price ，其中 price[i] 表示第 i 类糖果的价格，另给你一个正整数 k 。

商店组合 k 类 不同 糖果打包成礼盒出售。礼盒的 甜蜜度 是礼盒中任意两种糖果 价格 绝对差的最小值。

返回礼盒的 最大 甜蜜度。
T2517
*/
func maximumTastiness(price []int, k int) int {
	sort.Ints(price)
	left, right := 0, price[0]
	for left < right {

	}
	return left
}
