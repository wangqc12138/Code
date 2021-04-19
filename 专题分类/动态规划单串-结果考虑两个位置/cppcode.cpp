/*
如果序列 X_1, X_2, ..., X_n 满足下列条件，就说它是 斐波那契式 的：
    n >= 3
    对于所有 i + 2 <= n，都有 X_i + X_{i+1} = X_{i+2}
给定一个严格递增的正整数数组形成序列，找到 A 中最长的斐波那契式的子序列的长度。如果一个不存在，返回  0 。
（回想一下，子序列是从原序列 A 中派生出来的，它从 A 中删掉任意数量的元素（也可以不删），而不改变其余元素的顺序。例如， [3, 5, 8] 是 [3, 4, 5, 6, 7, 8] 的一个子序列）
873
*/
class Solution {
public:
    int lenLongestFibSubseq(vector<int>& arr) {
    	int n=arr.size(),res=0;
    	vector<vector<int>> dp(n,vector<int>(n,2));
    	unordered_map<int,int> mmap;
    	for(int i=0;i<n;i++){
    		map[arr[i]]=i;
    		for(int j=0;j<i;j++){
    			int k=mmap.count(arr[i]-arr[j])?mmap[arr[i]-arr[j]]:-1;
    			if(arr[i]-arr[j]<arr[j]&&k!=-1){
    				dp[i][j]=dp[j][k]+1;
    			}
    			res=max(dp[i][j],res);
    		}
    	}
    	return res==2?0:res;
    }
};
/*
给定一个整数数组 A，返回 A 中最长等差子序列的长度。
回想一下，A 的子序列是列表 A[i_1], A[i_2], ..., A[i_k] 其中 0 <= i_1 < i_2 < ... < i_k <= A.length - 1。
并且如果 B[i+1] - B[i]( 0 <= i < B.length - 1) 的值都相同，那么序列 B 是等差的。
1027
与上题不同的是，此题可以有重复的值
*/
class Solution {
public:
    int longestArithSeqLength(vector<int>& A) {
    	int n=A.size(),res=0;
    	vector<vector<int>> dp(n,vector<int>(20000,1));
    	for(int i=0;i<n;i++){
    		for(int j=0;j<i;j++){
    			int sub=A[i]-A[j]+10000;
    			dp[i][sub]=dp[j][sub]+1;
    			res=max(res,dp[i][sub]);
    		}
    	}
    	return res;
    }
};