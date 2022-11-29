import imp
from typing import List
# 给你一个字符串 s，请你返回 两个相同字符之间的最长子字符串的长度 ，计算长度时不含这两个字符。如果不存在这样的子字符串，返回 -1 。

# 子字符串 是字符串中的一个连续字符序列。
# 1624


class Solution:
    def maxLengthBetweenEqualCharacters(self, s: str) -> int:
        dict = {}
        res = -1
        for i, c in enumerate(s):
            if c in dict:
                res = max(res, i-dict[c]-1)
            else:
                dict[c] = i
        return res


# 给你一个大小为 n x n 二进制矩阵 grid 。最多 只能将一格 0 变成 1 。

# 返回执行此操作后，grid 中最大的岛屿面积是多少？

# 岛屿 由一组上、下、左、右四个方向相连的 1 形成。
# 827


class Solution:
    dir = [(-1, 0), (0, 1), (1, 0), (0, -1)]

    def largestIsland(self, grid: List[List[int]]) -> int:
        res = 0

        # def dfs(self, grid: List[List[int]], index: int, i: int, j: int, m: int, n: int) -> int:
        #     if i < 0 or j < 0 or i >= m or j >= n or grid[i][j] != 1:
        #         return 0
        #     grid[i][j] = index
        #     S = 1
        #     for x, y in dir:
        #         S += dfs(grid, index, i+x, y+j, m, n)
        #     return S
        return res

    def dfs(self, grid: List[List[int]], index: int, i: int, j: int, m: int, n: int) -> int:
        if i < 0 or j < 0 or i >= m or j >= n or grid[i][j] != 1:
            return 0
        grid[i][j] = index
        S = 1
        for x, y in dir:
            S += self.dfs(grid, index, i+x, y+j, m, n)
        return S


""" 
有时候人们会用重复写一些字母来表示额外的感受，比如 "hello" -> "heeellooo", "hi" -> "hiii"。我们将相邻字母都相同的一串字符定义为相同字母组，例如："h", "eee", "ll", "ooo"。

对于一个给定的字符串 S ，如果另一个单词能够通过将一些字母组扩张从而使其和 S 相同，我们将这个单词定义为可扩张的（stretchy）。扩张操作定义如下：选择一个字母组（包含字母 c ），然后往其中添加相同的字母 c 使其长度达到 3 或以上。

例如，以 "hello" 为例，我们可以对字母组 "o" 扩张得到 "hellooo"，但是无法以同样的方法得到 "helloo" 因为字母组 "oo" 长度小于 3。此外，我们可以进行另一种扩张 "ll" -> "lllll" 以获得 "helllllooo"。如果 s = "helllllooo"，那么查询词 "hello" 是可扩张的，因为可以对它执行这两种扩张操作使得 query = "hello" -> "hellooo" -> "helllllooo" = s。

输入一组查询单词，输出其中可扩张的单词数量。
 """


class Solution:
    def expressiveWords(self, s: str, words: List[str]) -> int:
        def check(s: str, t: str) -> bool:
            i = j = 0
            m = len(s)
            n = len(t)
            while i < m and j < n:
                c1 = s[i]
                c2 = t[j]
                if c1 != c2:
                    return False
                len1 = len2 = 0
                while i < m and s[i] == c1:
                    len1 += 1
                    i += 1
                while j < n and t[j] == c2:
                    len2 += 1
                    j += 1
                if len1 != len2 and (len1 < 3 or len2 > len1):
                    return False
            return i == m and j == n
        res = sum(int(check(s, t)) for t in words)
        return res


""" 
给定数组 nums 和一个整数 k 。我们将给定的数组 nums 分成 最多 k 个相邻的非空子数组 。 分数 由每个子数组内的平均值的总和构成。

注意我们必须使用 nums 数组中的每一个数进行分组，并且分数不一定需要是整数。

返回我们所能得到的最大 分数 是多少。答案误差在 10-6 内被视为是正确的。
813
 """

# 二维


class Solution:
    def largestSumOfAverages(self, nums: List[int], k: int) -> float:
        sum = nums
        n = len(nums)
        dp = [[0.0]*(k+1) for _ in range(1, n)]
        for i in range(1, n):
            sum[i] += sum[i-1]
            dp[i][1] = sum[i]/(i+1)
        dp[0][1] = sum[0]
        for K in range(2, k+1):
            for i in range(0, n):
                for j in range(0, i):
                    dp[i][K] = max(dp[i][K], dp[j][K-1]+(sum[i]-sum[j])/(i-j))
        return dp[n-1][k]

# 一维


class Solution:
    def largestSumOfAverages(self, nums: List[int], k: int) -> float:
        sum = nums
        n = len(nums)
        dp = [0.0]*n
        for i in range(1, n):
            sum[i] += sum[i-1]
            dp[i] = sum[i]/(i+1)
        dp[0] = sum[0]
        # for i in range(0,n):
        #     print(dp[i])
        for t in range(2, k+1):
            # 注意倒序
            for i in range(n-1, -1, -1):
                for j in range(0, i):
                    dp[i] = max(dp[i], dp[j]+(sum[i]-sum[j])/(i-j))
        return dp[n-1]


""" 
给你一个仅由字符 '0' 和 '1' 组成的字符串 s 。一步操作中，你可以将任一 '0' 变成 '1' ，或者将 '1' 变成 '0' 。

交替字符串 定义为：如果字符串中不存在相邻两个字符相等的情况，那么该字符串就是交替字符串。例如，字符串 "010" 是交替字符串，而字符串 "0100" 不是。

返回使 s 变成 交替字符串 所需的 最少 操作数。
1758
 """


class Solution:
    def minOperations(self, s: str) -> int:
        cnt = 0
        index = 0
        for c in s:
            if int(c) == index % 2:
                cnt += 1
            index += 1
        return min(cnt, len(s)-cnt)


class Solution:
    def minOperations(self, s: str) -> int:
        cnt = 0
        for i, c in enumerate(s):
            if int(c) == i % 2:
                cnt += 1
        return min(cnt, len(s)-cnt)


class Solution:
    def minOperations(self, s: str) -> int:
        cnt = sum(int(c) == i % 2 for i, c in enumerate(s))
        return min(cnt, len(s)-cnt)
