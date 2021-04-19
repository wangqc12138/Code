/*
你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。
198
*/
class Solution {
public:
    int rob(vector<int>& nums) {
		vector<int> dp(nums);
		for(int i=1;i<nums.size();i++){
			//当到第二家时，可以选择偷第一家或者第二家
			if(i==1){
				dp[i]=max(dp[i-1],dp[i]);
			}else{
				dp[i]=max(dp[i-1],nums[i]+dp[i-2]);
			}	
		}    	
		return dp[nums.size()-1];
    }
};
/*
你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。这个地方所有的房屋都 围成一圈 ，这意味着第一个房屋和最后一个房屋是紧挨着的。同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警 。
给定一个代表每个房屋存放金额的非负整数数组，计算你 在不触动警报装置的情况下 ，能够偷窃到的最高金额。
213
选择0-n-2、1-n-1
*/
class Solution {
public:
    int rob(vector<int>& nums) {
    	int n=nums.size();
    	vector<int> dp(n),dpb(n,0);
    	for(int i=0;i<n-1;i++){
    		if(i==0){dp[0]=nums[0];}
    		else if(i==1){dp[i]=max(nums[0],nums[1]);}
    		else{dp[i]=max(dp[i-1],dp[i-2]+nums[i]);}
    	}
    	for(int i=1;i<n;i++){
    		if(i==1){dpb[i]=nums[1];}
    		else{dpb[i]=max(dpb[i-1],dpb[i-2]+nums[i]);}
    	}
    	return max(dpb[n-1],dp[n-2]);
    }
};
/*
给定一个整数数组 nums ，你可以对它进行一些操作。
每次操作中，选择任意一个 nums[i] ，删除它并获得 nums[i] 的点数。之后，你必须删除每个等于 nums[i] - 1 或 nums[i] + 1 的元素。
开始你拥有 0 个点数。返回你能通过这些操作获得的最大点数。
740
*/
class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
    	int k=*max_element(nums.begin(),nums.end());
    	vector<int> dp(k+1),temp(k+1,0);
    	for(int i:nums){
    		temp[i]++;
    	}
    	for(int i=1;i<k+1;i++){
    		if(i==1){
    			dp[i]=temp[i]*i;
    		}else{
    			dp[i]=max(temp[i]*i+dp[i-2],dp[i-1]);
    		}
    	}
    	return dp[k];
    }
};
/*
给你一个披萨，它由 3n 块不同大小的部分组成，现在你和你的朋友们需要按照如下规则来分披萨：
    你挑选 任意 一块披萨。
    Alice 将会挑选你所选择的披萨逆时针方向的下一块披萨。
    Bob 将会挑选你所选择的披萨顺时针方向的下一块披萨。
    重复上述过程直到没有披萨剩下。
每一块披萨的大小按顺时针方向由循环数组 slices 表示。
请你返回你可以获得的披萨大小总和的最大值。
1388
*/
class Solution {
public:
	int calculate(vector<int> slices){
		int n=slices.size();
        int k=(n+1)/3;
		vector<vector<int>> dp(n,vector<int>(k+1,0));
		for(int i=0;i<n;i++){
			for(int j=1;j<=k;j++){
				if(i==0){
					dp[i][j]=slices[0];
				}else if(i==1){
					dp[i][j]=max(slices[0],slices[1]);
				}else{
					dp[i][j]=max(dp[i-2][j-1]+slices[i],dp[i-1][j]);
				}
			}
		}
		return dp[n-1][k];
	}
    int maxSizeSlices(vector<int>& slices) {
    	vector<int> s1(slices.begin(),slices.end()-1),s2(slices.begin()+1,slices.end());
    	int res=max(calculate(s1),calculate(s2));
    	return res;
    }
};