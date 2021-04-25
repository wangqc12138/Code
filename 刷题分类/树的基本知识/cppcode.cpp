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