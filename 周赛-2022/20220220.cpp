#include "head.h"
/* 
给你一个正整数 num ，请你统计并返回 小于或等于 num 且各位数字之和为 偶数 的正整数的数目。

正整数的 各位数字之和 是其所有位上的对应数字相加的结果。
 */
//暴力
/* 
给你一个链表的头节点 head ，该链表包含由 0 分隔开的一连串整数。链表的 开端 和 末尾 的节点都满足 Node.val == 0 。

对于每两个相邻的 0 ，请你将它们之间的所有节点合并成一个节点，其值是所有已合并节点的值之和。然后将所有 0 移除，修改后的链表不应该含有任何 0 。

 返回修改后链表的头节点 head 。
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
    ListNode* mergeNodes(ListNode* head) {
		vector<int> temp;
		ListNode* ptr=head->next;
		while(ptr){
			if(ptr->val==0){
				temp.emplace_back(0);
			}else{
				temp.back()+=ptr->val;
			}
			ptr=ptr->next;
		}
		temp.pop_back();
		ptr=head;
		for(int i=0;i<temp.size();i++){
			ptr->val=temp[i];
			ptr=ptr->next;
		}
		ptr->next=nullptr;
		return head;
    }
};
//原地修改
class Solution {
public:
    ListNode* mergeNodes(ListNode* head) {
        ListNode* ptr=head->next;
		ListNode* node=head;
		int temp=0;
		while(ptr){
			if(ptr->val==0){
				node->val=temp;
				temp=0;
				if(ptr->next){
					node=node->next;
				}
			}
			temp+=ptr->val;
			ptr=ptr->next;
		}
    }
};
/* 
给你一个字符串 s 和一个整数 repeatLimit ，用 s 中的字符构造一个新字符串 repeatLimitedString ，
使任何字母 连续 出现的次数都不超过 repeatLimit 次。你不必使用 s 中的全部字符。

返回 字典序最大的 repeatLimitedString 。

如果在字符串 a 和 b 不同的第一个位置，字符串 a 中的字母在字母表中出现时间比字符串 b 对应的字母晚，则认为字符串 a 比字符串 b 字典序更大 。
如果字符串中前 min(a.length, b.length) 个字符都相同，那么较长的字符串字典序更大。
 */
using pii=pair<int,int>;
class Solution {
public:
    string repeatLimitedString(string s, int repeatLimit) {
		auto cmp=[](pii a,pii b){
			return a.first<b.first;
		};
		priority_queue<pii,vector<pii>,decltype(cmp)> mpq(cmp);
		map<int,int> mp;
		for(auto i:s){
			mp[i]++;
		}
		for(auto itr:mp){
			mpq.emplace(itr);
		}
		string res;
		while(!mpq.empty()){
			auto t=mpq.top();
			mpq.pop();
			if(t.second>repeatLimit){
				t.second-=repeatLimit;
				for(int i=0;i<repeatLimit;i++){
					res+=t.first;
				}
				if(mpq.empty()){
					break;
				}
				auto k=mpq.top();
				mpq.pop();
				if(--k.second>0){
					mpq.emplace(k);
				}
				mpq.emplace(t);
			}else{
				for(int i=0;i<t.second;i++){
					res+=t.first;
				}
			}
		}
		return res;
    }
};
class Solution {
public:
    string repeatLimitedString(string s, int repeatLimit) {
		sort(s.begin(),s.end(),greater());
		int k=0,i=0,j=0,n=s.size();
		for(;j<n;j++){
			if(s[j]!=s[0]){
				break;
			}
		}
		for(;i<n&&j<n;i++){
			if(i==j){
				while(j<n&&s[i]==s[j]){
                    j++;
                }
			}
			if(j-i<=repeatLimit){
				i=j;
			}else{
				auto t=s[i+repeatLimit];
				s[i+repeatLimit]=s[j];
				s[j]=t;
				i+=repeatLimit;
				j++;
			}
		}
		string res=s.substr(0,i+1);
		return res;
    }
};