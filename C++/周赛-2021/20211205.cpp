#include "head.h"
/* 
给你一个整数数组 digits ，其中每个元素是一个数字（0 - 9）。数组中可能存在重复元素。

你需要找出 所有 满足下述条件且 互不相同 的整数：

    该整数由 digits 中的三个元素按 任意 顺序 依次连接 组成。
    该整数不含 前导零
    该整数是一个 偶数

例如，给定的 digits 是 [1, 2, 3] ，整数 132 和 312 满足上面列出的全部条件。

将找出的所有互不相同的整数按 递增顺序 排列，并以数组形式返回。
 */
class Solution {
public:
    vector<int> findEvenNumbers(vector<int>& digits) {
        vector<int> nums(10,0),res;
		for(int i:digits){
			nums[i]++;
		}
		for(int i=998;i>=100;i-=2){
			int j=i%10,k=i/100,l=(i/10)%10;
			vector<int> temp=nums;
			if(--temp[j]<0){
				continue;
			}
			if(--temp[k]<0){
				continue;
			}
			if(--temp[l]<0){
				continue;
			}
			res.emplace_back(i);
		}
		return res;
    }
};
/* 
给你一个链表的头节点 head 。删除 链表的 中间节点 ，并返回修改后的链表的头节点 head 。

长度为 n 链表的中间节点是从头数起第 ⌊n / 2⌋ 个节点（下标从 0 开始），其中 ⌊x⌋ 表示小于或等于 x 的最大整数。

    对于 n = 1、2、3、4 和 5 的情况，中间节点的下标分别是 0、1、1、2 和 2 。
 */

/* 快慢指针一遍遍历 */
class Solution {
public:
    ListNode* deleteMiddle(ListNode* head) {
        ListNode* dum=new ListNode(0);
		dum->next=head;
		int n=0;
		ListNode *ptr=head;
		while(ptr){
			ptr=ptr->next;
			n++;
		}
		ptr=dum;
		ListNode *pre=dum;
		for(int i=1;i<=n/2;i++){
			ptr=ptr->next;
			if(i!=1){
				pre=pre->next;
			}
		}
		pre->next=ptr->next;
		return dum->next;
    }
};
/* 
给你一棵 二叉树 的根节点 root ，这棵二叉树总共有 n 个节点。每个节点的值为 1 到 n 中的一个整数，且互不相同。
给你一个整数 startValue ，表示起点节点 s 的值，和另一个不同的整数 destValue ，表示终点节点 t 的值。

请找到从节点 s 到节点 t 的 最短路径 ，并以字符串的形式返回每一步的方向。每一步用 大写 字母 'L' ，'R' 和 'U' 分别表示一种方向：

    'L' 表示从一个节点前往它的 左孩子 节点。
    'R' 表示从一个节点前往它的 右孩子 节点。
    'U' 表示从一个节点前往它的 父 节点。

请你返回从 s 到 t 最短路径 每一步的方向。
 */
class Solution {
public:
    string getDirections(TreeNode* root, int startValue, int destValue) {
        
    }
	int dfs(TreeNode* root,int startValue,int destValue) {
		if(root==nullptr){
			return 0;
		}
		if(root->val==startValue){
			return 1;
		}
		if(root->val==destValue){
			return 2;
		}
		int l=dfs(root->left,startValue,destValue);
		int r=dfs(root->right,startValue,destValue);
		if(l&&r){
			return 
		}
	}
};