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
		return dfs(root,uset);
    }
	TreeNode* dfs(TreeNode* root,unordered_set<TreeNode*> uset){
		if(uset.count(root)){
			return root;
		}
		if(root){
			auto l=dfs(root->left,uset);
			auto r=dfs(root->right,uset);
			if(l&&r){
				return root;
			}else if(l){
				return l;
			}else if(r){
				return r;
			}
		}
		return nullptr;
	}
};
/* 
根据一棵树的前序遍历与中序遍历构造二叉树。
注意:
你可以假设树中没有重复的元素。
105
前序遍历是VLR,中序遍历是LVR
由此可以确定根节点和左部分，右部分
改进：可以用map记录每个值在中序遍历的位置，更快
还有迭代的做法----------
 */
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		int n=preorder.size()-1;
		return dfs(preorder,inorder,0,n,0,n);
    }
	TreeNode* dfs(vector<int>& preorder, vector<int>& inorder,int pre_b,int pre_e,int in_b,int in_e){
		if(pre_b>pre_e||in_b>in_e){
			return nullptr;
		}
		TreeNode* root=new TreeNode(preorder[pre_b]);
		int i=in_b;
		for(;i<inorder.size();i++){
			if(inorder[i]==preorder[pre_b]){
				break;
			}
		}
		int len=i-in_b;
		root->left=dfs(preorder,inorder,pre_b+1,pre_b+len,in_b,i-1);
		root->right=dfs(preorder,inorder,pre_b+len+1,pre_e,i+1,in_e);
		return root;
	}
};
/* 
根据一棵树的中序遍历与后序遍历构造二叉树。

注意:
你可以假设树中没有重复的元素。
后序为LRV
 */
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
		int n=inorder.size();
		for(int i=0;i<n;i++){
			in[inorder[i]]=i;
		}
		return dfs(inorder,postorder,0,n-1,0,n-1);
    }
	TreeNode* dfs(vector<int>& inorder, vector<int>& postorder,int in_b,int in_e,int post_b,int post_e){
		if(in_b>in_e||post_b>post_e){
			return nullptr;
		}
		TreeNode* root=new TreeNode(postorder[post_e]);
		int inv=in[postorder[post_e]];
		root->left=dfs(inorder,postorder,in_b,inv-1,post_b,post_b+inv-in_b-1);
		root->right=dfs(inorder,postorder,inv+1,in_e,post_b+inv-in_b,post_e-1);
		return root;
	}
private:
	unordered_map<int,int> in;
};
/* 
返回与给定的前序和后序遍历匹配的任何二叉树。

 pre 和 post 遍历中的值是不同的正整数。
 889
 前序VLR,后序LRV
 前序遍历的头和后序遍历的尾相同；则左子树的前的左子树的尾，所以L的长度为后L的尾-前L的头,可以知道L的长度
 */
class Solution {
public:
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
		int n=preorder.size();
		for(int i=0;i<n;i++){
			pre[preorder[i]]=i;
			post[postorder[i]]=i;
		}
		return dfs(preorder,postorder,0,n-1,0,n-1);
    }
	TreeNode* dfs(vector<int>& preorder, vector<int>& postorder,int pre_b,int pre_e,int post_b,int post_e){
		if(pre_b>pre_e||post_b>post_e){
			return nullptr;
		}
		TreeNode* root=new TreeNode(preorder[pre_b]);
		if(pre_b==pre_e||post_b==post_e){
			return root;
		}
		int len=post[preorder[pre_b+1]]-post_b;//左子树的长度
		root->left=dfs(preorder,postorder,pre_b+1,pre_b+1+len,post_b,post_b+len);
		root->right=dfs(preorder,postorder,pre_b+1+len+1,pre_e,post_b+len+1,post_e-1);
		return root;
	}
private:
	unordered_map<int,int> pre,post;
};
/* 
返回与给定前序遍历 preorder 相匹配的二叉搜索树（binary search tree）的根结点。

(回想一下，二叉搜索树是二叉树的一种，其每个节点都满足以下规则，对于 node.left 的任何后代，值总 < node.val，
而 node.right 的任何后代，值总 > node.val。此外，前序遍历首先显示节点 node 的值，然后遍历 node.left，接着遍历 node.right。）

题目保证，对于给定的测试用例，总能找到满足要求的二叉搜索树。
1008
前序遍历VLR，对应二叉搜索树中小大
 */
class Solution {
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
		return dfs(preorder,0,preorder.size()-1);
    }
	TreeNode* dfs(vector<int>& preorder,int pre_b,int pre_e){
		if(pre_b>pre_e){
			return nullptr;
		}
		TreeNode* root=new TreeNode(preorder[pre_b]);
		if(pre_b==pre_e){
			return root;
		}
		int i=pre_b;
		for(;i<=pre_e;i++){
			if(preorder[i]>preorder[pre_b]){
				break;
			}
		}
		root->left=dfs(preorder,pre_b+1,i-1);
		root->right=dfs(preorder,i,pre_e);
		return root;
	}
};
/* 
给定一个整数数组，你需要验证它是否是一个二叉搜索树正确的先序遍历序列。

你可以假定该序列中的数都是不相同的。
255
可以从上题中获取一些信息，当找到右子树时，右子树必大于根，所以当根大于右子树的任一节点时，返回false;超时！

本题也可以用单调栈----------
 */
class Solution {
public:
    bool verifyPreorder(vector<int>& preorder) {
		return dfs(preorder,0,preorder.size()-1,INT_MIN,INT_MAX);
    }
	bool dfs(vector<int>& preorder,int pre_b,int pre_e,int minval,int maxval){
		if(pre_b>pre_e){
			return true;
		}
		if(preorder[pre_b]<=minval||preorder[pre_b]>=maxval){
			return false;
		}
		int i=pre_b+1;
		for(;i<=pre_e;i++){
			if(preorder[i]>=preorder[pre_b]){
				break;
			}
		}
		return dfs(preorder,pre_b+1,i-1,minval,preorder[pre_b])&&dfs(preorder,i,pre_e,preorder[pre_b],maxval);
	}
};
/* 
我们从二叉树的根节点 root 开始进行深度优先搜索。

在遍历中的每个节点处，我们输出 D 条短划线（其中 D 是该节点的深度），然后输出该节点的值。
（如果节点的深度为 D，则其直接子节点的深度为 D + 1。根节点的深度为 0）。

如果节点只有一个子节点，那么保证该子节点为左子节点。

给出遍历输出 S，还原树并返回其根节点 root。
1028
与前面几题类似！
 */
class Solution {
public:
    TreeNode* recoverFromPreorder(string traversal) {
		int k=0,index=0,n=traversal.size();
		vector<int> preorder;
		for(int i=0;i<traversal.size();i++){
			if(traversal[i]=='-'){
				k++;
			}else{
				int num=0;
				while(i<n&&traversal[i]!='-'){
					num=num*10+traversal[i]-'0';
					i++;
				}
				dep.emplace_back(k);
				preorder.emplace_back(num);
				k=0;
				i--;
			}
		}
		return dfs(preorder,0,preorder.size()-1);
    }
	TreeNode* dfs(vector<int> preorder,int pre_b,int pre_e){
		if(pre_b>pre_e){
			return nullptr;
		}
		TreeNode* root=new TreeNode(preorder[pre_b]);
		int rd=dep[pre_b],l=-1,r=-1;
		for(int i=pre_b;i<=pre_e;i++){
			if(dep[i]==rd+1){
				if(l==-1){
					l=i;
				}else{
					r=i;
				}
			}
		}
		if(r!=-1){
            root->left=dfs(preorder,l,r-1);
			root->right=dfs(preorder,r,pre_e);
		}else{
            root->left=dfs(preorder,pre_b+1,pre_e);
        }
		return root;
	}
private:
	vector<int> dep;
};
//栈--------------后序遍历的迭代！
/* 
给你二叉树的根节点 root ，返回它节点值的 前序 遍历。
144
递归很简单，使用栈非递归
VLR
 */
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
		vector<int> res;
		stack<TreeNode*> ms;
		ms.emplace(root);
		while(!ms.empty()){
			TreeNode* node=ms.top();
			ms.pop();
			if(node==nullptr){
				continue;
			}
			res.emplace_back(node->val);
			ms.emplace(node->right);
			ms.emplace(node->left);
		}	 
		return res;
    }
};
/* 
给定一个二叉树的根节点 root ，返回它的 中序 遍历。
94
非递归
LVR
 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
		vector<int> res;
		stack<TreeNode*> ms;
		TreeNode* node=root;
		while(!ms.empty()||node!=nullptr){
			while(node){//先将左边所有节点压入栈
				ms.emplace(node);
				node=node->left;
			}
			node=ms.top();
			res.emplace_back(node->val);
			ms.pop();
			node=node->right;//递归右节点
		}
		return res;
    }
};
/* 
给定一个二叉树，返回它的 后序 遍历。
145
LRV
与VRL刚好逆序，可以先获取VRL，再翻转
 */
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
		vector<int> res;
		stack<TreeNode*> ms;
		ms.emplace(root);
		while(!ms.empty()){
			TreeNode* node=ms.top();
			ms.pop();
			if(node==nullptr){
				continue;
			}
			res.emplace_back(node->val);
			ms.emplace(node->left);
			ms.emplace(node->right);
		}	 
		reverse(res.begin(),res.end());
		return res;
    }
};
/* 
给定一个 N 叉树，返回其节点值的 前序遍历 。

N 叉树 在输入中按层序遍历进行序列化表示，每组子节点由空值 null 分隔（请参见示例）。
589
递归很简单，使用迭代？
 */
class Node {
public:
    int val;
    Node *left;//前面题用的
    Node *right;//同上
    Node *parent;//同上
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
class Solution {
public:
    vector<int> preorder(Node* root) {
        vector<int> res;
		stack<Node*> ms;
		ms.emplace(root);
		while(!ms.empty()){
			auto node=ms.top();
			ms.pop();
			if(node==nullptr){
				continue;
			}
			res.emplace_back(node->val);
			reverse(node->children.begin(),node->children.end());
			for(auto child:node->children){
				ms.emplace(child);
			}
		}
		return res;
    }
};
/*
给定一个 N 叉树，返回其节点值的 后序遍历 。

N 叉树 在输入中按层序遍历进行序列化表示，每组子节点由空值 null 分隔（请参见示例）。
590 
 */
class Solution {
public:
    vector<int> postorder(Node* root) {    
	    vector<int> res;
		stack<Node*> ms;
		ms.emplace(root);
		while(!ms.empty()){
			auto node=ms.top();
			ms.pop();
			if(node==nullptr){
				continue;
			}
			res.emplace_back(node->val);
			for(auto child:node->children){
				ms.emplace(child);
			}
		}
		reverse(res.begin(),res.end());
		return res;
    }
};	
//深度优先遍历的应用
//1-获得图（树）的一些属性,如129
//2-计算无向图的连通分量
/* 
无向图中连通分量的数目
给定编号从 0 到 n-1 的 n 个节点和一个无向边列表（每条边都是一对节点），请编写一个函数来计算无向图中连通分量的数目。
323
三种方法，这里使用DFS，感觉挺像岛屿的，感染？
 */
class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
		int res=0;
		vector<bool> visit(n,false);
		vector<vector<int>> next(n);
		for(auto edge:edges){
			next[edge[0]].emplace_back(edge[1]);
			next[edge[1]].emplace_back(edge[0]);
		}
		for(int i=0;i<n;i++){
			if(visit[i]){
				continue;
			}
			visit[i]=true;
			res++;
			dfs(next,visit,i);
		}
		return res;
    }
	void dfs(vector<vector<int>>& next,vector<bool>& visit,int n){//使用引用比传值快的多！
		for(int i:next[n]){
			if(visit[i]){
				continue;
			}
			visit[i]=true;
			dfs(next,visit,i);
		}
	}
};
//检测图中是否存在环
/* 
在本问题中, 树指的是一个连通且无环的无向图。

输入一个图，该图由一个有着N个节点 (节点值不重复1, 2, ..., N) 的树及一条附加的边构成。
附加的边的两个顶点包含在1到N中间，这条附加的边不属于树中已存在的边。

结果图是一个以边组成的二维数组。每一个边的元素是一对[u, v] ，满足 u < v，表示连接顶点u 和v的无向图的边。

返回一条可以删去的边，使得结果图是一个有着N个节点的树。如果有多个答案，则返回二维数组中最后出现的边。
答案边 [u, v] 应满足相同的格式 u < v。
684
遇上一题类似，可以用并查集，此处使用DFS
 */
class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {

    }
};
/* 
在有向图中，从某个节点和每个转向处开始出发，沿着图的有向边走。如果到达的节点是终点（即它没有连出的有向边），则停止。

如果从起始节点出发，最后必然能走到终点，就认为起始节点是 最终安全 的。
更具体地说，对于最终安全的起始节点而言，存在一个自然数 k ，无论选择沿哪条有向边行走 ，走了不到 k 步后必能停止在一个终点上。

返回一个由图中所有最终安全的起始节点组成的数组作为答案。答案数组中的元素应当按 升序 排列。

该有向图有 n 个节点，按 0 到 n - 1 编号，其中 n 是 graph 的节点数。
图以下述形式给出：graph[i] 是编号 j 节点的一个列表，满足 (i, j) 是图的一条有向边。
802
 */
class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {

    }
};
/* 
存在一个 无向图 ，图中有 n 个节点。其中每个节点都有一个介于 0 到 n - 1 之间的唯一编号。
给你一个二维数组 graph ，其中 graph[u] 是一个节点数组，由节点 u 的邻接节点组成。
形式上，对于 graph[u] 中的每个 v ，都存在一条位于节点 u 和节点 v 之间的无向边。该无向图同时具有以下属性：

    不存在自环（graph[u] 不包含 u）。
    不存在平行边（graph[u] 不包含重复值）。
    如果 v 在 graph[u] 内，那么 u 也应该在 graph[v] 内（该图是无向图）
    这个图可能不是连通图，也就是说两个节点 u 和 v 之间可能不存在一条连通彼此的路径。

二分图 定义：如果能将一个图的节点集合分割成两个独立的子集 A 和 B ，
并使图中的每一条边的两个节点一个来自 A 集合，一个来自 B 集合，就将这个图称为 二分图 。

如果图是二分图，返回 true ；否则，返回 false 。
785
 */
class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {

    }
};