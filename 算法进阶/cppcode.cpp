#include "head.h"
//DAY1
/* 
现有一个按 升序 排列的整数数组 nums ，其中每个数字都 互不相同 。

给你一个整数 k ，请你找出并返回从数组最左边开始的第 k 个缺失数字。
1060
 */
class Solution {
public:
    int missingElement(vector<int>& nums, int k) {
		int i=nums[0],index=0;
		while(k){
			if(index<nums.size()&&nums[index]==i){
				index++;
			}else{
				k--;
			}
            if(k){
                i++;
            }
		}
		return i;
    }
};
class Solution {
public:
    int missingElement(vector<int>& nums, int k) {
		int i=1;
		for(;i<nums.size();i++){
			if(nums[i]-nums[i-1]-1>=k){
				break;
			}else{
				k-=nums[i]-nums[i-1]-1;
			}
		}
		return nums[i-1]+k;
    }
};
class Solution {
public:
    int missingElement(vector<int>& nums, int k) {
		int n=nums.size();
		int left=0,right=n-1;
		while(left<right){
			//排除右半部分，使用向上取整
			int mid=left+(right-left+1)/2;
            //cout<<left<<" "<<mid<<" "<<right<<endl;
			if(nums[mid]-nums[0]-mid<k){
				left=mid;
			}else{
				right=mid-1;
			}
		}
		return k+left+nums[0];
    }
};
/* 
一个 2D 网格中的 顶峰元素 是指那些 严格大于 其相邻格子(上、下、左、右)的元素。

给你一个 从 0 开始编号 的 m x n 矩阵 mat ，其中任意两个相邻格子的值都 不相同 。
找出 任意一个 顶峰元素 mat[i][j] 并 返回其位置 [i,j] 。

你可以假设整个矩阵周边环绕着一圈值为 -1 的格子。

要求必须写出时间复杂度为 O(m log(n)) 或 O(n log(m)) 的算法
1901
 */
//不合法
class Solution {
public:
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        int m=mat.size(),n=mat[0].size();
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				if(check(mat,i,j,m,n)){
					return {i,j};
				}
			}
		}
		return {};
    }
	bool check(vector<vector<int>>& mat,int i,int j,int m,int n){
		if(i-1>=0&&mat[i][j]<mat[i-1][j]){
			return false;
		}
		if(i+1<m&&mat[i][j]<mat[i+1][j]){
			return false;
		}
		if(j-1>=0&&mat[i][j]<mat[i][j-1]){
			return false;
		}
		if(j+1<n&&mat[i][j]<mat[i][j+1]){
			return false;
		}
		return true;
	}
};
/* 
[45,35,27,15,29]
[38,18,1,49,11]
[45,28,22,18,10]
[14,49,7,6,25]
[7,23,39,17,3]
 */
class Solution {
public:
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
		int m=mat.size();
		int left=0,right=m-1;
		while(left<=right){
			int mid=left+(right-left)/2;
            //cout<<left<<" "<<mid<<" "<<right<<endl;
			if(mid>0&&mid<m-1){
				int m1=*max_element(mat[mid-1].begin(),mat[mid-1].end());
				int m2=*max_element(mat[mid].begin(),mat[mid].end());
				int m3=*max_element(mat[mid+1].begin(),mat[mid+1].end());
                //cout<<m1<<" "<<m2<<" "<<m3<<endl;
				if(m1<=m2&&m3<=m2){
					for(int i=0;i<mat[mid].size();i++){
						if(m2==mat[mid][i]){
							return {mid,i};
						}
					}
				}else if(m1<=m2){
					left=mid+1;
				}else{
					right=mid-1;
				}
			}else if(mid==0){
				int m2=*max_element(mat[mid].begin(),mat[mid].end());
				int m3=*max_element(mat[mid+1].begin(),mat[mid+1].end());
				if(m3<=m2){
					for(int i=0;i<mat[mid].size();i++){
						if(m2==mat[mid][i]){
							return {mid,i};
						}
					}
				}else{
					left=mid+1;
				}
			}else{
				int m1=*max_element(mat[mid-1].begin(),mat[mid-1].end());
				int m2=*max_element(mat[mid].begin(),mat[mid].end());
				if(m1<=m2){
					for(int i=0;i<mat[mid].size();i++){
						if(m2==mat[mid][i]){
							return {mid,i};
						}
					}
				}else{
					right=mid-1;
				}
			}
		}
		return {};
    }
};
//DAY2
/* 
你有一大块巧克力，它由一些甜度不完全相同的小块组成。我们用数组 sweetness 来表示每一小块的甜度。

你打算和 K 名朋友一起分享这块巧克力，所以你需要将切割 K 次才能得到 K+1 块，每一块都由一些 连续 的小块组成。

为了表现出你的慷慨，你将会吃掉 总甜度最小 的一块，并将其余几块分给你的朋友们。

请找出一个最佳的切割策略，使得你所分得的巧克力 总甜度最大，并返回这个 最大总甜度。
1231
 */
class Solution {
public:
    int maximizeSweetness(vector<int>& sweetness, int k) {
		int left=0,right=accumulate(sweetness.begin(),sweetness.end(),0);
		auto check=[&](int mid){
			int m=0,n=0;
			for(auto i:sweetness){
				m+=i;
				if(m>=mid){
					n++;
					m=0;
				}
			}
			//k+1块
			return n>k;
		};
		while(left<right){
			int mid=left+(right-left+1)/2;
			if(check(mid)){
				left=mid;
			}else{
				right=mid-1;
			}
		}
		return left;
    }
};
/* 
给你一个数组 colors，里面有  1、2、 3 三种颜色。

我们需要在 colors 上进行一些查询操作 queries，其中每个待查项都由两个整数 i 和 c 组成。

现在请你帮忙设计一个算法，查找从索引 i 到具有目标颜色 c 的元素之间的最短距离。

如果不存在解决方案，请返回 -1。
1182
 */
class Solution {
public:
    vector<int> shortestDistanceColor(vector<int>& colors, vector<vector<int>>& queries) {
		vector<vector<int>> vec(4);
		for(int i=0;i<colors.size();i++){
			vec[colors[i]].emplace_back(i);
		}
		vector<int> res;
		for(auto v:queries){
			int m=v[1];
			if(vec[m].empty()){
				res.emplace_back(-1);
				continue;
			}
			auto i=lower_bound(vec[m].begin(),vec[m].end(),v[0])-vec[m].begin();
			if(i==0){
				res.emplace_back(vec[m][0]-v[0]);
			}else if(i==vec[m].size()){
				res.emplace_back(v[0]-vec[m][i-1]);
			}else{
				res.emplace_back(min(vec[m][i]-v[0],v[0]-vec[m][i-1]));
			}
		}
		return res;
    }
};
//DAY3
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
//DAY4
/* 
给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
42
 */
class Solution {
public:
    int trap(vector<int>& height) {

    }
};