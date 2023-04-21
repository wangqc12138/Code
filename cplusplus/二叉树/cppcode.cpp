#include "head.h"
// 遍历
/*
给你二叉树的根节点 root ，返回它节点值的 前序 遍历。
T144
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
// 使用递归和非递归
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        function<void(TreeNode*)> dfs = [&](TreeNode* root) -> void {
            if (root == nullptr) {
                return;
            }
            res.emplace_back(root->val);
            dfs(root->left);
            dfs(root->right);
        };
        dfs(root);
        return res;
    }
};
// 非递归
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*> sk;
        sk.emplace(root);
        vector<int> res;
        while (!sk.empty()) {
            auto node = sk.top();
            sk.pop();
            if (node == nullptr) {
                continue;
            }
            res.emplace_back(node->val);
            sk.emplace(node->right);
            sk.emplace(node->left);
        }
        return res;
    }
};
// 非递归
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*> sk;
        map<TreeNode*, int> mp;
        vector<int> res;
        sk.emplace(root);
        while (!sk.empty()) {
            auto node = sk.top();
            sk.pop();
            if (node == nullptr) {
                continue;
            }
            if (mp[node] == 1) {
                res.emplace_back(node->val);
            } else {
                mp[node] = 1;
                sk.emplace(node->right);
                sk.emplace(node->left);
                sk.emplace(node);
            }
        }
        return res;
    }
};
/*
给定一个二叉树的根节点 root ，返回 它的 中序 遍历 。
T94
 */
// 递归
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        function<void(TreeNode*)> dfs = [&](TreeNode* root) -> void {
            if (root == nullptr) {
                return;
            }
            dfs(root->left);
            res.emplace_back(root->val);
            dfs(root->right);
        };
        dfs(root);
        return res;
    }
};
// 非递归
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> sk;
        map<TreeNode*, int> mp;
        vector<int> res;
        sk.emplace(root);
        while (!sk.empty()) {
            auto node = sk.top();
            sk.pop();
            if (node == nullptr) {
                continue;
            }
            if (mp[node] == 1) {
                res.emplace_back(node->val);
            } else {
                mp[node] = 1;
                sk.emplace(node->right);
                sk.emplace(node);
                sk.emplace(node->left);
            }
        }
        return res;
    }
};
/*
给你一棵二叉树的根节点 root ，返回其节点值的 后序遍历 。
T145
 */
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        stack<TreeNode*> sk;
        map<TreeNode*, int> mp;
        vector<int> res;
        sk.emplace(root);
        while (!sk.empty()) {
            auto node = sk.top();
            sk.pop();
            if (node == nullptr) {
                continue;
            }
            if (mp[node] == 1) {
                res.emplace_back(node->val);
            } else {
                mp[node] = 1;
                sk.emplace(node);
                sk.emplace(node->right);
                sk.emplace(node->left);
            }
        }
        return res;
    }
};
/*
给你二叉树的根节点 root ，返回其节点值的 层序遍历 。 （即逐层地，从左到右访问所有节点）。
T102
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> mq;
        vector<vector<int>> res;
        mq.emplace(root);
        while (!mq.empty()) {
            int len = mq.size();
            vector<int> temp;
            for (int i = 0; i < len; i++) {
                auto node = mq.front();
                mq.pop();
                if (node == nullptr) {
                    continue;
                }
                temp.emplace_back(node->val);
                mq.emplace(node->left);
                mq.emplace(node->right);
            }
            if (!temp.empty()) {
                res.emplace_back(temp);
            }
        }
        return res;
    }
};
/*
给你二叉树的根节点 root ，返回其节点值的 锯齿形层序遍历 。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。
T103
 */
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        queue<TreeNode*> mq;
        vector<vector<int>> res;
        mq.emplace(root);
        while (!mq.empty()) {
            int len = mq.size();
            vector<int> temp;
            for (int i = 0; i < len; i++) {
                auto node = mq.front();
                mq.pop();
                if (node == nullptr) {
                    continue;
                }
                temp.emplace_back(node->val);
                mq.emplace(node->left);
                mq.emplace(node->right);
            }
            if (!temp.empty()) {
                if (res.size() % 2) {
                    reverse(temp.begin(), temp.end());
                }
                res.emplace_back(temp);
            }
        }
        return res;
    }
};