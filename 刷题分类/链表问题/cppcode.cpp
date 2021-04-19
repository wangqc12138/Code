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