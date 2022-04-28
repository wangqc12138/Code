#include "head.h"
/* 
给你一个 从 0 开始的排列 nums（下标也从 0 开始）。请你构建一个 同样长度 的数组 ans ，
其中，对于每个 i（0 <= i < nums.length），都满足 ans[i] = nums[nums[i]] 。返回构建好的数组 ans 。

从 0 开始的排列 nums 是一个由 0 到 nums.length - 1（0 和 nums.length - 1 也包含在内）的不同整数组成的数组
 */
class Solution {
public:
    vector<int> buildArray(vector<int>& nums) {
		vector<int> res;
		for(int i:nums){
			res.emplace_back(nums[i]);
		}
		return res;
    }
};
/* 
你正在玩一款电子游戏，在游戏中你需要保护城市免受怪物侵袭。
给你一个 下标从 0 开始 且长度为 n 的整数数组 dist ，其中 dist[i] 是第 i 个怪物与城市的 初始距离（单位：米）。

怪物以 恒定 的速度走向城市。给你一个长度为 n 的整数数组 speed 表示每个怪物的速度，其中 speed[i] 是第 i 个怪物的速度（单位：米/分）。

怪物从 第 0 分钟 时开始移动。你有一把武器，并可以 选择 在每一分钟的开始时使用，包括第 0 分钟。
但是你无法在一分钟的中间使用武器。这种武器威力惊人，一次可以消灭任一还活着的怪物。

一旦任一怪物到达城市，你就输掉了这场游戏。
如果某个怪物 恰 在某一分钟开始时到达城市，这会被视为 输掉 游戏，在你可以使用武器之前，游戏就会结束。

返回在你输掉游戏前可以消灭的怪物的 最大 数量。如果你可以在所有怪物到达城市前将它们全部消灭，返回  n 
 */
class Solution {
public:
    int eliminateMaximum(vector<int>& dist, vector<int>& speed) {
		int n=dist.size();
		vector<int> need(n);
		for(int i=0;i<n;i++){
			//向上取整
			need[i]=(dist[i]-1)/speed[i]+1;
		}
		sort(need.begin(),need.end());
		int index=0;
		for(int i=0;i<n;i++){
			if(need[i]<=index++){
				return i;
			}
		}
		return n;
	}
};
/* 
我们称一个数字字符串是 好数字 当它满足（下标从 0 开始）偶数 下标处的数字为 偶数 且 奇数 下标处的数字为 质数 （2，3，5 或 7）。

    比方说，"2582" 是好数字，因为偶数下标处的数字（2 和 8）是偶数且奇数下标处的数字（5 和 2）为质数。
	但 "3245" 不是 好数字，因为 3 在偶数下标处但不是偶数。

给你一个整数 n ，请你返回长度为 n 且为好数字的数字字符串 总数 。由于答案可能会很大，请你将它对 109 + 7 取余后返回 。

一个 数字字符串 是每一位都由 0 到 9 组成的字符串，且可能包含前导 0 。
 */
class Solution {
public:
    int countGoodNumbers(long long n) {
		long long res=1;
		for(long long i=0;i<n;i++){
			if(i%2==0){
				res*=5;
			}else{
				res*=4;
			}
			res/=1000000007;
		}
		return res;
    }
};