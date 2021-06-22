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
//	 bool hasPathSum(TreeNode* root, int targetSum) {
// 		if(root==nullptr){
// 			if(targetSum==0){
// 				return true;
// 			}else{
// 				return false;
// 			}
// 		}
// 		return hasPathSum(root->left,targetSum-root->val)||hasPathSum(root->right,targetSum-root->val);
//	 }
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
//二分图检测
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
	bool dfs(vector<vector<int>>& graph,vector<int> &color,int i,int c){
		if(color[i]!=-1){//已染色
			return color[i]==c;//它的邻居肯定已经染色了，判断即可返回，
		}
		color[i]=c;
		for(int next:graph[i]){
			if(dfs(graph,color,next,!c)==false){
				return false;
			}
		}
		return true;
	}
	bool isBipartite(vector<vector<int>>& graph) {
		int n=graph.size();
		vector<int> color(n,-1);
		for(int i=0;i<n;i++){
			if(color[i]==-1){//如果节点未染色
				if(dfs(graph,color,i,0)==false){//染色失败直接返回失败
					return false;
				}
			}
		}
		return true;
	}
};
/* 
给定一组 N 人（编号为 1, 2, ..., N）， 我们想把每个人分进任意大小的两组。

每个人都可能不喜欢其他人，那么他们不应该属于同一组。

形式上，如果 dislikes[i] = [a, b]，表示不允许将编号为 a 和 b 的人归入同一组。

当可以用这种方法将所有人分进两组时，返回 true；否则返回 false。
886
 */
class Solution {
public:
	bool dfs(vector<vector<int>>& next,vector<int>& color,int i,int c){
		if(color[i]!=-1){
			return color[i]==c;
		}
		color[i]=c;
		for(int j:next[i]){
			if(false==dfs(next,color,j,!c)){
				return false;
			}
		}
		return true;
	}
	bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
		vector<vector<int>> next(n+1);
		vector<int> color(n+1,-1);
		for(auto vec:dislikes){
			next[vec[0]].emplace_back(vec[1]);
			next[vec[1]].emplace_back(vec[0]);
		}
		for(int i=1;i<n+1;i++){
			if(color[i]==-1){
				if(false==dfs(next,color,i,0)){
					return false;
				}
			}
		}
		return true;
	}
};
//回溯
//1-排列 组合 子集等问题
/* 
给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。
46
使用visit数组标记已经访问过的下标
 */
class Solution {
public:
	vector<vector<int>> res;
	vector<int> temp;
	vector<vector<int>> permute(vector<int>& nums) {
		vector<int> visit(nums.size(),0);
		dfs(nums,visit);
		return res;
	}
	void dfs(vector<int>& nums,vector<int> visit){
		if(temp.size()==nums.size()){
			res.emplace_back(temp);
			return;
		}
		for(int i=0;i<nums.size();i++){
			if(visit[i]==1){
				continue;
			}
			visit[i]=1;
			temp.emplace_back(nums[i]);
			dfs(nums,visit);
			temp.pop_back();
			visit[i]=0;
		}
	}
};
/* 
给定一个可包含重复数字的序列 nums ，按任意顺序 返回所有不重复的全排列。
47
与上题不同的是，此题存在重复数字！
 */
class Solution {
public:
	vector<vector<int>> res;
	vector<int> temp,visit;
	vector<vector<int>> permuteUnique(vector<int>& nums) {
		visit.resize(nums.size());
		sort(nums.begin(),nums.end());
		dfs(nums);
		return res;
	}
	void dfs(vector<int> &nums){
		if(temp.size()==nums.size()){
			res.emplace_back(temp);
			return;
		}
		for(int i=0;i<nums.size();i++){
			if(visit[i]==1||i>0&&nums[i]==nums[i-1]&&visit[i-1]==0){//如果i和i-1相同，那么只存在都拿或者只拿前者
				continue;//前者未拿的情况也不能拿这个
			}
			temp.emplace_back(nums[i]);
			visit[i]=1;
			dfs(nums);
			temp.pop_back();
			visit[i]=0;
		}
	}
};
/* 
给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的数字可以无限制重复被选取。
39
 */
class Solution {
public:
	vector<vector<int>> res;
	vector<int> temp;
	vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
		dfs(candidates,target,0);
		return res;
	}
	void dfs(vector<int>& candidates,int target,int index){
		if(target<=0){
			if(target==0){
				res.emplace_back(temp);
			}
			return;
		}
		for(int i=index;i<candidates.size();i++){
			temp.emplace_back(candidates[i]);
			dfs(candidates,target-candidates[i],i);
			temp.pop_back();
		}
	}
};
/* 
给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的每个数字在每个组合中只能使用一次。

说明：
	所有数字（包括目标数）都是正整数。
	解集不能包含重复的组合。 
40
存在重复元素
 */
class Solution {
public:
	vector<vector<int>> res;
	vector<int> temp,visit;
	vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
		visit.resize(candidates.size());
		sort(candidates.begin(),candidates.end());
		dfs(candidates,target,0);
		return res;
	}
	void dfs(vector<int>& candidates,int target,int index){
		if(target<=0){
			if(target==0){
				res.emplace_back(temp);
			}
			return;
		}
		for(int i=index;i<candidates.size();i++){
			/* if(i>0&&candidates[i-1]==candidates[i]&&visit[i-1]==0){//这样可以，与排列的相同
				continue;
			} */
			if(i>index&&candidates[i-1]==candidates[i]){//本轮选择过的不再重复，与排列不同的是，从index开始选择的，前面的自然排除
				continue;
			}
			temp.emplace_back(candidates[i]);
			visit[i]=1;
			dfs(candidates,target-candidates[i],i+1);
			visit[i]=0;
			temp.pop_back();
		}
	}
};
/* 
给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合。
77
前两题的中和，非重复数组不无限选
 */
class Solution {
public:
	vector<vector<int>> res;
	vector<int> temp;
	vector<vector<int>> combine(int n, int k) {
		dfs(n,1,k);
		return res;
	}
	void dfs(int n,int index,int k){
		if(temp.size()==k){
			res.emplace_back(temp);
			return;
		}
		for(int i=index;i<=n;i++){
			temp.emplace_back(i);
			dfs(n,i+1,k);
			temp.pop_back();
		}
	}
};
/* 
二进制手表顶部有 4 个 LED 代表 小时（0-11），底部的 6 个 LED 代表 分钟（0-59）。每个 LED 代表一个 0 或 1，最低位在右侧。
给你一个整数 turnedOn ，表示当前亮着的 LED 的数量，返回二进制手表可以表示的所有可能时间。你可以 按任意顺序 返回答案。
小时不会以零开头：
	例如，"01:00" 是无效的时间，正确的写法应该是 "1:00" 。
分钟必须由两位数组成，可能会以零开头：
	例如，"10:2" 是无效的时间，正确的写法应该是 "10:02" 。
401
本题除了爆搜，还有其他做法，更牛逼--------------
 */
class Solution {
public:
	vector<string> res;
	int hour,min;
	vector<string> readBinaryWatch(int turnedOn) {
		dfs(turnedOn,1);
		return res;
	}
	void dfs(int turnedOn,int index){
		if(turnedOn==0){
			if(hour<=11&&min<=59){
				string temp=to_string(hour);
				temp+=":";
				if(min<10){
					temp+="0";
				}
				temp+=to_string(min);
				res.emplace_back(temp);
			}
			return;
		}
		for(int i=index;i<=10;i++){
			if(i>4){
				min+=pow(2,i-5);
			}else{
				hour+=pow(2,i-1);
			}
			dfs(turnedOn-1,i+1);
			if(i>4){
				min-=pow(2,i-5);
			}else{
				hour-=pow(2,i-1);
			}
		}
	}
};
/* 
给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。

解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。
78
 */
class Solution {
public:
	vector<vector<int>> res;
	vector<int> temp;
	vector<vector<int>> subsets(vector<int>& nums) {
		dfs(nums,0);
		return res;
	}
	void dfs(vector<int>& nums,int index){
		res.emplace_back(temp);
		for(int i=index;i<nums.size();i++){
			temp.emplace_back(nums[i]);
			dfs(nums,i+1);
			temp.pop_back();
		}
	}
};
/* 
给你一个整数数组 nums ，其中可能包含重复元素，请你返回该数组所有可能的子集（幂集）。

解集 不能 包含重复的子集。返回的解集中，子集可以按 任意顺序 排列。
90
与上题不同的是：存在重复元素
 */
class Solution {
public:
	vector<vector<int>> res;
	vector<int> temp;
	vector<vector<int>> subsetsWithDup(vector<int>& nums) {
		sort(nums.begin(),nums.end());
		dfs(nums,0);
		return res;
	}
	void dfs(vector<int>& nums,int index){
		res.emplace_back(temp);
		for(int i=index;i<nums.size();i++){
			if(i>index&&nums[i]==nums[i-1]){
				continue;
			}
			temp.emplace_back(nums[i]);
			dfs(nums,i+1);
			temp.pop_back();
		}
	}
};
/* 
给出集合 [1,2,3,...,n]，其所有元素共有 n! 种排列。

按大小顺序列出所有排列情况，并一一标记，当 n = 3 时, 所有排列如下：

	"123"
	"132"
	"213"
	"231"
	"312"
	"321"

给定 n 和 k，返回第 k 个排列。
有数学方法，此处使用回溯----------------
60
 */
class Solution {
public:
	vector<int> visit;
	string res,temp;
	int index;
	string getPermutation(int n, int k) {
		visit.resize(n+1);
		index=k;
		dfs(n);
		return res;
	}
	void dfs(int n){
		if(index==0){//当找到后，不必再去看后面的全排列，明显加快
			return;
		}
		if(temp.size()==n){
			if(--index==0){
				res=temp;
			}
			return;
		}
		for(int i=1;i<=n;i++){
			if(visit[i]==1){
				continue;
			}
			visit[i]=1;
			temp+=i+'0';
			dfs(n);
			temp.pop_back();
			visit[i]=0;
		}
	}
};
/* 
给定一个只包含数字的字符串，用以表示一个 IP 地址，返回所有可能从 s 获得的 有效 IP 地址 。你可以按任何顺序返回答案。

有效 IP 地址 正好由四个整数（每个整数位于 0 到 255 之间组成，且不能含有前导 0），整数之间用 '.' 分隔。

例如："0.1.2.201" 和 "192.168.1.1" 是 有效 IP 地址，但是 "0.011.255.245"、"192.168.1.312" 和 "192.168@1.1" 是 无效 IP 地址。
93
 */
class Solution {
public:
	vector<string> res;
	vector<string> temp;
	vector<string> restoreIpAddresses(string s) {
		dfs(s,0);
		return res;
	}
	void dfs(string s,int index){
		if(s.size()-index>3*(4-temp.size())){//如果尾巴大于指定值，则直接返回，超出长度
			return;
		}
		if(index>=s.size()){
			if(temp.size()==4&&index==s.size()){
				string str="";
				for(string s:temp){
					str+=s+".";
				}
				str.pop_back();
				res.emplace_back(str);
			}
			return;
		}
		for(int i=1;i<=3;i++){
			string str=s.substr(index,i);
			int k=atoi(str.c_str());
			if(i>1&&str[0]=='0'||k>255){//前置0或者大于255
				return;
			}
			temp.emplace_back(str);
			dfs(s,index+i);
			temp.pop_back();
		}
	}
};
/* 
给定一个整数数组  nums 和一个正整数 k，找出是否有可能把这个数组分成 k 个非空子集，其总和都相等。
698
 */
class Solution {
public:
	bool res=false;
	vector<int> visit;
	bool canPartitionKSubsets(vector<int>& nums, int k) {
		int sum=accumulate(nums.begin(),nums.end(),0);
		if(sum%k){
			return false;
		}
		sort(nums.begin(),nums.end());
		visit.resize(nums.size());
		int target=sum/k;
		dfs(nums,target,0,0,k);
		return res;
	}
	void dfs(vector<int>& nums,int target,int sum,int index,int k){
		if(k==1){
			res=true;
			return;
		}
		if(sum==target){
			dfs(nums,target,0,0,k-1);
		}
		for(int i=index;i<nums.size();i++){
			if(visit[i]==1||i>0&&nums[i-1]==nums[i]&&visit[i-1]==0){
				continue;
			}
			visit[i]=1;
			dfs(nums,target,sum+nums[i],i+1,k);
			visit[i]=0;
		}
	}
};
//字符串回溯问题
/* 
给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。

给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。
17
 */
class Solution {
public:
	vector<string> res;
	string temp;
	vector<string> words={"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
	vector<string> letterCombinations(string digits) {
		dfs(digits,0);
		return res;
	}
	void dfs(string digits,int index){
		if(index==digits.size()){
			if(index!=0){
				res.emplace_back(temp);
			}
			return;
		}
		for(int i=0;i<words[digits[index]-'0'].size();i++){
			temp+=words[digits[index]-'0'][i];
			dfs(digits,index+1);
			temp.pop_back();
		}
	}
};
/* 
数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
22
本题在广度搜索分类中提到过，此处使用回溯来做
 */
class Solution {
public:
	vector<string> res;
	string temp;
	vector<string> generateParenthesis(int n) {
		dfs(n,n);
		return res;
	}
	void dfs(int left,int right){
		if(left==0&&right==0){
			res.emplace_back(temp);
			return;
		}
		if(left>0){
			temp+="(";
			dfs(left-1,right);
			temp.pop_back();
		}
		if(right>left){
			temp+=")";
			dfs(left,right-1);
			temp.pop_back();
		}
	}
};
/* 
给定一个字符串S，通过将字符串S中的每个字母转变大小写，我们可以获得一个新的字符串。返回所有可能得到的字符串集合。
	S 的长度不超过12。
	S 仅由数字和字母组成。
784
 */
class Solution {
public:
	vector<string> res;
	string temp;
	vector<string> letterCasePermutation(string s) {
		dfs(s,0);
		return res;
	}
	void dfs(string s,int index){
		if(temp.size()==s.size()){
			res.emplace_back(temp);
			return;
		}
		temp+=tolower(s[index]);
		dfs(s,index+1);
		temp.pop_back();
		if(s[index]>'9'||s[index]<'0'){
			temp+=toupper(s[index]);
			dfs(s,index+1);
			temp.pop_back();
		}
	}
};
/* 
输入一个字符串，打印出该字符串中字符的所有排列。

你可以以任意顺序返回这个字符串数组，但里面不能有重复元素。
剑指38
求排列就知道大概率是回溯
 */
class Solution {
public:
	vector<string> res;
	string temp;
	vector<int> visit;
	vector<string> permutation(string s) {
		visit.resize(s.size());
		sort(s.begin(),s.end());
		dfs(s);
		return res;
	}
	void dfs(string s){
		if(temp.size()==s.size()){
			res.emplace_back(temp);
			return;
		}
		for(int i=0;i<s.size();i++){
			if(visit[i]==1||i>0&&s[i]==s[i-1]&&visit[i-1]==0){
				continue;
			}
			visit[i]=1;
			temp+=s[i];
			dfs(s);
			visit[i]=0;
			temp.pop_back();
		}
	}
};
/*
给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是 回文串 。返回 s 所有可能的分割方案。
回文串 是正着读和反着读都一样的字符串。
131
*/
class Solution {
public:
    vector<vector<string>> partition(string s) {

    }
};
//游戏问题
/* 
编写一个程序，通过填充空格来解决数独问题。

数独的解法需 遵循如下规则：

	数字 1-9 在每一行只能出现一次。
	数字 1-9 在每一列只能出现一次。
	数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。（请参考示例图）

数独部分空格内已填入了数字，空白格用 '.' 表示。
37
 */
/* 
n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。

给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。

每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。
51
 */
class Solution {
public:
	vector<vector<string>> solveNQueens(int n) {

	}
};
/* 
回忆一下祖玛游戏。现在桌上有一串球，颜色有红色(R)，黄色(Y)，蓝色(B)，绿色(G)，还有白色(W)。 现在你手里也有几个球。

每一次，你可以从手里的球选一个，然后把这个球插入到一串球中的某个位置上（包括最左端，最右端）。接着，如果有出现三个或者三个以上颜色相同的球相连的话，就把它们移除掉。重复这一步骤直到桌上所有的球都被移除。

找到插入并可以移除掉桌上所有球所需的最少的球数。如果不能移除桌上所有的球，输出 -1 。
488
 */
class Solution {
public:
	int findMinStep(string board, string hand) {

	}
};
/* 
让我们一起来玩扫雷游戏！

给定一个代表游戏板的二维字符矩阵。 'M' 代表一个未挖出的地雷，'E' 代表一个未挖出的空方块，'B' 代表没有相邻（上，下，左，右，和所有4个对角线）地雷的已挖出的空白方块，数字（'1' 到 '8'）表示有多少地雷与这块已挖出的方块相邻，'X' 则表示一个已挖出的地雷。

现在给出在所有未挖出的方块中（'M'或者'E'）的下一个点击位置（行和列索引），根据以下规则，返回相应位置被点击后对应的面板：

	如果一个地雷（'M'）被挖出，游戏就结束了- 把它改为 'X'。
	如果一个没有相邻地雷的空方块（'E'）被挖出，修改它为（'B'），并且所有和其相邻的未挖出方块都应该被递归地揭露。
	如果一个至少与一个地雷相邻的空方块（'E'）被挖出，修改它为数字（'1'到'8'），表示相邻地雷的数量。
	如果在此次点击中，若无更多方块可被揭露，则返回面板。
529
 */
class Solution {
public:
	vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {

	}
};
//剪枝
/* 
还记得童话《卖火柴的小女孩》吗？现在，你知道小女孩有多少根火柴，请找出一种能使用所有火柴拼成一个正方形的方法。
不能折断火柴，可以把火柴连接起来，并且每根火柴都要用到。

输入为小女孩拥有火柴的数目，每根火柴用其长度表示。输出即为是否能用所有的火柴拼成正方形。

473
698的简化题，分为四个集合！
 */
class Solution {
public:
	bool res=false;
	vector<int> visit;
	bool makesquare(vector<int>& matchsticks) {
		int sum=accumulate(matchsticks.begin(),matchsticks.end(),0);
		if(sum%4!=0){
			return false;
		}
		visit.resize(matchsticks.size());
		sort(matchsticks.begin(),matchsticks.end());
		dfs(matchsticks,sum/4,0,0,4);
		return res;
	}
	void dfs(vector<int> &nums,int target,int sum,int index,int k){
		if(k==1){
			res=true;
			return;
		}
		if(sum==target){
			dfs(nums,target,0,0,k-1);
		}
		for(int i=index;i<nums.size();i++){
			if(visit[i]==1||i>0&&nums[i]==nums[i-1]&&visit[i-1]==0){
				continue;
			}
			if(sum+nums[i]>target){
				break;
			}
			visit[i]=1;
			dfs(nums,target,sum+nums[i],i+1,k);
			visit[i]=0;
		}
	}
};
/* 
给你一个字符串 s ，请你拆分该字符串，并返回拆分后唯一子字符串的最大数目。

字符串 s 拆分后可以得到若干 非空子字符串 ，这些子字符串连接后应当能够还原为原字符串。但是拆分出来的每个子字符串都必须是 唯一的 。

注意：子字符串 是字符串中的一个连续字符序列。
1593
 */
class Solution {
public:
	int res=-1;
	int temp=0;
	unordered_set<string> us;
	int maxUniqueSplit(string s) {
		dfs(s,0);
		return res;
	}
	void dfs(string s,int index){
		if(index==s.size()){
			res=max(res,temp);
			return;
		}
		int k=s.size()-index;
		if(temp+k<=res){//剪枝，如果未分割的挨个分也不超过res，则可以放弃这条路
			return;
		}
		for(int i=index+1;i<=s.size();i++){
			string str=s.substr(index,i-index);
			if(!us.count(str)){
				us.emplace(str);
				temp++;
				dfs(s,i);
				temp--;
				us.erase(str);
			}
		}
	}
};
/* 
你有一套活字字模 tiles，其中每个字模上都刻有一个字母 tiles[i]。返回你可以印出的非空字母序列的数目。

注意：本题中，每个活字字模只能使用一次。
1079
方案一：先找出子集，然后每个子集的全排列个数
方案二：全排列那题查找是等长度为源字符串长，而只要每个不为0的长度记录下来就是所有长度的全排列了！
 */
class Solution {
public:
	int res=0;
	vector<int> visit;
	int numTilePossibilities(string tiles) {
		sort(tiles.begin(),tiles.end());
		visit.resize(tiles.size());
		dfs(tiles);
		return res;
	}
	void dfs(string tiles){
		for(int i=0;i<tiles.size();i++){
			if(visit[i]==1||i>0&&tiles[i]==tiles[i-1]&&visit[i-1]==0){
				continue;
			}
			visit[i]=1;
			res++;
			dfs(tiles);
			visit[i]=0;
		}
	}
};
//二维平面搜索(岛屿问题的衍生和合集)
/* 
给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。
同一个单元格内的字母不允许被重复使用。
79
应该也是可以用BFS的
 */
class Solution {
public:
	const vector<pair<int, int>> directions{{0, 1},{1, 0},{0, -1},{-1, 0}};
	bool exist(vector<vector<char>>& board, string word) {
		for(int i=0;i<board.size();++i){
			for(int j=0;j<board[0].size();++j){
				if(board[i][j]==word[0]){
					if(dfs(board,word,i,j,0)){
						return true;
					}
				}
			}
		}
		return false;
	}
	bool dfs(vector<vector<char>>& board,string& word,int i,int j,int k){
		if(k==word.size()){
			return true;
		}
		if(i<0||j<0||i>=board.size()||j>=board[i].size()||board[i][j]!=word[k]||board[i][j]=='#'){
			return false;
		}
		board[i][j]='#';
		if(dfs(board,word,i,j-1,k+1)){
			return true;
		}
		if(dfs(board,word,i-1,j,k+1)){
			return true;
		}
		if(dfs(board,word,i,j+1,k+1)){
			return true;
		}
		if(dfs(board,word,i+1,j,k+1)){
			return true;
		}
		board[i][j]=word[k];
		return false;
	}
};
/* 
给你一个 m x n 的矩阵 board ，由若干字符 'X' 和 'O' ，找到所有被 'X' 围绕的区域，并将这些区域里所有的 'O' 用 'X' 填充。 
130
 */
class Solution {
public:
    void solve(vector<vector<char>>& board) {

    }
};
/* 
给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。

岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。

此外，你可以假设该网格的四条边均被水包围。
200
 */
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {

    }
};
/* 
给定一个 m x n 的非负整数矩阵来表示一片大陆上各个单元格的高度。“太平洋”处于大陆的左边界和上边界，而“大西洋”处于大陆的右边界和下边界。

规定水流只能按照上、下、左、右四个方向流动，且只能从高到低或者在同等高度上流动。

请找出那些水流既可以流动到“太平洋”，又能流动到“大西洋”的陆地单元的坐标。

 

提示：

    输出坐标的顺序不重要
    m 和 n 都小于150
417
 */
class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {

    }
};
/* 
有一幅以二维整数数组表示的图画，每一个整数表示该图画的像素值大小，数值在 0 到 65535 之间。

给你一个坐标 (sr, sc) 表示图像渲染开始的像素值（行 ，列）和一个新的颜色值 newColor，让你重新上色这幅图像。

为了完成上色工作，从初始坐标开始，记录初始坐标的上下左右四个方向上像素值与初始坐标相同的相连像素点，
接着再记录这四个方向上符合条件的像素点与他们对应四个方向上像素值与初始坐标相同的相连像素点，……，重复该过程。
将所有有记录的像素点的颜色值改为新的颜色值。

最后返回经过上色渲染后的图像。
733
 */
class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {

    }
};
/* 
给出一个二维数组 A，每个单元格为 0（代表海）或 1（代表陆地）。

移动是指在陆地上从一个地方走到另一个地方（朝四个方向之一）或离开网格的边界。

返回网格中无法在任意次数的移动中离开网格边界的陆地单元格的数量。
1020
 */
class Solution {
public:
    int numEnclaves(vector<vector<int>>& grid) {

    }
};
/* 
给出一个二维整数网格 grid，网格中的每个值表示该位置处的网格块的颜色。

只有当两个网格块的颜色相同，而且在四个方向中任意一个方向上相邻时，它们属于同一连通分量。

连通分量的边界是指连通分量中的所有与不在分量中的正方形相邻（四个方向上）的所有正方形，
或者在网格的边界上（第一行/列或最后一行/列）的所有正方形。

给出位于 (r0, c0) 的网格块和颜色 color，使用指定颜色 color 为所给网格块的连通分量的边界进行着色，并返回最终的网格 grid 。
1034
 */
class Solution {
public:
    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int r0, int c0, int color) {

    }
};
/* 
有一个二维矩阵 grid ，每个位置要么是陆地（记号为 0 ）要么是水域（记号为 1 ）。

我们从一块陆地出发，每次可以往上下左右 4 个方向相邻区域走，能走到的所有陆地区域，我们将其称为一座「岛屿」。

如果一座岛屿 完全 由水域包围，即陆地边缘上下左右所有相邻区域都是水域，那么我们将其称为 「封闭岛屿」。

请返回封闭岛屿的数目。
1254
 */
class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {

    }
};
/*
在二维地图上， 0代表海洋， 1代表陆地，我们最多只能将一格 0 海洋变成 1变成陆地。
进行填海之后，地图上最大的岛屿面积是多少？（上、下、左、右四个方向相连的 1 可形成岛屿）
827------欠优
*/
class Solution {
public:
    vector<pair<int,int>> dir={{0,1},{0,-1},{1,0},{-1,0}};
    int largestIsland(vector<vector<int>>& grid) {
        int k=2,res=0;
        map<int,int> mapS;
        for(int i=0;i<grid.size();++i){
            for(int j=0;j<grid[0].size();++j){
                if(grid[i][j]==1){
                    int s=0;
                    dfs(grid,i,j,k++,s);
                    mapS[k-1]=s;
                    res=max(s,res);
                }
            }
        }
        for(int i=0;i<grid.size();++i){
            for(int j=0;j<grid[0].size();++j){
                if(grid[i][j]==0){
                    set<int> setIndex;
                    for(auto[x,y]:dir){
                        setIndex.insert(nextS(grid,i+x,j+y));
                    }
                    int S=0;
                    for(auto index:setIndex){
                        S+=mapS[index];
                    }
                    res=max(res,S+1);
                }
            }
        }
        return res;
    }
    int nextS(vector<vector<int>>& grid,int i,int j){
        if(i<0||i>=grid.size()||j<0||j>=grid[0].size()||grid[i][j]==0){
            return 0;
        }
        return grid[i][j];
    }
    void dfs(vector<vector<int>>& grid,int i,int j,int k,int &s){
        if(i<0||i>=grid.size()||j<0||j>=grid[0].size()||grid[i][j]!=1){
            return;
        }
        grid[i][j]=k;
        s++;
        for(auto[x,y]:dir){
            dfs(grid,i+x,j+y,k,s);
        }
    }
};
/*
给定一个 row x col 的二维网格地图 grid ，其中：grid[i][j] = 1 表示陆地， grid[i][j] = 0 表示水域。
网格中的格子 水平和垂直 方向相连（对角线方向不相连）。整个网格被水完全包围，但其中恰好有一个岛屿（或者说，一个或多个表示陆地的格子相连组成的岛屿）。
岛屿中没有“湖”（“湖” 指水域在岛屿内部且不和岛屿周围的水相连）。格子是边长为 1 的正方形。网格为长方形，且宽度和高度均不超过 100 。计算这个岛屿的周长
463
*/
class Solution {
public:
    vector<pair<int,int>> dir={{0,1},{0,-1},{1,0},{-1,0}};
    int islandPerimeter(vector<vector<int>>& grid) {
        int res=0;
        for(int i=0;i<grid.size();++i){
            for(int j=0;j<grid[0].size();++j){
                if(grid[i][j]==1){
                    dfs(grid,i,j,res);
                    return res;
                }
            }
        }
        return 0;
    }
    void dfs(vector<vector<int>>& grid,int i,int j,int &C){
        if(i<0||i>=grid.size()||j<0||j>=grid[0].size()||grid[i][j]!=1){
            return;
        }
        grid[i][j]=2;
        C+=4;
        for(auto[x,y]:dir){
            if(next(grid,i+x,j+y)){
                C--;
            }
        }
        for(auto[x,y]:dir){
            dfs(grid,i+x,j+y,C);
        }
    }
    bool next(vector<vector<int>>& grid,int i,int j){
        if(i<0||i>=grid.size()||j<0||j>=grid[0].size()||grid[i][j]==0){
            return false;
        }
        return true;
    }
};
/*
给定一个包含了一些 0 和 1 的非空二维数组 grid 。
一个 岛屿 是由一些相邻的 1 (代表土地) 构成的组合，这里的「相邻」要求两个 1 必须在水平或者竖直方向上相邻。你可以假设 grid 的四个边缘都被 0（代表水）包围着。
找到给定的二维数组中最大的岛屿面积。(如果没有岛屿，则返回面积为 0 。)
695
*/
class Solution {
public:
    vector<pair<int,int>> dir={{0,1},{0,-1},{1,0},{-1,0}};
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int res=0;
        for(int i=0;i<grid.size();++i){
            for(int j=0;j<grid[0].size();++j){
                if(grid[i][j]==1){
                    int s=0;
                    dfs(grid,i,j,s);
                    res=max(s,res);
                }
            }
        }
        return res;
    }
    void dfs(vector<vector<int>>& grid,int i,int j,int &s){
        if(i<0||i>=grid.size()||j<0||j>=grid[0].size()||grid[i][j]!=1){
            return;
        }
        grid[i][j]=2;
        s++;
        for(auto[x,y]:dir){
            dfs(grid,i+x,j+y,s);
        }
    }
};
/* 
给你无向 连通 图中一个节点的引用，请你返回该图的 深拷贝（克隆）。

图中的每个节点都包含它的值 val（int） 和其邻居的列表（list[Node]）。

class Node {
    public int val;
    public List<Node> neighbors;
}

 

测试用例格式：

简单起见，每个节点的值都和它的索引相同。例如，第一个节点值为 1（val = 1），第二个节点值为 2（val = 2），
以此类推。该图在测试用例中使用邻接列表表示。

邻接列表 是用于表示有限图的无序列表的集合。每个列表都描述了图中节点的邻居集。

给定节点将始终是图中的第一个节点（值为 1）。你必须将 给定节点的拷贝 作为对克隆图的引用返回。
133
 */
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    Node* cloneGraph(Node* node) {
        
    }
};
/* 
地上有一个m行n列的方格，从坐标 [0,0] 到坐标 [m-1,n-1] 。
一个机器人从坐标 [0, 0] 的格子开始移动，它每次可以向左、右、上、下移动一格（不能移动到方格外），
也不能进入行坐标和列坐标的数位之和大于k的格子。
例如，当k为18时，机器人能够进入方格 [35, 37] ，因为3+5+3+7=18。但它不能进入方格 [35, 38]，因为3+5+3+8=19。
请问该机器人能够到达多少个格子？
剑指13
 */
class Solution {
public:
    int movingCount(int m, int n, int k) {

    }
};