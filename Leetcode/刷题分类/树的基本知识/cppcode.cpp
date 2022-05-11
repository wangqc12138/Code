#include "head.h"
/*
序列化二叉树的一种方法是使用前序遍历。当我们遇到一个非空节点时，我们可以记录下这个节点的值。如果它是一个空节点，我们可以使用一个标记值记录，例如 #。
331
*/

/*
给你一棵二叉搜索树，请你 按中序遍历 将其重新排列为一棵递增顺序搜索树，使树中最左边的节点成为树的根节点，并且每个节点没有左子节点，只有一个右子节点。
897
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
//可以用morris遍历
class Solution {
public:
    TreeNode* dum=new TreeNode(0);
    TreeNode* increasingBST(TreeNode* root) {
        TreeNode* res=dum; 
        inorder(root);
        return res->right;
    }
    void inorder(TreeNode *root){
        if(root==nullptr){
            return;
        }
        inorder(root->left);
        dum->right=root;
        root->left=nullptr;
        dum=root;
        inorder(root->right);
    }
};
/* 
序列化是将数据结构或对象转换为一系列位的过程，以便它可以存储在文件或内存缓冲区中，或通过网络连接链路传输，以便稍后在同一个或另一个计算机环境中重建。

设计一个算法来序列化和反序列化 二叉搜索树 。 对序列化/反序列化算法的工作方式没有限制。 您只需确保二叉搜索树可以序列化为字符串，并且可以将该字符串反序列化为最初的二叉搜索树。

编码的字符串应尽可能紧凑。
449
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
	string res;
	void preorder(TreeNode* root){
		if(!root){
			return;
		}
		res+=to_string(root->val)+',';
		preorder(root->left);
		preorder(root->right);
	}
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        preorder(root);
		return res;
    }
	void splite(string str,vector<int>& ans){
		int i=0;
		while(i<str.size()){
			int k=str.find(',',i);
			ans.emplace_back(stoi(str.substr(i,k-i)));
			i=k+1;
		}
	}
	TreeNode* buildtree(vector<int>& data,int L,int R){
		if(L<0||L>=data.size()||L>R){
			return nullptr;
		}
		TreeNode* root=new TreeNode(data[L]);
		int l=-1,r=-1;
		for(int i=L;i<=R;i++){
			if(data[i]<data[L]&&l==-1){
				l=i;
			}
			if(data[i]>data[L]&&r==-1){
				r=i;
			}
		}
		root->left=buildtree(data,l,r-1<0?R:r-1);
		root->right=buildtree(data,r,R);
		return root;
	}
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<int> ans;
		splite(data,ans);
		return buildtree(ans,0,ans.size()-1);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;