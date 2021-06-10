#include "head.h"
//树的DFS
/*
给定一个二叉树，找出其最大深度。
二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。
说明: 叶子节点是指没有子节点的节点。
104
注意递归函数的返回值就可以
*/
class Solution {
public:
    int maxDepth(TreeNode* root) {
		if(root==nullptr){
			return 0;
		}
		int ld=maxDepth(root->left);
		int rd=maxDepth(root->right);
		return 1+max(ld,rd);
    }
};
/*
给定一个二叉树，找出其最小深度。
最小深度是从根节点到最近叶子节点的最短路径上的节点数量。
说明：叶子节点是指没有子节点的节点。
111
如果像上一题一样设计，会出现：根节点只有一个子节点时，返回1；
最短路径，其实使用BFS更快。
*/
class Solution {
public:
    int minDepth(TreeNode* root) {
		if(root==nullptr){
            return 0;
        }
		int len=INT_MAX;
		if(root->left){
			len=min(minDepth(root->left),len);
		}
		if(root->right){
			len=min(minDepth(root->right),len);
		} 
		if(len==INT_MAX){//叶节点
			return 1;
		}
		return 1+len;
    }
};
//BFS
class Solution {
public:
    int minDepth(TreeNode* root) {
		int res=0;
		queue<TreeNode*> mq;
		if(root==nullptr){
			return 0;
		}
		mq.emplace(root);
		while(!mq.empty()){
			int len=mq.size();
			for(int i=0;i<len;i++){
				auto node=mq.front();
				if(!node->left&&!node->right){
					return res;
				}
				mq.pop();
				if(node->left){
					mq.emplace(node->left);
				}
				if(node->right){
					mq.emplace(node->right);
				}
			}
			res++;
		}
    }
};
/*
给你二叉树的根节点 root 和一个表示目标和的整数 targetSum ，判断该树中是否存在 根节点到叶子节点 的路径，
这条路径上所有节点值相加等于目标和 targetSum 。
叶子节点 是指没有子节点的节点。
112
下面注释的代码遇到当输入根节点为空，targetSum=0时会错误
*/
// class Solution {
// public:
//     bool hasPathSum(TreeNode* root, int targetSum) {
// 		if(root==nullptr){
// 			if(targetSum==0){
// 				return true;
// 			}else{
// 				return false;
// 			}
// 		}
// 		return hasPathSum(root->left,targetSum-root->val)||hasPathSum(root->right,targetSum-root->val);
//     }
// };
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
		if(root==nullptr){
			return false;
		}
		if(!root->left&&!root->right){
			return targetSum==root->val;
		}
		return hasPathSum(root->left,targetSum-root->val)||hasPathSum(root->right,targetSum-root->val);
    }
};
/*
翻转一棵二叉树。
226
依次用前中后序层次遍历------
*/
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
		if(!root){
			return nullptr;
		}
		TreeNode* temp=root->right;
		root->right=invertTree(root->left);
		root->left=invertTree(temp);
		return root;
    }
};
/*
给你两棵二叉树的根节点 p 和 q ，编写一个函数来检验这两棵树是否相同。
如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。
100
*/
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
		if(!p&&!q){
			return true;
		}
		if(!p&&q||p&&!q){
        	return false;
		}
		return p->val==q->val&&isSameTree(p->left,q->left)&&isSameTree(p->right,q->right);
    }
};
/*
给定一个二叉树，检查它是否是镜像对称的。
101
*/
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
		if(!root){
			return true;
		}
		return dfs(root->left,root->right);
    }
	bool dfs(TreeNode* p,TreeNode* q){
		if(!p&&!q){
			return true;
		}
		if(!p||!q){
			return false;
		}
		if(p->val!=q->val){
			return false;
		}
		return dfs(p->right,q->left)&&dfs(p->left,q->right);
	}
};
/*
给你一个二叉树的根节点 root ，树中每个节点都存放有一个 0 到 9 之间的数字。
每条从根节点到叶节点的路径都代表一个数字：
    例如，从根节点到叶节点的路径 1 -> 2 -> 3 表示数字 123 。
计算从根节点到叶节点生成的 所有数字之和 。
叶节点 是指没有子节点的节点。
129
*/
class Solution {
public:
    int sumNumbers(TreeNode* root) {
		return dfs(root,0);
    }
	int dfs(TreeNode* root,int sum){
		if(!root){
			return 0;
		}
		// sum=sum*10+root->val;
		if(!root->left&&!root->right){
			return sum*10+root->val;
		}
		return dfs(root->left,sum*10+root->val)+dfs(root->right,sum*10+root->val);
	}
};
//LCA问题
/* 
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为：
对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。
236
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root==p||root==q){//如果它的子树下面有另一个，那自己也算祖先，可以立刻返回
			return root;
		}
		if(root){
			TreeNode *l=lowestCommonAncestor(root->left,p,q);
			TreeNode *r=lowestCommonAncestor(root->right,p,q);
			if(l&&r){//一左一右
				return root;
			}else if(l){//全在左子树上
				return l;
			}else if(r){//全在右子树上
				return r;
			}
		}
		return nullptr;
    }
};
class Solution {
public:
	TreeNode* res;
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        findListNode(root,p->val,q->val);
        return res;
    }
    bool findListNode(TreeNode* root, int p, int q){
        if(root==nullptr){
            return false;
        }
        bool inCurr=root->val==p||root->val==q;
        bool inRight=findListNode(root->right,p,q);
        bool inLeft=findListNode(root->left,p,q);
        if(inRight&&inLeft||inCurr&&(inRight||inLeft)){//如果一左一右有或者自己是且另一个是子节点
        	res=root;
        }
        return inCurr||inRight||inLeft;
    }
};
/*
给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。
235
二叉搜索树比上一题简单，当然用上一题代码也可以
*/
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root==nullptr){
			return nullptr;
		}
		if(root->val<=max(p->val,q->val)&&root->val>=min(p->val,q->val)){
			return root;
		}
		TreeNode *l=lowestCommonAncestor(root->left,p,q);
		TreeNode *r=lowestCommonAncestor(root->right,p,q);
		if(l){
			return l;
		}
		return r;
    }
};
/*
给定一棵二叉树的根节点 root，返回给定节点 p 和 q 的最近公共祖先（LCA）节点。
如果 p 或 q 之一不存在于该二叉树中，返回 null。树中的每个节点值都是互不相同的。
1644
*/
class Solution {
public:
	TreeNode* res;
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        dfs(root,p->val,q->val);
		return res;
    }
	bool dfs(TreeNode* root,int p,int q){
		if(root==nullptr){
			return false;
		}
		bool inCur=false,inLeft,inRight;//不初始化会出现默认为true！！！
		if(root->val==p||root->val==q){
			inCur=true;
		}
		inLeft=dfs(root->left,p,q);
		inRight=dfs(root->right,p,q);
		if(inLeft&&inRight||inCur&&(inLeft||inRight)){
			res=root;
		}
		return inLeft||inRight||inCur;
	}
};
/*
给定一棵二叉树中的两个节点 p 和 q，返回它们的最近公共祖先节点（LCA）。
每个节点都包含其父节点的引用（指针）。Node 的定义如下：
class Node {
    public int val;
    public Node left;
    public Node right;
    public Node parent;
}
1650
本题不是使用DFS，不过作为LCA的题放一起了
*/
class Node {
public:
	int val;
    Node *left;
    Node *right;
    Node *parent;
};
class Solution {
public:
    Node* lowestCommonAncestor(Node* p, Node * q) {
    	set<int> myset;
    	while(p){
    		myset.insert(p->val);
    		p=p->parent;
    	}
    	while(q){
    		if(myset.count(q->val)){
    			return q;
    		}
    		q=q->parent;
    	}
    	return nullptr;
    }
};
/*
给定一棵二叉树的根节点 root 和 TreeNode 类对象的数组（列表） nodes，返回 nodes 中所有节点的最近公共祖先（LCA）。
数组（列表）中所有节点都存在于该二叉树中，且二叉树中所有节点的值都是互不相同的。
1676
*/
//慢
class Solution {
public:
	TreeNode* res;
    TreeNode* lowestCommonAncestor(TreeNode* root, vector<TreeNode*> &nodes) {
        dfs(root,nodes);
        return res;
    }
    int dfs(TreeNode* root, vector<TreeNode*> &nodes) {
    	if(root==nullptr){
    		return 0;
    	}
    	int inCurr=0;
    	for(int i=0;i<nodes.size();++i){
    		if(nodes[i]->val==root->val){
    			inCurr=1;
    			break;
    		}
    	}
    	int inLeft=dfs(root->left,nodes);
    	int inRight=dfs(root->right,nodes);
    	if(inCurr+inLeft+inRight==nodes.size()){
    		res=root;
			return 0;
    	}
    	return inCurr+inLeft+inRight;
    }
};
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, vector<TreeNode*> &nodes) {
		unordered_set<TreeNode*> uset(nodes.begin(),nodes.end());

    }
	TreeNode* dfs(TreeNode* root,unordered_set<TreeNode*> uset){
		if(uset.count(root)){
			return root;
		}
		if(root){
			
		}
		return nullptr;
	}
};