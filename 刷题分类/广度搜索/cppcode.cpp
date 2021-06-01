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
/* 
在给定的二维二进制数组 A 中，存在两座岛。（岛是由四面相连的 1 形成的一个最大组。）

现在，我们可以将 0 变为 1，以使两座岛连接起来，变成一座岛。

返回必须翻转的 0 的最小数目。（可以保证答案至少是 1 。）
934
 */
class Solution {
public:
    int temp=INT_MAX;
	vector<vector<int>> dir={{0,1},{0,-1},{1,0},{-1,0}};
    int shortestBridge(vector<vector<int>>& grid) {
		int m=grid.size(),n=grid[0].size();
        bool first=true;
		int n1=0,n2=0;
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				if(grid[i][j]==1){
					if(first){
						dfs(grid,i,j,2,n1);
						first=false;
					}else{
						dfs(grid,i,j,3,n2);
					}
					
				}
			}
		}
		int k=n1>n2?3:2;
		int res=bfs(grid,k);
		return res;
    }
	int bfs(vector<vector<int>>& A, int round){
        // from round to find target
		int n=A.size(),m=A[0].size();
        int target = 0;
        if(round == 3) target = 2;
        else if(round == 2) target = 3;
        queue<pair<int,int>> q;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                if(A[i][j]==round)
                    q.push({i,j});
        int ans = 0;
        while(!q.empty()){
            ans ++;
            int size = q.size();
            for(int i = 0; i < size; i++){
                auto cur = q.front(); q.pop();
                int x = cur.first;
                int y = cur.second;
                for(int i = 0; i < 4; i++){
                    int a = x + dir[i][0];
                    int b = y + dir[i][1];
                    if(a >= 0 && a < n && b >=0 && b < m){
                        if(A[a][b]==0) {
                           q.push({a,b});
                           A[a][b] = 4; 
                        }
                        else if(A[a][b] == target) return ans;
                    }
                }
            }
        }
        return -1;
    }
	void dfs(vector<vector<int>>& grid,int i,int j,int n,int& k){
		if(i<0||i>=grid.size()||j<0||j>=grid[0].size()||grid[i][j]!=1){
			return;
		}
		grid[i][j]=n;
		k++;
		for(auto d:dir){
			dfs(grid,i+d[0],j+d[1],n,k);
		}
	}
};
/* 
让我们一起来玩扫雷游戏！

给定一个代表游戏板的二维字符矩阵。 
'M' 代表一个未挖出的地雷，
'E' 代表一个未挖出的空方块，
'B' 代表没有相邻（上，下，左，右，和所有4个对角线）地雷的已挖出的空白方块，
数字（'1' 到 '8'）表示有多少地雷与这块已挖出的方块相邻，
'X' 则表示一个已挖出的地雷。

现在给出在所有未挖出的方块中（'M'或者'E'）的下一个点击位置（行和列索引），根据以下规则，返回相应位置被点击后对应的面板：

    如果一个地雷（'M'）被挖出，游戏就结束了- 把它改为 'X'。
    如果一个没有相邻地雷的空方块（'E'）被挖出，修改它为（'B'），并且所有和其相邻的未挖出方块都应该被递归地揭露。
    如果一个至少与一个地雷相邻的空方块（'E'）被挖出，修改它为数字（'1'到'8'），表示相邻地雷的数量。
    如果在此次点击中，若无更多方块可被揭露，则返回面板。
529
 */
class Solution {
public:
	int m,n;
	vector<vector<int>> dir={{1,1},{1,0},{1,-1},{-1,-1},{-1,0},{-1,1},{0,1},{0,-1}};
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
		int x=click[0],y=click[1];
		m=board.size(),n=board[0].size();
		if(board[x][y]=='M'){
			board[x][y]='X';
			return board;
		}
		if(board[x][y]=='E'){
			vector<vector<int>> visit(m,vector<int>(n,0));
			queue<pair<int,int>> mq;
			mq.push({x,y});
			visit[x][y]=1;
            while(!mq.empty()){
				int len=mq.size();
				for(int k=0;k<len;k++){
					int i=mq.front().first;
					int j=mq.front().second;
					mq.pop();
					if(process(board,i,j)){
						continue;
					}
					for(auto d:dir){
						int a=i+d[0];
						int b=j+d[1];
						if(a<0||a>=m||b<0||b>=n||visit[a][b]==1){
							continue;
						}
						if(board[a][b]=='E'){
							mq.push({a,b});
						}
						visit[a][b]=1;
					}
				}
            }
			
		}
		return board;
    }
	int process(vector<vector<char>>& board,int i,int j){
		int m_n=0;
		for(auto d:dir){
			int a=i+d[0];
			int b=j+d[1];
			if(a<0||a>=m||b<0||b>=n){
				continue;
			}
			if(board[a][b]=='M'){
				m_n++;
			}
		}
		if(m_n==0){
			board[i][j]='B';
		}else{
			board[i][j]='0'+m_n;
		}
		return m_n;
	}
};
/* 
给出一个二维数组 A，每个单元格为 0（代表海）或 1（代表陆地）。

移动是指在陆地上从一个地方走到另一个地方（朝四个方向之一）或离开网格的边界。

返回网格中无法在任意次数的移动中离开网格边界的陆地单元格的数量。
1020
 */
//方法1
class Solution {
public:
	vector<pair<int,int>> dir={{0,1},{0,-1},{1,0},{-1,0}};
    int numEnclaves(vector<vector<int>>& grid) {
		int res=0;
		int m=grid.size(),n=grid[0].size();
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				if(grid[i][j]==0){
					continue;
				}
				bool k=false;
				int s=1;
				queue<pair<int,int>> mq;
				grid[i][j]=0;
				mq.push({i,j});
				while(!mq.empty()){
					int x=mq.front().first;
					int y=mq.front().second;
					mq.pop();
                    //cout<<x<<" "<<y<<endl;
					if(x==0||x==m-1||y==0||y==n-1){
						k=true;
					}
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
                if(k){
                    s=0;
                }
				res+=s;
			}
		}
		return res;
    }
};

//方法2
class Solution {
public:
	vector<pair<int,int>> dir={{0,1},{0,-1},{1,0},{-1,0}};	
    int numEnclaves(vector<vector<int>>& grid) {
		vector<pair<int,int>> boundary; 
		queue<pair<int,int>> mq;
		int m=grid.size(),n=grid[0].size();
		for(int i=0;i<m;i++){
			boundary.push_back({i,0});
			boundary.push_back({i,n-1});
		}
		for(int j=0;j<n;j++){
			boundary.push_back({0,j});
			boundary.push_back({m-1,j});
		}
		for(auto [i,j]:boundary){
			if(grid[i][j]==0){
				continue;
			}
			grid[i][j]=0;
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
					}
				}
			}
		}
		int res=0;
		for(auto vec:grid){
			for(auto i:vec){
				if(i==1){
					res++;
				}
			}
		}
		return res;
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
	vector<pair<int,int>> dir={{0,1},{0,-1},{1,0},{-1,0}};	
    int closedIsland(vector<vector<int>>& grid) {
		int res=0;
		int m=grid.size(),n=grid[0].size();
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				if(grid[i][j]==1){
					continue;
				}
				bool k=false;
				queue<pair<int,int>> mq;
				grid[i][j]=1;
				mq.push({i,j});
				while(!mq.empty()){
					int x=mq.front().first;
					int y=mq.front().second;
					mq.pop();
                    //cout<<x<<" "<<y<<endl;
					if(x==0||x==m-1||y==0||y==n-1){
						k=true;
					}
					for(auto [a,b]:dir){
						int c=a+x;
						int d=b+y;
						if(c<0||c>=m||d<0||d>=n){
							continue;
						}
						if(grid[c][d]==0){
							grid[c][d]=1;
							mq.push({c,d});
						}
					}
				}
                if(!k){
                    res++;
                }
			}
		}
		return res;
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
	vector<vector<int>> dir={{1,0},{-1,0},{0,1},{0,-1}};
    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int r0, int c0, int color) {
		queue<pair<int,int>> mq;
		int m=grid.size(),n=grid[0].size();
		int k=grid[r0][c0];
		mq.push({r0,c0});
		grid[r0][c0]=0;
		while(!mq.empty()){
			int i=mq.front().first;
			int j=mq.front().second;
			mq.pop();
			int index=0;
			for(auto d:dir){
				int x=i+d[0];
				int y=j+d[1];
				if(x<0||x>=m||y<0||y>=n){
					continue;
				}
				if(grid[x][y]==0||grid[x][y]==-1){
					index++;
				}
				if(grid[x][y]==k){
					grid[x][y]=0;
					mq.push({x,y});
					index++;
				}
			}
			if(index==4){
				grid[i][j]=-1;
			}
		}
		for(auto &vec:grid){
            for(int &i:vec){
                //cout<<i<<" ";
                if(i==-1){
                    i=k;
                }
				if(i==0){
					i=color;
				}
            }
            //cout<<endl;
        }
		return grid;
    }
};
/* 
有一幅以二维整数数组表示的图画，每一个整数表示该图画的像素值大小，数值在 0 到 65535 之间。

给你一个坐标 (sr, sc) 表示图像渲染开始的像素值（行 ，列）和一个新的颜色值 newColor，让你重新上色这幅图像。

为了完成上色工作，从初始坐标开始，记录初始坐标的上下左右四个方向上像素值与初始坐标相同的相连像素点，接着再记录这四个方向上符合条件的像素点与他们对应四个方向上像素值与初始坐标相同的相连像素点，……，重复该过程。将所有有记录的像素点的颜色值改为新的颜色值。

最后返回经过上色渲染后的图像。
 */
class Solution {
public:
	vector<vector<int>> dir={{1,0},{-1,0},{0,1},{0,-1}};
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
		queue<pair<int,int>> mq;
		int m=image.size(),n=image[0].size();
		vector<vector<int>> visit(m,vector<int>(n,0));
		int k=image[sr][sc];
		mq.push({sr,sc});
		visit[sr][sc]=1;
		image[sr][sc]=newColor;
		while(!mq.empty()){
			int i=mq.front().first;
			int j=mq.front().second;
			mq.pop();
			for(auto d:dir){
				int x=i+d[0];
				int y=j+d[1];
				if(x<0||x>=m||y<0||y>=n||visit[x][y]==1){
					continue;
				}
				image[x][y]=newColor;
				visit[x][y]=1;
				mq.push({x,y});
			}
		}
		return image;
    }
};
/* 
剑指 Offer 13. 机器人的运动范围
地上有一个m行n列的方格，从坐标 [0,0] 到坐标 [m-1,n-1] 。
一个机器人从坐标 [0, 0] 的格子开始移动，它每次可以向左、右、上、下移动一格（不能移动到方格外），
也不能进入行坐标和列坐标的数位之和大于k的格子。
例如，当k为18时，机器人能够进入方格 [35, 37] ，因为3+5+3+7=18。但它不能进入方格 [35, 38]，因为3+5+3+8=19。
请问该机器人能够到达多少个格子？
 */
class Solution {
public:
	vector<vector<int>> dir={{0,1},{0,-1},{1,0},{-1,0}};
    int movingCount(int m, int n, int k) {
		queue<pair<int,int>> mq;
		vector<vector<int>> visit(m,vector<int>(n,0));
		int res=1;
		mq.push({0,0});
		visit[0][0]=1;
		while(!mq.empty()){
			int i=mq.front().first;
			int j=mq.front().second;
			mq.pop();
			for(auto d:dir){
				int x=i+d[0],y=j+d[1];
				if(x<0||x>=m||y<0||y>=n||visit[x][y]==1){
					continue;
				}
				if(getSum(x)+getSum(y)>k){
					continue;
				}
				visit[x][y]=1;
				mq.push({x,y});
				res++;
			}
		}
		return res;
    }
	int getSum(int n){
		int res=0;
		while(n){
			res+=n%10;
			n/=10;
		}
		return res;
	}
};
/* 
N x N 的棋盘 board 上，按从 1 到 N*N 的数字给方格编号，编号 从左下角开始，每一行交替方向。

r 行 c 列的棋盘，按前述方法编号，棋盘格中可能存在 “蛇” 或 “梯子”；如果 board[r][c] != -1，那个蛇或梯子的目的地将会是 board[r][c]。

玩家从棋盘上的方格 1 （总是在最后一行、第一列）开始出发。

每一回合，玩家需要从当前方格 x 开始出发，按下述要求前进：

    选定目标方格：选择从编号 x+1，x+2，x+3，x+4，x+5，或者 x+6 的方格中选出一个目标方格 s ，目标方格的编号 <= N*N。
        该选择模拟了掷骰子的情景，无论棋盘大小如何，你的目的地范围也只能处于区间 [x+1, x+6] 之间。
    传送玩家：如果目标方格 S 处存在蛇或梯子，那么玩家会传送到蛇或梯子的目的地。否则，玩家传送到目标方格 S。 

注意，玩家在每回合的前进过程中最多只能爬过蛇或梯子一次：就算目的地是另一条蛇或梯子的起点，你也不会继续移动。

返回达到方格 N*N 所需的最少移动次数，如果不可能，则返回 -1。
909
 */
class Solution {
public:
	int m,n;
	vector<vector<int>> num;
	map<int,pair<int,int>> map;
    int snakesAndLadders(vector<vector<int>>& board) {
		m=board.size(),n=board[0].size();
		num=board;
		getnumber();
		queue<int> mq;
		vector<int> visit(m*n+1,0);
		int res=0;
		mq.push(1);
		visit[1]=1;
		while(!mq.empty()){
			int len=mq.size();
			for(int j=0;j<len;j++){
				int k=mq.front();
				if(k==m*n){
					return res;
				}
				mq.pop();
				for(int i=1;i<=6;i++){
					if(k+i>m*n||visit[k+i]==1){
						continue;
					}
                    visit[k+i]=1;
					int x=map[k+i].first;
					int y=map[k+i].second;
					if(board[x][y]!=-1){
						mq.push(board[x][y]);
					}else{
						mq.push(k+i);
					}
				}
			}
			res++;
		}
		return -1;
    }
	void getnumber(){
		bool k=true;
		int index=1;
		for(int i=m-1;i>=0;i--){
			if(k){
				for(int j=0;j<n;j++){
					num[i][j]=index++;
				}
			}else{
				for(int j=n-1;j>=0;j--){
					num[i][j]=index++;
				}
			}
			k=!k;
		}
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				map[num[i][j]]={i,j};
			}
		}
	}
};