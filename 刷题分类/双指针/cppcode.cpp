#include "head.h"
/*
你是一名行政助理，手里有两位客户的空闲时间表：slots1 和 slots2，以及会议的预计持续时间 duration，请你为他们安排合适的会议时间。

「会议时间」是两位客户都有空参加，并且持续时间能够满足预计时间 duration 的 最早的时间间隔。

如果没有满足要求的会议时间，就请返回一个 空数组。

「空闲时间」的格式是 [start, end]，由开始时间 start 和结束时间 end 组成，表示从 start 开始，到 end 结束。 

题目保证数据有效：同一个人的空闲时间不会出现交叠的情况，
也就是说，对于同一个人的两个空闲时间 [start1, end1] 和 [start2, end2]，要么 start1 > end2，要么 start2 > end1。
1229
 */
class Solution {
public:
    vector<int> minAvailableDuration(vector<vector<int>>& slots1, vector<vector<int>>& slots2, int duration) {
		sort(slots1.begin(),slots1.end());
		sort(slots2.begin(),slots2.end());
		for(auto i:slots1){
			if(i[1]-i[0]<duration){
				continue;
			}
			for(auto j:slots2){
				if(j[1]-j[0]<duration){
					continue;
				}
				if(j[0]>=i[1]){
					break;
				}
				if(min(j[1],i[1])-max(i[0],j[0])>=duration){
					return {max(i[0],j[0]),max(i[0],j[0])+duration};
				}
			}
		}
		return {};
    }
};
/* 
给定一个包含 n + 1 个整数的数组 nums ，其数字都在 1 到 n 之间（包括 1 和 n），可知至少存在一个重复的整数。

假设 nums 只有 一个重复的整数 ，找出 这个重复的数 。

你设计的解决方案必须不修改数组 nums 且只用常量级 O(1) 的额外空间。
287
 */
//不符合题意
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
		for(int i=0;i<nums.size();i++){
			int j=abs(nums[i]);
			if(nums[j]<0){
				return j;
			}else{
				nums[j]*=-1;
			}
		}
		return -1;
    }
};
//超时
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
		for(int i=0;i<nums.size();i++){
			for(int j=i+1;j<nums.size();j++){
				if(nums[i]==nums[j]){
					return nums[i];
				}
			}
		}
		return -1;
    }
};
//看成数组化的链表，使用快慢指针类似于142题
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
		int slow=0,quick=0;
		do{
			slow=nums[slow];
			quick=nums[nums[quick]];
		}while(slow!=quick);
		slow=0;
		while(slow!=quick){
			slow=nums[slow];
			quick=nums[quick];
		}
		return slow;
    }
};
//二分也可以，在1-n里面查找，根据小于mid数是否合理来排除,
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
		int n=nums.size(),left=0,right=n;
		while(left<right){
			int mid=left+(right-left)/2,cnt=0;
			for(int i:nums){
				cnt+=i<=mid;
			}
			//==是有问题的，因为并不是都是1-n所有数字，有可能缺！！！
			if(cnt==mid){
				left=mid+1;
			}else{
				right=mid;
			}
		}
		return left;
    }
};