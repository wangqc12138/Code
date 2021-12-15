#include "head.h"
/* 
有 n 个人前来排队买票，其中第 0 人站在队伍 最前方 ，第 (n - 1) 人站在队伍 最后方 。

给你一个下标从 0 开始的整数数组 tickets ，数组长度为 n ，其中第 i 人想要购买的票数为 tickets[i] 。

每个人买票都需要用掉 恰好 1 秒 。
一个人 一次只能买一张票 ，如果需要购买更多票，他必须走到  队尾 重新排队（瞬间 发生，不计时间）。
如果一个人没有剩下需要买的票，那他将会 离开 队伍。

返回位于位置 k（下标从 0 开始）的人完成买票需要的时间（以秒为单位）。

 */
class Solution {
public:
    int timeRequiredToBuy(vector<int>& tickets, int k) {
        queue<pair<int,int>> mq;
		int index=0;
		for(int i:tickets){
			mq.emplace(index++,i);
		}
		int res=0;
		while(!mq.empty()){
			auto hd=mq.front();
			mq.pop();
            res++;
			if(--hd.second==0){
				if(hd.first==k){
					return res;
				}
			}else{
				mq.emplace(hd);
			}
		}
        return -1;
    }
};
/* 
给你一个链表的头节点 head 。

链表中的节点 按顺序 划分成若干 非空 组，这些非空组的长度构成一个自然数序列（1, 2, 3, 4, ...）。
一个组的 长度 就是组中分配到的节点数目。换句话说：

    节点 1 分配给第一组
    节点 2 和 3 分配给第二组
    节点 4、5 和 6 分配给第三组，以此类推

注意，最后一组的长度可能小于或者等于 1 + 倒数第二组的长度 。

反转 每个 偶数 长度组中的节点，并返回修改后链表的头节点 head 。
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
    ListNode* reverseEvenLengthGroups(ListNode* head) {
        ListNode* pre=head;
		ListNode* ptr=head->next;
		int n=2,s=-1;
        while(pre){
            pre=pre->next;
            s++;
        }
        pre=head;
		while(ptr){
			if((s>=n&&n%2==0)||(s%2==0&&s<n)){
				for(int i=0;i<n-1&&ptr->next;i++){
					ListNode *temp=ptr->next;
					ptr->next=temp->next;
					temp->next=pre->next;
					pre->next=temp;
				}
				pre=ptr;
				ptr=ptr->next;
			}else{
				for(int i=0;i<n&&ptr;i++){
					ptr=ptr->next;
					pre=pre->next;
				}
			}
            ListNode *temp=head;
            s-=n;
            n++;
		}
		return head;
    }
};

class Solution {
public:
    string decodeCiphertext(string encodedText, int rows) {
		int n=encodedText.size();
		int cols=n/rows;
		vector<vector<char>> vec(rows,vector<char>(cols));
		int index=0;
		for(int i=0;i<rows;i++){
			for(int j=0;j<cols;j++){
				vec[i][j]=encodedText[index++];
			}
		}
		string res="";
		for(int j=0;j<cols;j++){
			int k=j;
			for(int i=0;i<rows&&j<cols;){
				res+=vec[i++][j++];
			}
			j=k;
		}
		for(int i=res.size()-1;i>0;i--){
			if(res[i]==' '){
				res.pop_back();
			}else{
				break;
			}
		}
		return res;
    }
};
/* 
给你一个整数 n ，表示网络上的用户数目。每个用户按从 0 到 n - 1 进行编号。

给你一个下标从 0 开始的二维整数数组 restrictions ，其中 restrictions[i] = [xi, yi] 意味着用户 xi 和用户 yi 不能 成为 朋友 ，不管是 直接 还是通过其他用户 间接 。

最初，用户里没有人是其他用户的朋友。给你一个下标从 0 开始的二维整数数组 requests 表示好友请求的列表，其中 requests[j] = [uj, vj] 是用户 uj 和用户 vj 之间的一条好友请求。

如果 uj 和 vj 可以成为 朋友 ，那么好友请求将会 成功 。每个好友请求都会按列表中给出的顺序进行处理（即，requests[j] 会在 requests[j + 1] 前）。一旦请求成功，那么对所有未来的好友请求而言， uj 和 vj 将会 成为直接朋友 。

返回一个 布尔数组 result ，其中元素遵循此规则：如果第 j 个好友请求 成功 ，那么 result[j] 就是 true ；否则，为 false 。

注意：如果 uj 和 vj 已经是直接朋友，那么他们之间的请求将仍然 成功 。
 */
class unionfindset{
public:
	void makeset(int n,vector<vector<int>>& restrictions){
		for(int i=0;i<n;i++){
			head[i]=i;
			size[i]=1;
			friendlist[i].emplace(i);
		}
		for(auto vec:restrictions){
			blacklist[vec[0]].emplace(vec[1]);
			blacklist[vec[1]].emplace(vec[0]);
		}
	}
	int findhead(int i){
		int h=head[i];
		if(h!=i){
			h=findhead(h);
		}
		head[i]=h;
		return h;
	}
	bool issamehead(int i,int j){
		return findhead(i)==findhead(j);
	}
	bool isinblacklist(int i,int j){
		int ihead=findhead(i);
		int jhead=findhead(j);
		for(int k:friendlist[ihead]){
			if(blacklist[jhead].count(k)){
				return true;
			}
		}
		return false;
	}
	void unionset(int i,int j){
		int ihead=findhead(i);
		int jhead=findhead(j);
		if(ihead!=jhead){
			int isize=size[ihead];
			int jsize=size[jhead];
			if(isize>=jsize){
				head[jhead]=ihead;
				size[ihead]=isize+jsize;
				blacklist[ihead].insert(blacklist[jhead].begin(),blacklist[jhead].end());
				friendlist[ihead].insert(friendlist[jhead].begin(),friendlist[jhead].end());
			}else{
				head[ihead]=jhead;
				size[jhead]=isize+jsize;
				blacklist[jhead].insert(blacklist[ihead].begin(),blacklist[ihead].end());
				friendlist[jhead].insert(friendlist[ihead].begin(),friendlist[ihead].end());
			}
		}
	}
private:
	map<int,int> head,size;
	map<int,set<int>> blacklist;
	map<int,set<int>> friendlist;
};
class Solution {
public:
    vector<bool> friendRequests(int n, vector<vector<int>>& restrictions, vector<vector<int>>& requests) {
        unionfindset ufs;
		ufs.makeset(n,restrictions);
		vector<bool> res;
        int index=0;
		for(auto vec:requests){
			if(ufs.isinblacklist(vec[0],vec[1])){
				res.emplace_back(false);
			}else{
				res.emplace_back(true);
				ufs.unionset(vec[0],vec[1]);
			}
		}
		return res;
    }
};