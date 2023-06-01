#include "head.h"
/* 
给定一个可能含有重复元素的整数数组，要求随机输出给定的数字的索引。 您可以假设给定的数字一定存在于数组中。

注意：
数组大小可能非常大。 使用太多额外空间的解决方案将不会通过测试。
398
*/
//方法一：map
class Solution {
public:
    Solution(vector<int>& nums) {
		for(int index=0;auto i:nums){
			ump[i].emplace_back(index++);
		}
    }
    
    int pick(int target) {
		vector<int> temp;
		temp=ump[target];
		return temp[rand()%temp.size()];
    }
private:
	unordered_map<int,vector<int>> ump;
};
//方法二：蓄水池抽样
class Solution {
public:
    Solution(vector<int>& nums) {
		this->nums=nums;
    }
    
    int pick(int target) {
		int cnt=0,res=-1;
		for(int i=0;i<nums.size();i++){
			if(target==nums[i]){
				if(rand()%++cnt==0){
					res=i;
				}
			}
		}
		return res;
    }
private:
	vector<int> nums;
};
/* 
给你一个单链表，随机选择链表的一个节点，并返回相应的节点值。每个节点 被选中的概率一样 。

实现 Solution 类：

    Solution(ListNode head) 使用整数数组初始化对象。
    int getRandom() 从链表中随机选择一个节点并返回该节点的值。链表中所有节点被选中的概率相等。
382
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
    Solution(ListNode* head) {
        while(head){
            nums.emplace_back(head->val);
            head=head->next;
        }
    }
    
    int getRandom() {
        return nums[rand()%nums.size()];
    }
private:
    vector<int> nums;
};
//进阶
class Solution {
public:
    Solution(ListNode* head) {
        while(head){
            nums.emplace_back(head->val);
            head=head->next;
        }
    }
    
    int getRandom() {
        int res=0;
        for(int index=0;int i:nums){
            if(rand()%++index==0){
                res=i;
            }
        }
        return res;
    }
private:
    vector<int> nums;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */
/* 
给你一个 m x n 的二元矩阵 matrix ，且所有值被初始化为 0 。请你设计一个算法，随机选取一个满足 matrix[i][j] == 0 的下标 (i, j) ，并将它的值变为 1 。、
所有满足 matrix[i][j] == 0 的下标 (i, j) 被选取的概率应当均等。

尽量最少调用内置的随机函数，并且优化时间和空间复杂度。

实现 Solution 类：

    Solution(int m, int n) 使用二元矩阵的大小 m 和 n 初始化该对象
    int[] flip() 返回一个满足 matrix[i][j] == 0 的随机下标 [i, j] ，并将其对应格子中的值变为 1
    void reset() 将矩阵中所有的值重置为 0
519
 */
class Solution {
public:
    Solution(int m, int n) {
        nums=vector<int>(m*n,0);
        this->n=n;
    }
    
    vector<int> flip() {
        int cnt=0;
        vector<int> res(2);
        while(1){
            int k=rand();
            if(nums[k%nums.size()]==0){
                cnt=k%nums.size();
                nums[cnt]=1;
                return {cnt/n,cnt%n};
            }
        }
        return {};
    }
    
    void reset() {
        nums=vector<int>(nums.size(),0);
    }
private:
    vector<int> nums;
    int n;
};
