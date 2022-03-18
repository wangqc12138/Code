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
/* 
运用你所掌握的数据结构，设计和实现一个  LRU (最近最少使用) 缓存机制 。

实现 LRUCache 类：

    LRUCache(int capacity) 以正整数作为容量 capacity 初始化 LRU 缓存
    int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
    void put(int key, int value) 如果关键字已经存在，则变更其数据值；如果关键字不存在，则插入该组「关键字-值」。
	当缓存容量达到上限时，它应该在写入新数据之前删除最久未使用的数据值，从而为新的数据值留出空间。

 

进阶：你是否可以在 O(1) 时间复杂度内完成这两种操作？
146
 */
class DLNode{
public:
	int key,val;
	DLNode *pre, *next;
	DLNode():key(0),val(0),pre(nullptr),next(nullptr){};
	DLNode(int key,int val):key(key),val(val),pre(nullptr),next(nullptr){};
	DLNode(int key,int val,DLNode *pre,DLNode *next):key(key),val(val),pre(pre),next(next){};
};
class LRUCache {
public:
    LRUCache(int capacity) {
		s=capacity;
		head=new DLNode();
		tail=new DLNode();
        head->next=tail;
        tail->pre=head;
    }
    int get(int key) {
		if(!ump.count(key)){
			return -1;
		}
		DLNode* tmp=ump[key];
		DLNode* p=tmp->pre, *q=tmp->next;
		p->next=q;
		q->pre=p;
		p=head->next;
		tmp->next=p;
		p->pre=tmp;
		head->next=tmp;
		tmp->pre=head;
		return ump[key]->val;
    }
    
    void put(int key, int value) {
		if(ump.count(key)){
			DLNode* tmp=ump[key];
			DLNode* p=tmp->pre, *q=tmp->next;
			p->next=q;
			q->pre=p;
			p=head->next;
			tmp->next=p;
			p->pre=tmp;
			head->next=tmp;
			tmp->pre=head;
			ump[key]->val=value;
		}else{
			DLNode* ptr=new DLNode(key,value,head,head->next);
			ump[key]=ptr;
            DLNode* tmp=head->next;
			tmp->pre=ptr;
			head->next=ptr;
			if(s>0){
				s--;
			}else{
                int dk=tail->pre->key;
                ump.erase(dk);
				DLNode* tmp=tail->pre->pre;
				tmp->next=tail;
				tail->pre=tmp;
			}	
		}
    }
private:
	unordered_map<int,DLNode*> ump;
	DLNode *head,*tail;
	int s;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
/* 
请你为 最不经常使用（LFU）缓存算法设计并实现数据结构。

实现 LFUCache 类：

    LFUCache(int capacity) - 用数据结构的容量 capacity 初始化对象
    int get(int key) - 如果键存在于缓存中，则获取键的值，否则返回 -1。
    void put(int key, int value) - 如果键已存在，则变更其值；如果键不存在，请插入键值对。
	当缓存达到其容量时，则应该在插入新项之前，使最不经常使用的项无效。
	在此问题中，当存在平局（即两个或更多个键具有相同使用频率）时，应该去除 最近最久未使用 的键。

注意「项的使用次数」就是自插入该项以来对其调用 get 和 put 函数的次数之和。使用次数会在对应项被移除后置为 0 。

为了确定最不常使用的键，可以为缓存中的每个键维护一个 使用计数器 。使用计数最小的键是最久未使用的键。

当一个键首次插入到缓存中时，它的使用计数器被设置为 1 (由于 put 操作)。对缓存中的键执行 get 或 put 操作，使用计数器的值将会递增。
460
 */
class LFUCache {
public:
    LFUCache(int capacity) {

    }
    
    int get(int key) {

    }
    
    void put(int key, int value) {

    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
//双链表的应用
/* 
请你设计一个用于存储字符串计数的数据结构，并能够返回计数最小和最大的字符串。

实现 AllOne 类：

    AllOne() 初始化数据结构的对象。
    inc(String key) 字符串 key 的计数增加 1 。如果数据结构中尚不存在 key ，那么插入计数为 1 的 key 。
    dec(String key) 字符串 key 的计数减少 1 。如果 key 的计数在减少后为 0 ，那么需要将这个 key 从数据结构中删除。测试用例保证：在减少计数前，key 存在于数据结构中。
    getMaxKey() 返回任意一个计数最大的字符串。如果没有元素存在，返回一个空字符串 "" 。
    getMinKey() 返回任意一个计数最小的字符串。如果没有元素存在，返回一个空字符串 "" 。
432
 */
class AllOne {
public:
    AllOne() {
		
    }
    
    void inc(string key) {

    }
    
    void dec(string key) {

    }
    
    string getMaxKey() {

    }
    
    string getMinKey() {

    }
};