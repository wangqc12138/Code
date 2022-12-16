#include "head.h"
/*
给你一棵 完美 二叉树的根节点 root ，请你反转这棵树中每个 奇数 层的节点值。

    例如，假设第 3 层的节点值是 [2,1,3,4,7,11,29,18] ，那么反转后它应该变成 [18,29,11,7,4,3,1,2] 。

反转后，返回树的根节点。

完美 二叉树需满足：二叉树的所有父节点都有两个子节点，且所有叶子节点都在同一层。

节点的 层数 等于该节点到根节点之间的边数。
 */
class Solution
{
public:
    TreeNode *reverseOddLevels(TreeNode *root)
    {
        queue<TreeNode *> mq;
        mq.emplace(root);
        stack<int> msk;
        int index = 0;
        while (!mq.empty())
        {
            int len = mq.size();
            for (int i = 0; i < len; i++)
            {
                auto node = mq.front();
                mq.pop();
                if (index % 2)
                {
                    node->val = msk.top();
                    msk.pop();
                }
                if (node->left)
                {
                    mq.emplace(node->left);
                    mq.emplace(node->right);
                    if (index % 2 == 0)
                    {
                        msk.emplace(node->left->val);
                        msk.emplace(node->right->val);
                    }
                }
            }
            index++;
        }
        return root;
    }
};
/*
给你一个长度为 n 的数组 words ，该数组由 非空 字符串组成。

定义字符串 word 的 分数 等于以 word 作为 前缀 的 words[i] 的数目。

    例如，如果 words = ["a", "ab", "abc", "cab"] ，那么 "ab" 的分数是 2 ，因为 "ab" 是 "ab" 和 "abc" 的一个前缀。

返回一个长度为 n 的数组 answer ，其中 answer[i] 是 words[i] 的每个非空前缀的分数 总和 。

注意：字符串视作它自身的一个前缀。
 */
class Trie
{
public:
    Trie()
    {
        next = vector<Trie *>(26);
        isEnd = false;
        count = 0;
    }
    void add(string str)
    {
        Trie *root = this;
        int index = 1;
        for (auto c : str)
        {
            if (root->next[c - 'a'] == nullptr)
            {
                root->next[c - 'a'] = new Trie();
            }
            root = root->next[c - 'a'];
            root->count += index++;
        }
        root->isEnd = true;
    }
    int getCount(string str)
    {
        Trie *root = this;
        for (auto c : str)
        {
            root = root->next[c - 'a'];
        }
        return root->count;
    }

private:
    vector<Trie *> next;
    bool isEnd;
    int count;
};
class Solution
{
public:
    vector<int> sumPrefixScores(vector<string> &words)
    {
        Trie *root = new Trie();
        for (auto str : words)
        {
            root->add(str);
        }
        vector<int> ans;
        for (auto str : words)
        {
            ans.emplace_back(root->getCount(str));
        }
        return ans;
    }
};