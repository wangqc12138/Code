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
		vector<vector<int>> vec(3);
		for(int i=0;i<colors.size();i++){
			vec[colors[i]].emplace_back(i);
		}
		for(auto v:queries){
			int m
		}
    }
};