from itertools import chain
import queue
from turtle import right
from typing import Optional
# Definition for a binary tree node.
# BFS


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def reverseOddLevels(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        q, index = [root], 0
        while q[0].left:
            q = chain.from_iterable((node.left, node.right) for node in q)
            if index == 0:
                for i in range(0, len(q)//2):
                    x, y = q[i], q[len(q)-i-1]
                    x.val, y.val = y.val, x.val
            index = 0 if index else 1
        return root
# DFS


class Solution:
    def reverseOddLevels(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        def dfs(L: Optional[TreeNode], R: Optional[TreeNode], index: int) -> None:
            if root is None:
                return
            if index % 2:
                L.val, R.val = R.val, L.val
            dfs(L.left, R.right, index+1)
            dfs(L.right, R.left, index+1)
        dfs(root.left, root.right, 1)
        return root


class Solution:
    def reverseOddLevels(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        def dfs(L: Optional[TreeNode], R: Optional[TreeNode], is_odd_level: int) -> None:
            if L is None:
                return
            if is_odd_level:
                L.val, R.val = R.val, L.val
            dfs(L.left, R.right,  is_odd_level + 1)
            dfs(L.right, R.left,  is_odd_level + 1)
        dfs(root.left, root.right, 1)
        return root
