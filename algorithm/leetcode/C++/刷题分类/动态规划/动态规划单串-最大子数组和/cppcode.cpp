/*
给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
53
*/
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
    	int n=nums.size(),res=0;
    	vector<int> dp(nums);
    	for(int i=1;i<n;i++){
    		dp[i]=max(nums[i],nums[i]+dp[i-1]);
    		res=max(res,dp[i]);
    	}
    	return res;
    }
};
/*
给你一个整数数组 nums ，请你找出数组中乘积最大的连续子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。
152
当前位置的最优解未必是由前一个位置的最优解转移得到的。
滚动数组！
Kadane's Algorithm：1191，1186
*/
class Solution {
public:
    int maxProduct(vector<int>& nums) {
    	int n=nums.size(),res=INT_MIN;
    	vector<int> maxn(nums),minn(nums);
    	for(int i=1;i<n;i++){
    		maxn[i]=max(nums[i],max(maxn[i-1]*nums[i],minn[i-1]*nums[i]));
    		minn[i]=min(nums[i],min(maxn[i-1]*nums[i],minn[i-1]*nums[i]));
    	}
    	return *max_element(maxn.begin(),minn.end());
    }
};
/*
给定一个由整数数组 A 表示的环形数组 C，求 C 的非空子数组的最大可能和。
在此处，环形数组意味着数组的末端将会与开头相连呈环状。（形式上，当0 <= i < A.length 时 C[i] = A[i]，且当 i >= 0 时 C[i+A.length] = C[i]）
此外，子数组最多只能包含固定缓冲区 A 中的每个元素一次。（形式上，对于子数组 C[i], C[i+1], ..., C[j]，不存在 i <= k1, k2 <= j 其中 k1 % A.length = k2 % A.length）
918
*/
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& A) {
    	//求一个最大值和，一个最小值和
    	vector<int> maxn(A),minn(A);
        int sum=A[0];
    	for(int i=1;i<A.size();i++){
    		maxn[i]=max(maxn[i-1]+A[i],A[i]);
    		minn[i]=min(minn[i-1]+A[i],A[i]);
    		sum+=A[i];
    	}
    	int maxi=*max_element(maxn.begin(),maxn.end());
    	int mini=*min_element(minn.begin(),minn.end());
    	if(sum==mini){
    		return maxi;
    	}else{
    		return max(maxi,sum-mini);
    	}
    }
};
/*
给定一个正整数、负整数和 0 组成的 N × M 矩阵，编写代码找出元素总和最大的子矩阵。
返回一个数组 [r1, c1, r2, c2]，其中 r1, c1 分别代表子矩阵左上角的行号和列号，r2, c2 分别代表右下角的行号和列号。若有多个满足条件的子矩阵，返回任意一个均可。
注意：本题相对书上原题稍作改动
面试17.24
*/
class Solution {
public:
    vector<int> getMaxMatrix(vector<vector<int>>& matrix) {
    	
    }
};