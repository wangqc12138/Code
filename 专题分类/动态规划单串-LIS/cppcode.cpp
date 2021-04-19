/*
给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。
子序列是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。
300
*/
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
    	int n=nums.size();
    	vector<int> dp(n,1);
    	for(int i=0;i<n;i++){
    		for(int j=0;j<i;j++){
    			if(nums[i]>nums[j]){
    				dp[i]=max(dp[i],dp[j]+1);
    			}
    		}
    	}
    	return dp[n-1];
    }
};
/*
给定一个未排序的整数数组，找到最长递增子序列的个数。
673
*/
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
		int n=nums.size(),res=0,maxn=0;
		vector<int> dp(n,1),count(n,1);
		for(int i=0;i<n;i++){
			for(int j=0;j<i;j++){
				if(nums[j]<nums[i]){
					if(dp[i]<dp[j]+1){
						dp[i]=dp[j]+1;
						count[i]=count[j];//这时最长为此时的j的个数
					}else if(dp[j]+1==dp[i]){
						count[i]+=count[j];
					}
				}
			}
			maxn=max(maxn,dp[i]);
		} 
		for(int i=0;i<n;i++){
			if(maxn==dp[i]){
				res+=count[i];
			}
		}
		return res;   	
    }
};
/*
给你一个二维整数数组 envelopes ，其中 envelopes[i] = [wi, hi] ，表示第 i 个信封的宽度和高度。
当另一个信封的宽度和高度都比这个信封大的时候，这个信封就可以放进另一个信封里，如同俄罗斯套娃一样。
请计算 最多能有多少个 信封能组成一组“俄罗斯套娃”信封（即可以把一个信封放到另一个信封里面）。
注意：不允许旋转信封。
354
auto cmp=[&](auto x,auto y){
    return x[1]<y[1];
};
*/
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
    	int n=envelopes.size(),res=0;
    	sort(envelopes.begin(),envelopes.end());
    	vector<int> dp(n,1);
    	for(int i=0;i<n;i++){
    		for(int j=0;j<i;j++){
    			if(envelopes[i][0]>envelopes[j][0]&&envelopes[i][1]>envelopes[j][1]){
    				dp[i]=max(dp[i],dp[j]+1);
    			}
    		}
    		res=max(res,dp[i]);
    	}
    	return res;
    }
};