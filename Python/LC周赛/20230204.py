from typing import List
"""
给你一个正整数数组 nums ，请你返回一个数组 answer ，你需要将 nums 中每个整数进行数位分割后，按照 nums 中出现的 相同顺序 放入答案数组中。

对一个整数进行数位分割，指的是将整数各个数位按原本出现的顺序排列成数组。

    比方说，整数 10921 ，分割它的各个数位得到 [1,0,9,2,1] 。

 """


class Solution:
    def separateDigits(self, nums: List[int]) -> List[int]:
        res = []
        for i in nums:
            for c in str(i):
                res.append(int(c))
        return res


"""
给你一个整数数组 banned 和两个整数 n 和 maxSum 。你需要按照以下规则选择一些整数：

    被选择整数的范围是 [1, n] 。
    每个整数 至多 选择 一次 。
    被选择整数不能在数组 banned 中。
    被选择整数的和不超过 maxSum 。

请你返回按照上述规则 最多 可以选择的整数数目。
 """


class Solution:
    def maxCount(self, banned: List[int], n: int, maxSum: int) -> int:
        sum, res, s = 0, 0, set(banned)
        for i in range(1, n+1):
            if i not in s:
                if sum+i <= maxSum:
                    sum += i
                    res += 1
                else:
                    return res
        return res


"""
在 X轴 上有一些奖品。给你一个整数数组 prizePositions ，它按照 非递减 顺序排列，其中 prizePositions[i] 是第 i 件奖品的位置。数轴上一个位置可能会有多件奖品。
再给你一个整数 k 。

你可以选择两个端点为整数的线段。每个线段的长度都必须是 k 。你可以获得位置在任一线段上的所有奖品（包括线段的两个端点）。注意，两个线段可能会有相交。

    比方说 k = 2 ，你可以选择线段 [1, 3] 和 [2, 4] ，你可以获得满足 1 <= prizePositions[i] <= 3 或者 2 <= prizePositions[i] <= 4 的所有奖品 i 。

请你返回在选择两个最优线段的前提下，可以获得的 最多 奖品数目。
 """


class Solution:
    def maximizeWin(self, prizePositions: List[int], k: int) -> int:
        res, l = 0, 0
        pre = []*(len(prizePositions)+1)
        for r in range(0, len(prizePositions)):
            while prizePositions[r]-prizePositions[l] > k:
                l += 1
            res = max(res, r-l+1+pre[l])
            pre[r+1] = max(pre[r], r-l+1)
        return res


""" 
给你一个下标从 0 开始的 m x n 二进制 矩阵 grid 。
你可以从一个格子 (row, col) 移动到格子 (row + 1, col) 或者 (row, col + 1) ，前提是前往的格子值为 1 。
如果从 (0, 0) 到 (m - 1, n - 1) 没有任何路径，我们称该矩阵是 不连通 的。

你可以翻转 最多一个 格子的值（也可以不翻转）。你 不能翻转 格子 (0, 0) 和 (m - 1, n - 1) 。

如果可以使矩阵不连通，请你返回 true ，否则返回 false 。

注意 ，翻转一个格子的值，可以使它的值从 0 变 1 ，或从 1 变 0 。
 """


class Solution:
    def isPossibleToCutPath(self, grid: List[List[int]]) -> bool:
        m, n = len(grid), len(grid[0])

        def dfs(x, y: int) -> bool:
            if x == m-1 and y == n-1:
                return True
            grid[x][y] = 0
            return x+1 < m and grid[x+1][y] == 1 and dfs(x+1, y) or y+1 < n and grid[x][y+1] == 1 and dfs(x, y+1)
        return not dfs(0, 0) or not dfs(0, 0)


class Solution:
    def isPossibleToCutPath(self, grid: List[List[int]]) -> bool:
        m, n = len(grid), len(grid[0])
        vist = []*m
        for i in range(0, m):
            vist.append([0]*n)
        mq = []
        mq.append((m-1, n-1))
        vist[m-1][n-1] = 1
        while len(mq) > 0:
            (x, y) = mq[0]
            mq.pop(0)
            if x-1 >= 0 and grid[x-1][y] == 1 and vist[x-1][y] == 0:
                mq.append((x-1, y))
                vist[x-1][y] = 1
            if y-1 >= 0 and grid[x][y-1] == 1 and vist[x][y-1] == 0:
                mq.append((x, y-1))
                vist[x][y-1] = 1
        if vist[0][0] == 0:
            return True
        mq.append((0, 0))
        while len(mq) > 0:
            if len(mq) == 1 and mq[0] != (0, 0) and mq[0] != (m-1, n-1):
                # print(mq[0])
                return True
            temp = []
            for (x, y) in mq:
                if x+1 < m and grid[x+1][y] == 1 and vist[x+1][y] == 1:
                    temp.append((x+1, y))
                    vist[x+1][y] = 0
                if y+1 < n and grid[x][y+1] == 1 and vist[x][y+1] == 1:
                    temp.append((x, y+1))
                    vist[x][y+1] = 0
            mq = temp
        return False
