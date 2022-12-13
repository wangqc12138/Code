import imp
from heapq import heappush
from heapq import heappop
from typing import List
from collections import defaultdict
from collections import Counter
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


""" 
设计一个类似堆栈的数据结构，将元素推入堆栈，并从堆栈中弹出出现频率最高的元素。

实现 FreqStack 类:

    FreqStack() 构造一个空的堆栈。
    void push(int val) 将一个整数 val 压入栈顶。
    int pop() 删除并返回堆栈中出现频率最高的元素。
        如果出现频率最高的元素不只一个，则移除并返回最接近栈顶的元素。
895
 """


class FreqStack:

    def __init__(self):
        self.h = []
        self.cnt = defaultdict(int)
        self.index = 0

    def push(self, val: int) -> None:
        self.cnt[val] += 1
        self.index += 1
        heappush(self.h, (-self.cnt[val], -self.index, val))

    def pop(self) -> int:
        res = heappop(self.h)[2]
        self.cnt[res] -= 1
        return res
# 不使用优先级队列


class FreqStack:

    def __init__(self):
        self.index = defaultdict(int)
        self.dic = defaultdict(list)
        self.m = 0

    def push(self, val: int) -> None:
        self.index[val] += 1
        self.m = max(self.index[val], self.m)
        self.dic[self.index[val]].append(val)

    def pop(self) -> int:
        res = self.dic[self.m].pop()
        self.index[res] -= 1
        if len(self.dic[self.m]) == 0:
            self.m -= 1
        return res


""" 
给你两个整数 x 和 y ，表示你在一个笛卡尔坐标系下的 (x, y) 处。同时，在同一个坐标系下给你一个数组 points ，其中 points[i] = [ai, bi] 表示在 (ai, bi) 处有一个点。当一个点与你所在的位置有相同的 x 坐标或者相同的 y 坐标时，我们称这个点是 有效的 。

请返回距离你当前位置 曼哈顿距离 最近的 有效 点的下标（下标从 0 开始）。如果有多个最近的有效点，请返回下标 最小 的一个。如果没有有效点，请返回 -1 。

两个点 (x1, y1) 和 (x2, y2) 之间的 曼哈顿距离 为 abs(x1 - x2) + abs(y1 - y2) 。
1779
 """


class Solution:
    def nearestValidPoint(self, x: int, y: int, points: List[List[int]]) -> int:
        res = -1
        m = 100000
        for i, [a, b] in enumerate(points):
            if (a == x or b == y) and m > abs(a-x)+abs(b-y):
                res = i
                m = abs(a-x)+abs(b-y)
        return res


""" 
有 n 个盒子。给你一个长度为 n 的二进制字符串 boxes ，其中 boxes[i] 的值为 '0' 表示第 i 个盒子是 空 的，而 boxes[i] 的值为 '1' 表示盒子里有 一个 小球。

在一步操作中，你可以将 一个 小球从某个盒子移动到一个与之相邻的盒子中。第 i 个盒子和第 j 个盒子相邻需满足 abs(i - j) == 1 。注意，操作执行后，某些盒子中可能会存在不止一个小球。

返回一个长度为 n 的数组 answer ，其中 answer[i] 是将所有小球移动到第 i 个盒子所需的 最小 操作数。

每个 answer[i] 都需要根据盒子的 初始状态 进行计算。
1769
 """


class Solution:
    def minOperations(self, boxes: str) -> List[int]:
        n, p, t = len(boxes), 0, 0
        res, pre = [0]*n, [0]*n
        pre[0] = int(boxes[0])
        for i in range(1, n):
            pre[i] = pre[i-1]+int(boxes[i])
            if boxes[i] == '1':
                t += i
        for i in range(0, n):
            res[i] = p+t
            p += pre[i]
            t -= pre[n-1]-pre[i]
        return res


""" 
给你两个长度可能不等的整数数组 nums1 和 nums2 。两个数组中的所有值都在 1 到 6 之间（包含 1 和 6）。

每次操作中，你可以选择 任意 数组中的任意一个整数，将它变成 1 到 6 之间 任意 的值（包含 1 和 6）。

请你返回使 nums1 中所有数的和与 nums2 中所有数的和相等的最少操作次数。如果无法使两个数组的和相等，请返回 -1 。
1775
 """


class Solution:
    def minOperations(self, nums1: List[int], nums2: List[int]) -> int:
        s1, s2, v1, v2, l1, l2 = sum(nums1), sum(
            nums2), [0]*7, [0]*7, len(nums1), len(nums2)
        if min(l1, l2)*6 < max(l1, l2)*1:
            return -1
        for i in nums1:
            v1[i] += 1
        for i in nums2:
            v2[i] += 1
        if s1 > s2:
            return help(v2, v1, s1-s2)
        return help(v1, v2, s2-s1)

    def help(self, v1: List[int], v2: List[int], diff: int) -> int:
        v = [0]*7
        for i in range(1, 7):
            v[i] = v1[i]+v2[7-i]
        res = 0
        for i in range(1, 7):
            if diff <= v[i]*(6-i):
                res += (diff+5-i)//(6-i)
                break
            else:
                res += v[i]
                diff -= v[i]*(6-i)
        return res


""" 
一个字符串的 美丽值 定义为：出现频率最高字符与出现频率最低字符的出现次数之差。

    比方说，"abaacc" 的美丽值为 3 - 1 = 2 。

给你一个字符串 s ，请你返回它所有子字符串的 美丽值 之和。
1781
 """


class Solution:
    def beautySum(self, s: str) -> int:
        res, n = 0, len(s)
        for i in range(0, n):
            v = [0]*26
            for j in range(i, n):
                v[ord(s[j])-ord('a')] += 1
                maxn, minn = 0, n
                for k in v:
                    if k > 0:
                        maxn = max(maxn, k)
                        minn = min(minn, k)
                res += maxn-minn
        return res


class Solution:
    def beautySum(self, s: str) -> int:
        res = 0
        for i in range(0, len(s)):
            cnt = defaultdict(int)
            # cnt = Counter()
            for j in range(i, len(s)):
                cnt[s[j]] += 1
                res += max(cnt.values())-min(cnt.values())
        return res
