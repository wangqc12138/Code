#include "head.h"
/* 
给你一个整数数组 nums，请你返回其中 位数为 偶数 的数字的个数.
 */
class Solution {
public:
    int findNumbers(vector<int>& nums) {
		auto help=[](int i){
			int k=0;
			while(i){
				k++;
				i/=10;
			}
			return k%2;
		};
		int res=0;
		for(int i:nums){
			if(help(i)){
				res++;
			}
		}
		return res;
	}
};
/* 
给定一颗根结点为 root 的二叉树，树中的每一个结点都有一个从 0 到 25 的值，
分别代表字母 'a' 到 'z'：值 0 代表 'a'，值 1 代表 'b'，
依此类推。

找出按字典序最小的字符串，该字符串从这棵树的一个叶结点开始，到根结点结束。

（小贴士：字符串中任何较短的前缀在字典序上都是较小的：例如，在字典序上 "ab" 比 "aba" 要小。叶结点是指没有子结点的结点。）
988
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
//暴力才是正解！！！！！！！！
class Solution {
public:
	string res="";
    string smallestFromLeaf(TreeNode* root) {
		dfs(root,"");
		return res; 
	}
	void dfs(TreeNode* root,string temp) {
		if(!root){
			return;
		}
		if(!root->left&&!root->right){
			temp+=root->val+'a';
            reverse(temp.begin(),temp.end());
			if(res==""){
				res=temp;
			}else{
				if(res>temp){
					res=temp;
				}
			}
		}
        temp+=root->val+'a';
		dfs(root->left,temp);
		dfs(root->right,temp);   
	}
};
/* 
给你一个长度为 n 、下标从 1 开始的二进制字符串，所有位最开始都是 0 。我们会按步翻转该二进制字符串的所有位（即，将 0 变为 1）。

给你一个下标从 1 开始的整数数组 flips ，其中 flips[i] 表示对应下标 i 的位将会在第 i 步翻转。

二进制字符串 前缀一致 需满足：在第 i 步之后，在 闭 区间 [1, i] 内的所有位都是 1 ，而其他位都是 0 。

返回二进制字符串在翻转过程中 前缀一致 的次数。
1375
 */
class Solution {
public:
    int numTimesAllBlue(vector<int>& flips) {
		int n=flips.size(),index=0,res=0;
		long long k=0,s=0;
		for(int i=0;i<n;i++){
			k+=flips[i];
			s+=i+1;
			if(k==s){
				res++;
			}
		}
		return res;
    }
};