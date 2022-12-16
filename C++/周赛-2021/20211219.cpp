#include "head.h"
/* 
给你一个下标从 0 开始的字符串 s ，以及一个下标从 0 开始的整数数组 spaces 。

数组 spaces 描述原字符串中需要添加空格的下标。每个空格都应该插入到给定索引处的字符值 之前 。

    例如，s = "EnjoyYourCoffee" 且 spaces = [5, 9] ，那么我们需要在 'Y' 和 'C' 之前添加空格，这两个字符分别位于下标 5 和下标 9 。
	因此，最终得到 "Enjoy Your Coffee" 。

请你添加空格，并返回修改后的字符串。
 */
class Solution {
public:
    string addSpaces(string s, vector<int>& spaces) {
		int index=0;
		string res="";
		for(int i=0;i<s.size();i++){
			if(index<spaces.size()&&i==spaces[index]){
				index++;
				res+=" ";
			}
			res+=s[i];
		}
		return res;
    }
};
/* 
给你一个整数数组 prices ，表示一支股票的历史每日股价，其中 prices[i] 是这支股票第 i 天的价格。

一个 平滑下降的阶段 定义为：对于 连续一天或者多天 ，每日股价都比 前一日股价恰好少 1 ，这个阶段第一天的股价没有限制。

请你返回 平滑下降阶段 的数目。
 */
class Solution {
public:
    long long getDescentPeriods(vector<int>& prices) {
        int n=prices.size(),index=-1;
		long long res=n;
		bool first=true;
		for(int i=1;i<n;i++){
			if(prices[i]==prices[i-1]-1){
				if(first){
					index=i-1;
					first=false;
				}
			}else if(first==false){
				first=true;
				res+=(long long)(i-index)*(i-index-1)/2;
			}
		}
        if(first==false){
            res+=(long long)(n-index)*(n-index-1)/2;
        }
		return res;
    }
};
/* 
给你一个下标从 0 开始包含 n 个正整数的数组 arr ，和一个正整数 k 。

如果对于每个满足 k <= i <= n-1 的下标 i ，都有 arr[i-k] <= arr[i] ，那么我们称 arr 是 K 递增 的。

    比方说，arr = [4, 1, 5, 2, 6, 2] 对于 k = 2 是 K 递增的，因为：
        arr[0] <= arr[2] (4 <= 5)
        arr[1] <= arr[3] (1 <= 2)
        arr[2] <= arr[4] (5 <= 6)
        arr[3] <= arr[5] (2 <= 2)
    但是，相同的数组 arr 对于 k = 1 不是 K 递增的（因为 arr[0] > arr[1]），对于 k = 3 也不是 K 递增的（因为 arr[0] > arr[3] ）。

每一次 操作 中，你可以选择一个下标 i 并将 arr[i] 改成任意 正整数。

请你返回对于给定的 k ，使数组变成 K 递增的 最少操作次数 。
 */
class Solution {
public:
    int kIncreasing(vector<int>& arr, int k) {
        int n=arr.size(),res=0;
		vector<int> visit(n,0);
		for(int i=k;i<n;i++){
			vector<int> dp(n,1);
			int maxlen=1,sumlen=0;
			for(int j=i;i>=0;j-=k,sumlen++){
				if(visit[j]){
					break;
				}
				visit[j]=1;
				for(int l=j;l<=i;l+=k){
					if(dp[l]>=dp[j]){
						dp[j]=max(dp[j],dp[l]+1);
					}
				}
				maxlen=max(dp[j],maxlen);
			}
			res+=sumlen-maxlen;
		}
		return res;
    }
};