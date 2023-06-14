from collections import Counter

grid = [[3, 1, 2, 2], [1, 4, 4, 5], [2, 4, 2, 2], [2, 4, 2, 2]]
res, n = 0, len(grid)
cnt = Counter(tuple(row) for row in grid)
print(cnt)
res = 0
for j in range(n):
    res += cnt[tuple([grid[i][j] for i in range(n)])]
