/*
给你一棵所有节点为非负值的二叉搜索树，请你计算树中任意两节点的差的绝对值的最小值。
二叉搜索树--有序--中序遍历为递增
530
*/
class Solution {
public:
    int res=MAX_INT,pre=-1;
    int getMinimumDifference(TreeNode* root) {
        midorder(root);
        return res;
    }
    void midorder(TreeNode* root){
        if(root==nullptr){
            return;
        }
        midorder(root->left);
        if(pre==-1){
            pre=root->val;
        }else{
            res=min(res,root->val-pre);
            pre=root->val;
        }
        midorder(root->right);
    }
};