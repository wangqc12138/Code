#include "head.h"
/* 
给定一个非负整数数组 nums ，你最初位于数组的 第一个下标 。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

判断你是否能够到达最后一个下标。
55
 */
//BFS
class Solution {
public:
    bool canJump(vector<int>& nums) {
		int n=nums.size();
		queue<int> mq;
		vector<int> visit(n,0);
		mq.emplace(0);
		visit[0]=1;
		while(!mq.empty()){
			int k=mq.front();
			if(k+nums[k]>=n-1){
				return true;
			}
			mq.pop();
			for(int i=k;i<=k+nums[k];i++){
				if(visit[i]==0){
					visit[i]=1;
					mq.emplace(i);
				}
			}
		}
		return false;
	}
};
//贪心-每次到最大
class Solution {
public:
    bool canJump(vector<int>& nums) {
		int n=nums.size(),maxn=0;
		for(int i=0;i<=maxn;i++){
			maxn=max(maxn,i+nums[i]);
			if(maxn>=n-1){
				return true;
			}
		}
		return false;
    }
};