#include "head.h"
/* 
给你两个 非负 整数 num1 和 num2 。

每一步 操作 中，如果 num1 >= num2 ，你必须用 num1 减 num2 ；否则，你必须用 num2 减 num1 。

    例如，num1 = 5 且 num2 = 4 ，应该用 num1 减 num2 ，因此，得到 num1 = 1 和 num2 = 4 。
	然而，如果 num1 = 4且 num2 = 5 ，一步操作后，得到 num1 = 4 和 num2 = 1 。

返回使 num1 = 0 或 num2 = 0 的 操作数 。
 */
class Solution {
public:
    int countOperations(int num1, int num2) {
		int res=0;
		while(num1&&num2){
			res++;
			if(num1>=num2){
				num1-=num2;
			}else{
				num2-=num1;
			}
		}
		return res;
    }
};
/* 
给你一个下标从 0 开始的数组 nums ，该数组由 n 个正整数组成。

如果满足下述条件，则数组 nums 是一个 交替数组 ：

    nums[i - 2] == nums[i] ，其中 2 <= i <= n - 1 。
    nums[i - 1] != nums[i] ，其中 1 <= i <= n - 1 。

在一步 操作 中，你可以选择下标 i 并将 nums[i] 更改 为 任一 正整数。

返回使数组变成交替数组的 最少操作数 。
 */
class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int n=nums.size();
		map<int,int> m1,m2;
		for(int i=0;i<n;i++){
			if(i%2==0){
				m1[nums[i]]++;
			}else{
				m2[nums[i]]++;
			}
		}
		auto cmp=[](auto t1,auto t2){
			return t1.second>t2.second;
		};
		sort(m1.begin(),m1.end(),cmp);	
		sort(m2.begin(),m2.end(),cmp);
		if(m1.begin()->first!=m2.begin()->first){
			return n-m1.begin()->second+m2.begin()->second;
		}
		return n-max((m1.begin()++)->second+m2.begin()->second,n-m1.begin()->second+(m2.begin()++)->second);
    }
};