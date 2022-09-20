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
