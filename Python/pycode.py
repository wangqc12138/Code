from typing import List
from typing import Optional
""" 
给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。

你可以按任意顺序返回答案。 
1
"""


class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        n = len(nums)
        for i in range(n):
            for j in range(i+1, n):
                if nums[i]+nums[j] == target:
                    return [i, j]
        return []


class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        dc = {}
        index = 0
        for i in nums:
            if target-i in dc:
                return [index, dc[target-i]]
            dc[i] = index
            index += 1
        return []


class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        dc = {}
        for i, n in enumerate(nums):
            if target-n in dc:
                return [i, dc[target-n]]
            dc[n] = i
        return []


""" 
给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。

请你将两个数相加，并以相同形式返回一个表示和的链表。

你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
2
 """
# Definition for singly-linked list.


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        res = ListNode()
        ans = res
        pre = 0
        while l1 and l2:
            ans.next = ListNode((l1.val+l2.val+pre) % 10)
            pre = (l1.val+l2.val+pre)//10
            l1 = l1.next
            l2 = l2.next
            ans = ans.next
        while l1:
            ans.next = ListNode((l1.val+pre) % 10)
            pre = (l1.val+pre)//10
            l1 = l1.next
            ans = ans.next
        while l2:
            ans.next = ListNode((l2.val+pre) % 10)
            pre = (l2.val+pre)//10
            l2 = l2.next
            ans = ans.next
        if pre > 0:
            ans.next = ListNode(pre)
            ans = ans.next
        return res.next


class Solution:
    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        head = ListNode()
        ptr = head
        pre = 0
        while l1 or l2:
            x = l1.val if l1 else 0
            y = l2.val if l2 else 0
            head.next = ListNode(pre+x+y)
            pre = (pre+x+y)//10
            l1 = l1.next if l1 else None
            l1 = l1.next if l1 else None
