#include "head.h"
/*
给你单链表的头节点 head 和两个整数 left 和 right ，其中 left <= right 。请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。 
92
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
    	if(left==right){
    		return head;
    	}
    	ListNode* dum= new ListNode(0);
    	dum->next=head;
    	ListNode* pre=dum;
    	for(int i=1;i<left;i++){
    		pre=pre->next;
    	}
    	ListNode* ptr=pre->next;
    	//ptr指向left
    	for(int i=left;i<right;i++){
    		ListNode* nxt=ptr->next;
    		ptr->next=nxt->next;
    		nxt->next=pre->next;
    		pre->next=nxt;
    	}
    	return dum->next;
    }
};
/*
存在一个按升序排列的链表，给你这个链表的头节点 head ，请你删除链表中所有存在数字重复情况的节点，只保留原始链表中 没有重复出现 的数字。
返回同样按升序排列的结果链表。
82
*/
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* dum=new ListNode(0);
        dum->next=head;
        ListNode* pre=dum;
        ListNode* ptr=dum->next;
        while(ptr!=nullptr&&ptr->next!=nullptr){
            if(ptr->val==ptr->next->val){
                int x=ptr->val;
                while(ptr!=nullptr&&ptr->val==x){
                    ptr=ptr->next;
                }
            }else{
                pre->next=ptr;
                pre=pre->next;
                ptr=ptr->next;
            }         
            
        }
        return dum->next;
    }
};
/* 
给你一个链表，每 k 个节点一组进行翻转，请你返回翻转后的链表。

k 是一个正整数，它的值小于或等于链表的长度。

如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。

进阶：

    你可以设计一个只使用常数额外空间的算法来解决此问题吗？
    你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。
25
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
	void reverse(ListNode* head,int i,int k){
		ListNode* pre=head;
		for(int index=0;index<i&&pre!=nullptr;i++){
			pre=pre->next;
		}
		ListNode* ptr=pre->next;
		while(ptr->next&&k-->0){
			ListNode *nxt=ptr->next;
			ptr->next=nxt->next;
			nxt->next=pre->next;
			pre->next=nxt;
		}
	}
    ListNode* reverseKGroup(ListNode* head, int k) {
		ListNode* dum=new ListNode(0);
		dum->next=head;
		int i=0,j=0;
		while(head){
			head=head->next;
			i++;
			if(i-j==k){
				j=i;
				reverse(dum,j,k);
			}
		}
		return dum->next;
    }
};
/* 
定义一个函数，输入一个链表的头节点，反转该链表并输出反转后链表的头节点。
示例:

输入: 1->2->3->4->5->NULL
输出: 5->4->3->2->1->NULL
206
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
		if(head==nullptr){
			return nullptr;
		}
		ListNode* dum=new ListNode(0);
		dum->next=head;
		while(head->next){
			ListNode* nxt=head->next;
			head->next=nxt->next;
			nxt->next=dum->next;
			dum->next=nxt;
		}
		return dum->next;
    }
};