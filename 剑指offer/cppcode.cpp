#include "head.h"
/* 
找出数组中重复的数字。
在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1 的范围内。
数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。
使用额外空间比较简单，这里不使用额外空间，将这个数字下标的那个数置为复数！
 */
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
		for(int i=0;i<nums.size();i++){
			int n=abs(nums[i]);
			if(nums[n]<0){
				return n;
			}
			nums[n]*=-1;
		}
		return 0;
    }
};
/* 
在一个 n * m 的二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。
请完成一个高效的函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
从左上或是右下开始找！
 */
class Solution {
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        if(matrix.size()==0){
            return false;
        }
		int m=matrix.size(),n=matrix[0].size();
		int i=m-1,j=0;
		while(i>=0&&j<n){
			if(matrix[i][j]==target){
				return true;
			}
			if(matrix[i][j]<target){
				j++;
			}else{
				i--;
			}
		}
		return false;
    }
};
/* 
请实现一个函数，把字符串 s 中的每个空格替换成"%20"。
 */
class Solution {
public:
    string replaceSpace(string s) {
		string res;
		for(auto c:s){
			if(c==' '){
				res+="%20";
			}else{
				res+=c;
			}
		}
		return res;
    }
};
/* 
输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）。
 */
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
		vector<int> res;
		while(head){
			res.emplace_back(head->val);
			head=head->next;
		}
		reverse(res.begin(),res.end());
		return res;
    }
};
/* 
输入某二叉树的前序遍历和中序遍历的结果，请重建该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。
 */
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		for(int i=0;i<inorder.size();i++){
			ump[inorder[i]]=i;
		}
		return dfs(preorder,inorder,0,preorder.size()-1,0,inorder.size()-1);
    }
	TreeNode* dfs(vector<int>& preorder, vector<int>& inorder,int pre_h,int pre_t,int in_h,int in_t){
		if(pre_h>pre_t||in_h>in_t){
			return nullptr;
		}
		int l_len=ump[preorder[pre_h]]-in_h;
		TreeNode *root=new TreeNode(preorder[pre_h]);
		root->left=dfs(preorder,inorder,pre_h+1,pre_h+l_len,in_h,in_h+l_len-1);
		root->right=dfs(preorder,inorder,pre_h+1+l_len,pre_t,in_h+l_len+1,in_t);
		return root;
	}
private:
	unordered_map<int,int> ump;
};
/* 
用两个栈实现一个队列。队列的声明如下，请实现它的两个函数 appendTail 和 deleteHead ，
分别完成在队列尾部插入整数和在队列头部删除整数的功能。(若队列中没有元素，deleteHead 操作返回 -1 )
 */
class CQueue {
public:
    CQueue() {
		while(!s1.empty()){
			s1.pop();
		}
		while(!s2.empty()){
			s2.pop();
		}
    }
    
    void appendTail(int value) {
		while(!s2.empty()){
			s1.emplace(s2.top());
			s2.pop();
		}
		s1.emplace(value);
    }
    
    int deleteHead() {
		while(!s1.empty()){
			s2.emplace(s1.top());
			s1.pop();
		}
		if(s2.empty()){
			return -1;
		}
		int res=s2.top();
		s2.pop();
		return res;
    }
private:
	stack<int> s1,s2;
};

/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue* obj = new CQueue();
 * obj->appendTail(value);
 * int param_2 = obj->deleteHead();
 */
/* 
写一个函数，输入 n ，求斐波那契（Fibonacci）数列的第 n 项（即 F(N)）。斐波那契数列的定义如下：

F(0) = 0,   F(1) = 1
F(N) = F(N - 1) + F(N - 2), 其中 N > 1.

斐波那契数列由 0 和 1 开始，之后的斐波那契数就是由之前的两数相加而得出。

答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。
 */
class Solution {
public:
    int fib(int n) {
		long long i1=0,i2=1,res=0;
		for(int i=2;i<=n;i++){
			res=i1+i2;
			i1=i2%1000000007;
			i2=res%1000000007;
		}
		return n==0?0:n==1?1:res%1000000007;
    }
};
/* 
一只青蛙一次可以跳上1级台阶，也可以跳上2级台阶。求该青蛙跳上一个 n 级的台阶总共有多少种跳法。

答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。
 */
class Solution {
public:
    int numWays(int n) {
        vector<long long> dp(n+1);
        dp[0]=1;
        for(int i=1;i<=n;i++){
            if(i==1){
                dp[i]=1;
            }else{
                dp[i]=dp[i-1]%1000000007+dp[i-2]%1000000007;
            }
        }
        return dp[n]%1000000007;
    }
};
/* 
把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。
例如，数组 [3,4,5,1,2] 为 [1,2,3,4,5] 的一个旋转，该数组的最小值为1。  
O(n)为简单题 O（logN)为困难题
 */
class Solution {
public:
    int minArray(vector<int>& nums) {
		int left=0,right=nums.size()-1;
		while(left<right){
			while(left<nums.size()-1&&nums[left]==nums[left+1]){
				left++;
			}
			while(right>0&&nums[right]==nums[right-1]){
				right--;
			}
			int mid=left+(right-left)/2;
			if(nums[mid]>nums[right]){
				left=mid+1;
			}else{
				right=mid;
			}
		}
		return nums[left];
    }
};
/* 
给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。
同一个单元格内的字母不允许被重复使用。
 */
class Solution {
public:
	vector<pair<int,int>> dir={{0,1},{1,0},{-1,0},{0,-1}};
    bool exist(vector<vector<char>>& board, string word) {
		for(int i=0;i<board.size();i++){
			for(int j=0;j<board[0].size();j++){
				if(board[i][j]==word[0]){
					if(dfs(board,word,0,i,j)){
						return true;
					}
				}
			}
		}
		return false;
    }
	bool dfs(vector<vector<char>>& board, string word, int k,int i,int j){
		if(k==word.size()){
			return true;
		}
		if(i<0||j<0||i>=board.size()||j>=board[0].size()){
			return false;
		}
		if(board[i][j]!=word[k]){
			return false;
		}
		board[i][j]='#';
		for(auto [a,b]:dir){
			if(dfs(board,word,k+1,i+a,j+b)){
				return true;
			}
		}
		board[i][j]=word[k];
		return false;
	}
};
/* 
地上有一个m行n列的方格，从坐标 [0,0] 到坐标 [m-1,n-1] 。
一个机器人从坐标 [0, 0] 的格子开始移动，它每次可以向左、右、上、下移动一格（不能移动到方格外），
也不能进入行坐标和列坐标的数位之和大于k的格子。
例如，当k为18时，机器人能够进入方格 [35, 37] ，因为3+5+3+7=18。但它不能进入方格 [35, 38]，因为3+5+3+8=19。
请问该机器人能够到达多少个格子？
上次使用bfs，此次使用dfs
 */
class Solution {
public:
    set<pair<int,int>> visit;
	int movingCount(int m, int n, int k) {
		return dfs(m,n,k,0,0);
    }
	int dfs(int m,int n,int k,int i,int j){
		if(i<0||i>=m||j<0||j>=n||visit.count({i,j})||getnum(i)+getnum(j)>k){
			return 0;
		}
		visit.emplace(i,j);
		return 1+dfs(m,n,k,i+1,j)+dfs(m,n,k,i,j+1);//只用往右或者往下走
	}
	int getnum(int n){
		int res=0;
		while(n){
			res+=n%10;
			n/=10;
		}
		return res;
	}
};
/* 
给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），
每段绳子的长度记为 k[0],k[1]...k[m-1] 。
请问 k[0]*k[1]*...*k[m-1] 可能的最大乘积是多少？
例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。
-----------------------
 */
class Solution {
public:
    int cuttingRope(int n) {

    }
};
/* 
编写一个函数，输入是一个无符号整数（以二进制串的形式），返回其二进制表达式中数字位数为 '1' 的个数（也被称为 汉明重量).）。
 */
class Solution {
public:
    int hammingWeight(uint32_t n) {
		int res=0;
		for(int i=0;i<32;i++){
			if((n>>i)&1){
				res++;
			}
		}
		return res;
    }
};
/* 
实现 pow(x, n) ，即计算 x 的 n 次幂函数（即，xn）。不得使用库函数，同时不需要考虑大数问题。
    -100.0 < x < 100.0
    -231 <= n <= 231-1
    -104 <= xn <= 104
 */
/* 
输入数字 n，按顺序打印出从 1 到最大的 n 位十进制数。比如输入 3，则打印出 1、2、3 一直到最大的 3 位数 999。
 */
class Solution {
public:
    vector<int> printNumbers(int n) {

    }
};
/* 
一个整型数组 nums 里除两个数字之外，其他数字都出现了两次。请写程序找出这两个只出现一次的数字。要求时间复杂度是O(n)，空间复杂度是O(1)。
 */
class Solution {
public:
    vector<int> singleNumbers(vector<int>& nums) {
		int n=0;
		for(int i:nums){
			n^=i;
		}
		int i=1;
		for(;i<32;i++){
			if((n>>i)&1){
				break;
			}
		}
		int n1=0,n2=0;
		for(int num:nums){
			if((num>>i)&1){
				n1^=num;
			}else{
				n2^=num;
			}
		}
		return vector<int>{n1,n2};
    }
};
/* 
在一个数组 nums 中除一个数字只出现一次之外，其他数字都出现了三次。请找出那个只出现一次的数字。
 */
class Solution {
public:
    int singleNumber(vector<int>& nums) {
		unordered_map<int,int> ump;
		for(int i:nums){
			ump[i]++;
		}
		for(auto [i,j]:ump){
			if(j==1){
				return i;
			}
		}
		return -1;
    }
};
/*
每位相加对三求余 
 */
/* 
在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组，求出这个数组中的逆序对的总数。
 */
//法一：归并
class Solution {
public:
	vector<int> res;
	map<int,int> mp;
    vector<int> countSmaller(vector<int>& nums) {
		int n=nums.size();
		res.resize(n);
		for(int i=0;i<n;i++){
			mp[i]=i;
		}
		mergesort(nums,0,n-1);
		return res;
    }
	void mergesort(vector<int>& nums,int left,int right){
		if(left>=right){
			return;
		}
		int mid=left+(right-left)/2;
		mergesort(nums,left,mid);
		mergesort(nums,mid+1,right);
		merge(nums,left,right);
	}
	void merge(vector<int>& nums,int left,int right){
		vector<int> help(right-left+1);
		int mid=left+(right-left)/2;
		int p1=left,p2=mid+1,index=0;
		while(p1<=mid&&p2<=right){
			if(nums[p1]<=nums[p2]){
				help[index]=nums[p1];
				res[mp[p1]]+=p2-mid-1;
                mp[p1]=mp[left+index];
				index++,p1++;
			}else{
				help[index]=nums[p2];
				mp[p2]=mp[left+index];
				index++,p2++;
			}
		}
		while(p1<=mid){
			help[index]=nums[p1];
            //res[mp[p1]]+=p2-mid-1;
			mp[p1]=mp[left+index];
			index++,p1++;
		}
		while(p2<=right){
			help[index]=nums[p2];
			mp[p2]=mp[left+index];
			index++,p2++;
		}
		for(int i=0;i<=right-left;i++){
			nums[left+i]=help[i];
		}
	}
};
/* 
剑指 Offer II 060. 出现频率最高的 k 个数字
给定一个整数数组 nums 和一个整数 k ，请返回其中出现频率前 k 高的元素。可以按 任意顺序 返回答案。

示例 1:
输入: nums = [1,1,1,2,2,3], k = 2
输出: [1,2]

示例 2:
输入: nums = [1], k = 1
输出: [1]

提示：

    1 <= nums.length <= 105
    k 的取值范围是 [1, 数组中不相同的元素的个数]
    题目数据保证答案唯一，换句话说，数组中前 k 个高频元素的集合是唯一的
 */
using pii=pair<int,int>;
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
		auto cmp=[](pii a,pii b){
			return a.second>b.second;
		};
        priority_queue<pii,vector<pii>,decltype(cmp)> mpq(cmp);
		map<int,int> mp;
		for(int i:nums){
			mp[i]++;
		}
		for(auto itr:mp){
			mpq.emplace(itr);
			if(mpq.size()>k){
				mpq.pop();
			}
		}
		vector<int> res;
		while(!mpq.empty()){
			res.emplace_back(mpq.top().first);
			mpq.pop();
		}
		return res;
	}
};
/* 
剑指 Offer II 059. 数据流的第 K 大数值

设计一个找到数据流中第 k 大元素的类（class）。注意是排序后的第 k 大元素，不是第 k 个不同的元素。

请实现 KthLargest 类：

    KthLargest(int k, int[] nums) 使用整数 k 和整数流 nums 初始化对象。
    int add(int val) 将 val 插入数据流 nums 后，返回当前数据流中第 k 大的元素。
 */
class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) {
		this->k=k;
		for(int i:nums){
			mpq.emplace(i);
			if(mpq.size()>k){
				mpq.pop();
			}
		}
    }
    
    int add(int val) {
		mpq.emplace(val);
		if(mpq.size()>k){
			mpq.pop();
		}
		return mpq.top();
    }
private:
	priority_queue<int,vector<int>,greater<int>> mpq;
	int k;
};
/* 
剑指 Offer 49. 丑数

我们把只包含质因子 2、3 和 5 的数称作丑数（Ugly Number）。求按从小到大的顺序的第 n 个丑数。
 */
class Solution {
public:
    int nthUglyNumber(int n) {
		priority_queue<long long,vector<long long>,greater<long long>> mpq;
		int temp[3]={2,3,5};
		set<long long> visit;
		mpq.emplace(1);
		visit.emplace(1);
		int index=0;
		while(!mpq.empty()){
			if(++index==n){
				return mpq.top();
			}
			int k=mpq.top();
			mpq.pop();
			for(auto i:temp){
				long long L=(long long)i*k;
				if(!visit.count(L)){
					mpq.emplace(L);
                    visit.emplace(L);
				}
			}
		}	
		return -1;
    }
};