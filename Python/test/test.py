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
        res =0
        for t in List:
            res
    def help(s:str,t:str)->bool:
