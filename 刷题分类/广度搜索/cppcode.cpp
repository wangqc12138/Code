#include "head.h"
//广度优先遍历
/* 
给你一个二叉树，请你返回其按 层序遍历 得到的节点值。 （即逐层地，从左到右访问所有节点）。
102
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
		queue<TreeNode*> mq;
		vector<vector<int>> res;
        if(root==nullptr){
            return res;
        }
		mq.push(root);
		while(!mq.empty()){
			int n=mq.size();
			vector<int> temp;
			for(int i=0;i<n;i++){
				TreeNode* node=mq.front();
				mq.pop();
				temp.push_back(node->val);
				if(node->left){
					mq.push(node->left);
				}
				if(node->right){
					mq.push(node->right);
				}
			}
			res.push_back(temp);
		}
        return res;
    }
};
/* 
无向图中连通分量的数目
323
有三种方法
DFS
BFS
unionfindset
 */
class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {

    }
};
/* 
给定一个二叉树，返回其节点值自底向上的层序遍历。 （即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历）
107
 */
class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
		queue<TreeNode*> mq;
		stack<vector<int>> ms;
		vector<vector<int>> res;
		if(root){
			mq.push(root);
		}
		while(!mq.empty()){
			int n=mq.size();
			vector<int> temp;
			for(int i=0;i<n;i++){
				TreeNode* node=mq.front();
				mq.pop();
				temp.push_back(node->val);
				if(node->left){
					mq.push(node->left);
				}
				if(node->right){
					mq.push(node->right);
				}
			}
			ms.push(temp);
		}
		while(!ms.empty()){
			res.push_back(ms.top());
			ms.pop();
		}
		return res;
    }
};
/* 
从上到下打印出二叉树的每个节点，同一层的节点按照从左到右的顺序打印。
剑指 Offer 32 - I.
 */
class Solution {
public:
    vector<int> levelOrder(TreeNode* root) {
		queue<TreeNode*> mq;
		vector<int> res;
		if(root){
			mq.push(root);
		}
		while(!mq.empty()){
			TreeNode* node=mq.front();
			mq.pop();
			res.push_back(node->val);
			if(node->left){
				mq.push(node->left);
			}
			if(node->right){
				mq.push(node->right);
			}
		}
		return res;
    }
};
/* 
从上到下按层打印二叉树，同一层的节点按从左到右的顺序打印，每一层打印到一行。
剑指 Offer 32 - II.
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
		queue<TreeNode*> mq;
		vector<vector<int>> res;
        if(root==nullptr){
            return res;
        }
		mq.push(root);
		while(!mq.empty()){
			int n=mq.size();
			vector<int> temp;
			for(int i=0;i<n;i++){
				TreeNode* node=mq.front();
				mq.pop();
				temp.push_back(node->val);
				if(node->left){
					mq.push(node->left);
				}
				if(node->right){
					mq.push(node->right);
				}
			}
			res.push_back(temp);
		}
        return res;
    }
};
/* 
请实现一个函数按照之字形顺序打印二叉树，
即第一行按照从左到右的顺序打印，第二层按照从右到左的顺序打印，第三行再按照从左到右的顺序打印，其他行以此类推。
剑指 Offer 32 - III.
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
		queue<TreeNode*> mq;
		vector<vector<int>> res;
		bool k=true;
        if(root){
			mq.push(root);
        }
		while(!mq.empty()){
			int n=mq.size();
			vector<int> temp;
			for(int i=0;i<n;i++){
				TreeNode* node=mq.front();
				mq.pop();
				temp.push_back(node->val);
				if(node->left){
					mq.push(node->left);
				}
				if(node->right){
					mq.push(node->right);
				}
			}
			if(!k){
				reverse(temp.begin(),temp.end());
			}
			res.push_back(temp);
			k=!k;
		}
        return res;
    }
};
/* 
给定一个二叉树，返回其节点值的锯齿形层序遍历。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。
103
 */
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
		queue<TreeNode*> mq;
		vector<vector<int>> res;
		bool k=true;
        if(root){
			mq.push(root);
        }
		while(!mq.empty()){
			int n=mq.size();
			vector<int> temp;
			for(int i=0;i<n;i++){
				TreeNode* node=mq.front();
				mq.pop();
				temp.push_back(node->val);
				if(node->left){
					mq.push(node->left);
				}
				if(node->right){
					mq.push(node->right);
				}
			}
			if(!k){
				reverse(temp.begin(),temp.end());
			}
			res.push_back(temp);
			k=!k;
		}
        return res;
    }
};
/* 
给定一个 N 叉树，返回其节点值的层序遍历。（即从左到右，逐层遍历）。
树的序列化输入是用层序遍历，每组子节点都由 null 值分隔（参见示例）。
429
 */
class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        queue<Node*> mq;
		vector<vector<int>> res;
		if(root){
			mq.push(root);
		}
		while(!mq.empty()){
			int n=mq.size();
			vector<int> temp;
			for(int i=0;i<n;i++){
				Node* node=mq.front();
				mq.pop();
				temp.push_back(node->val);
				for(auto m:node->children){
					if(m){
						mq.push(m);
					}
				}
			}
			res.push_back(temp);
		}
		return res;
    }
};
/* 
在二叉树中，根节点位于深度 0 处，每个深度为 k 的节点的子节点位于深度 k+1 处。
如果二叉树的两个节点深度相同，但 父节点不同 ，则它们是一对堂兄弟节点。
我们给出了具有唯一值的二叉树的根节点 root ，以及树中两个不同节点的值 x 和 y 。
只有与值 x 和 y 对应的节点是堂兄弟节点时，才返回 true 。否则，返回 false。
993
 */
class Solution {
public:
    bool isCousins(TreeNode* root, int x, int y) {
        queue<TreeNode*> mq;
		mq.push(root);
		bool k=false,l=false;
		while(!mq.empty()){
			int n=mq.size();
			for(int i=0;i<n;i++){
				TreeNode* node=mq.front();
				mq.pop();
				if(node==nullptr){
					if(k){
						l=true;
					}
					continue;
				}
				if(node->val==x||node->val==y){
					if(!k){
						k=true;
					}
					if(l){
						return true;
					}
				}
				mq.push(node->left);
				mq.push(node->right);
				mq.push(nullptr);
			}
		}
		return false;
    }
};
/* 
给定一个包含了一些 0 和 1 的非空二维数组 grid 。

一个 岛屿 是由一些相邻的 1 (代表土地) 构成的组合，这里的「相邻」要求两个 1 必须在水平或者竖直方向上相邻。
你可以假设 grid 的四个边缘都被 0（代表水）包围着。

找到给定的二维数组中最大的岛屿面积。(如果没有岛屿，则返回面积为 0 。)
695
 */
//DFS非递归
class Solution {
public:
	vector<pair<int,int>> dir={{0,1},{0,-1},{1,0},{-1,0}};
    int maxAreaOfIsland(vector<vector<int>>& grid) {
		stack<pair<int,int>> ms;
		int res=0;
		int m=grid.size(),n=grid[0].size();
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				if(grid[i][j]==0){
					continue;
				}
				grid[i][j]=0;
				int s=1;
				ms.push({i,j});
				while(!ms.empty()){
					int x=ms.top().first;
					int y=ms.top().second;
					ms.pop();
					for(auto [a,b]:dir){
						int c=a+x;
						int d=b+y;
						if(c<0||c>=m||d<0||d>=n){
							continue;
						}
						if(grid[c][d]==1){
							grid[c][d]=0;
							ms.push({c,d});
							s++;
						}
					}
				}
				res=max(s,res);
			}
		}
		return res;
    }
};
//BFS非递归
class Solution {
public:
	vector<pair<int,int>> dir={{0,1},{0,-1},{1,0},{-1,0}};
    int maxAreaOfIsland(vector<vector<int>>& grid) {
		queue<pair<int,int>> mq;
		int res=0;
		int m=grid.size(),n=grid[0].size();
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				if(grid[i][j]==0){
					continue;
				}
				grid[i][j]=0;
				int s=1;
				mq.push({i,j});
				while(!mq.empty()){
					int x=mq.front().first;
					int y=mq.front().second;
					mq.pop();
					for(auto [a,b]:dir){
						int c=a+x;
						int d=b+y;
						if(c<0||c>=m||d<0||d>=n){
							continue;
						}
						if(grid[c][d]==1){
							grid[c][d]=0;
							mq.push({c,d});
							s++;
						}
					}
				}
				res=max(s,res);
			}
		}
		return res;
    }
};
/* 
给你一个 n x n 的二进制矩阵 grid 中，返回矩阵中最短 畅通路径 的长度。如果不存在这样的路径，返回 -1 。

二进制矩阵中的 畅通路径 是一条从 左上角 单元格（即，(0, 0)）到 右下角 单元格（即，(n - 1, n - 1)）的路径，该路径同时满足下述要求：

    路径途经的所有单元格都的值都是 0 。
    路径中所有相邻的单元格应当在 8 个方向之一 上连通（即，相邻两单元之间彼此不同且共享一条边或者一个角）。
畅通路径的长度 是该路径途经的单元格总数。
    n == grid.length
    n == grid[i].length
    1 <= n <= 100
    grid[i][j] 为 0 或 1
1091
 */
class Solution {
public:
	vector<pair<int,int>> dir={{0,1},{0,-1},{1,0},{-1,0},{-1,-1},{-1,1},{1,-1},{1,1}};
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
		queue<pair<int,int>> mq;
		int res=0,n=grid.size();
		if(grid[0][0]!=0){
			return -1;
		}
		mq.push({0,0});
		grid[0][0]=1;
		while(!mq.empty()){
			res++;
			int m=mq.size();
			while(--m>=0){
				int x=mq.front().first;
				int y=mq.front().second;
				mq.pop();
				if(x==n-1&&y==n-1){
					return res;
				}
				for(auto [a,b]:dir){
					int c=x+a,d=y+b;
					if(c<0||d<0||c>=n||d>=n||grid[c][d]==1){
						continue;
					}
					mq.push({c,d});
					grid[c][d]=1;
				}
			}
		}
		return -1;
    }
};
/* 
给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。

岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。

此外，你可以假设该网格的四条边均被水包围。
 */
//BFS
class Solution {
public:
	vector<pair<int,int>> dir={{0,1},{0,-1},{1,0},{-1,0}};
    int numIslands(vector<vector<char>>& grid) {
		queue<pair<int,int>> mq;
		int res=0;
		int m=grid.size(),n=grid[0].size();
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				if(grid[i][j]=='0'){
					continue;
				}
				grid[i][j]='0';
				res++;
				mq.push({i,j});
				while(!mq.empty()){
					int x=mq.front().first;
					int y=mq.front().second;
					mq.pop();
					for(auto [a,b]:dir){
						int c=a+x;
						int d=b+y;
						if(c<0||c>=m||d<0||d>=n){
							continue;
						}
						if(grid[c][d]=='1'){
							grid[c][d]='0';
							mq.push({c,d});
						}
					}
				}
			}
		}
		return res;
    }
};
/* 
给定一个 m x n 的非负整数矩阵来表示一片大陆上各个单元格的高度。“太平洋”处于大陆的左边界和上边界，而“大西洋”处于大陆的右边界和下边界。

规定水流只能按照上、下、左、右四个方向流动，且只能从高到低或者在同等高度上流动。

请找出那些水流既可以流动到“太平洋”，又能流动到“大西洋”的陆地单元的坐标。
417
 */
class Solution {
public:
	vector<pair<int,int>> dir={{0,1},{0,-1},{1,0},{-1,0}};
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
		vector<vector<int>> res;
		set<pair<int,int>> s1,s2,b1,b2;
		int m=heights.size(),n=heights[0].size();
		for(int i=0;i<m;i++){
			b1.insert({i,0});
			b2.insert({i,n-1});
		}
		for(int j=0;j<n;j++){
			b1.insert({0,j});
			b2.insert({m-1,j});
		}
		for(auto [i,j]:b1){
			queue<pair<int,int>> mq;
			vector<vector<bool>> visit(m,vector<bool>(n,false));
			mq.push({i,j});
			visit[i][0]=true;
			while(!mq.empty()){
				int x=mq.front().first;
				int y=mq.front().second;
				s1.insert({x,y});
				mq.pop();
				for(auto [a,b]:dir){
					int c=x+a;
					int d=y+b;
					if(c<0||d<0||c>=m||d>=n){
						continue;
					}
					if(heights[c][d]>=heights[x][y]&&visit[c][d]==false){
						visit[c][d]=true;
						mq.push({c,d});
					}
				}
			}
		}
		for(auto [i,j]:b2){
			queue<pair<int,int>> mq;
			vector<vector<bool>> visit(m,vector<bool>(n,false));
			mq.push({i,j});
			visit[i][0]=true;
			while(!mq.empty()){
				int x=mq.front().first;
				int y=mq.front().second;
				s2.insert({x,y});
				mq.pop();
				for(auto [a,b]:dir){
					int c=x+a;
					int d=y+b;
					if(c<0||d<0||c>=m||d>=n){
						continue;
					}
					if(heights[c][d]>=heights[x][y]&&visit[c][d]==false){
						visit[c][d]=true;
						mq.push({c,d});
					}
				}
			}
		}
		for(auto i:s1){
			if(s2.count(i)){
				res.push_back({i.first,i.second});
			}
		}
		return res;
    }
};
/* 
给你一个 m x n 的矩阵 board ，由若干字符 'X' 和 'O' ，找到所有被 'X' 围绕的区域，并将这些区域里所有的 'O' 用 'X' 填充。 
130
 */
class Solution {
public:
	vector<pair<int,int>> dir={{0,1},{0,-1},{1,0},{-1,0}};
    void solve(vector<vector<char>>& board) {
		int m=board.size(),n=board[0].size();
		vector<pair<int,int>> vec;
		for(int i=0;i<m;i++){
			vec.push_back({i,0});
			vec.push_back({i,n-1});
		}
		for(int j=0;j<n;j++){
			vec.push_back({0,j});
			vec.push_back({m-1,j});
		}
		for(auto [i,j]:vec){
            if(board[i][j]!='O'){
                continue;
            }
			queue<pair<int,int>> mq;
			mq.push({i,j});
			board[i][j]='A';
			while(!mq.empty()){
				int x=mq.front().first;
				int y=mq.front().second;
				mq.pop();
				for(auto [a,b]:dir){
					int c=x+a;
					int d=y+b;
					if(c<0||d<0||c>=m||d>=n){
						continue;
					}
					if(board[c][d]=='O'){
						mq.push({c,d});
                        board[c][d]='A';
					}
				}
			}
		}
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				if(board[i][j]=='O'){
					board[i][j]='X';
				}
			}
		}
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				if(board[i][j]=='A'){
					board[i][j]='O';
				}
			}
		}
    }
};