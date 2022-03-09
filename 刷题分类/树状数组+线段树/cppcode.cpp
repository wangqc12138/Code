#include "head.h"
/* 
线段树是一种非常灵活的数据结构，它可以用于解决多种范围查询问题，
比如在对数时间内从数组中找到最小值、最大值、总和、最大公约数、最小公倍数等。
 */
/* 
给你一个整数数组 nums ，按要求返回一个新数组 counts 。
数组 counts 有该性质： counts[i] 的值是  nums[i] 右侧小于 nums[i] 的元素的数量。
315
 */
//方法一：归并排序改版
class Solution {
public:
	vector<int> res,p;
    vector<int> countSmaller(vector<int>& nums) {
		int n=nums.size();
		res.resize(n);
		for(int i=0;i<n;i++){
			p.emplace_back(i);
		}
		mergesort(nums,0,n-1);
		return res;
    }
	void mergesort(vector<int>& nums,int left,int right){
		if(left>=right){
			return;
		}
		int mid=left+(right-left)/2;
		mergesort(nums,left,mid);
		mergesort(nums,mid+1,right);
		merge(nums,left,right);
	}
	void merge(vector<int>& nums,int left,int right){
		vector<int> help(right-left+1),temp(right-left+1);
		int mid=left+(right-left)/2;
		int p1=left,p2=mid+1,index=0;
		while(p1<=mid&&p2<=right){
			if(nums[p1]<=nums[p2]){
				help[index]=nums[p1];
				temp[index]=p[p1];
				res[p[p1]]+=p2-mid-1;
				index++,p1++;
			}else{
				help[index]=nums[p2];
				temp[index]=p[p2];
				index++,p2++;
			}
		}
		while(p1<=mid){
			help[index]=nums[p1];
			temp[index]=p[p1];
			res[p[p1]]+=p2-mid-1;
			index++,p1++;
		}
		while(p2<=right){
			help[index]=nums[p2];
			temp[index]=p[p2];
			index++,p2++;
		}
		for(int i=0;i<=right-left;i++){
			nums[left+i]=help[i];
			p[left+i]=temp[i];
		}
	}
};
//方法2：树状数组/线段树
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {

    }
};
/* 
给你一个数组 nums ，请你完成两类查询。

    其中一类查询要求 更新 数组 nums 下标对应的值
    另一类查询要求返回数组 nums 中索引 left 和索引 right 之间（ 包含 ）的nums元素的 和 ，其中 left <= right

实现 NumArray 类：

    NumArray(int[] nums) 用整数数组 nums 初始化对象
    void update(int index, int val) 将 nums[index] 的值 更新 为 val
    int sumRange(int left, int right) 返回数组 nums 中索引 left 和索引 right 之间（ 包含 ）的nums元素的 和 （即，nums[left] + nums[left + 1], ..., nums[right]）
307
 */
//方法一：线段树
class NumArray {
public:
    NumArray(vector<int>& nums) {
		int n=nums.size();
		tree.resize(1000000);
		arr=nums;
		buildtree(nums,0,0,n-1);
    }
	void buildtree(vector<int>& nums,int root,int start,int end){
		if(start==end){
			tree[root]=arr[start];
			return;
		}
		int left_node=2*root+1,right_node=2*root+2,mid=(start+end)/2;
		buildtree(nums,left_node,start,mid);
		buildtree(nums,right_node,mid+1,end);
		tree[root]=tree[left_node]+tree[right_node];
	}
	void update(int root,int start,int end,int index,int val){
		if(start==end){
			arr[index]=val;
			tree[root]=val;
			return;
		}
		int left_node=2*root+1,right_node=2*root+2,mid=(start+end)/2;
		if(index<=mid){
			update(left_node,start,mid,index,val);
		}else{
			update(right_node,mid+1,end,index,val);
		}
		tree[root]=tree[left_node]+tree[right_node];
	}
    void update(int index, int val) {
		update(0,0,arr.size()-1,index,val);
    }
    int query(int root,int start,int end,int left,int right){
		if(left>end||right<start){
			return 0;
		}else if(left<=start&&right>=end){
			return tree[root];
		}
		int left_node=root*2+1;
		int right_node=root*2+2;
		int mid=(start+end)/2;
        int l=query(left_node,start,mid,left,right);
        int r=query(right_node,mid+1,end,left,right);
		//printf("start is %d,end is %d, l is %d, r is %d \n",start,right,l,r);
        return l+r;
	}
    int sumRange(int left, int right) {
		return query(0,0,arr.size()-1,left,right);
    }
private:
	vector<int> tree,arr;
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */
//方法2：树状数组
class NumArray {
public:
    NumArray(vector<int>& nums) {
		int n=nums.size();
		tree=vector<int>(n+1,0);
		arr=nums;
		for(int i=0;i<n;i++){
			add(i+1,nums[i]);
		}
    }
    
    void update(int index, int val) {
		add(index+1,val-arr[index]);
        arr[index]=val;
		
    }
    
    int sumRange(int left, int right) {
		return query(right+1)-query(left);
    }
	int lowbit(int x){
		return x&(-x);
	}
	void add(int index,int val){
		for(int i=index;i<tree.size();i+=lowbit(i)){
			tree[i]+=val;
		}
	}
	int query(int index){
		int res=0;
		for(int i=index;i>0;i-=lowbit(i)){
			res+=tree[i];
		}
		return res;
	}
private:
	vector<int> tree,arr;
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */
/* 
给你一个二维矩阵 matrix ，你需要处理下面两种类型的若干次查询：

    更新：更新 matrix 中某个单元的值。
    求和：计算矩阵 matrix 中某一矩形区域元素的 和 ，该区域由 左上角 (row1, col1) 和 右下角 (row2, col2) 界定。

实现 NumMatrix 类：

    NumMatrix(int[][] matrix) 用整数矩阵 matrix 初始化对象。
    void update(int row, int col, int val) 更新 matrix[row][col] 的值到 val 。
    int sumRegion(int row1, int col1, int row2, int col2) 返回矩阵 matrix 中指定矩形区域元素的 和 ，
	该区域由 左上角 (row1, col1) 和 右下角 (row2, col2) 界定。
 308
 */
/* 
转为一维，使用树状数组
 */
class NumMatrix {
public:
    NumMatrix(vector<vector<int>>& matrix) {
		m=matrix.size(),n=matrix[0].size();
		tree=vector<int>(m*n+1,0);
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				arr.emplace_back(matrix[i][j]);
			}
		}
		for(int i=0;i<m*n;i++){
			add(i+1,arr[i]);
		}
    }
	int lowbit(int x){
		return x&(-x);
	}
    void add(int x,int val){
		for(int i=x;i<tree.size();i+=lowbit(i)){
			tree[i]+=val;
		}
	}
    void update(int row, int col, int val) {
		int key=row*n+col;
		add(key+1,val-arr[key]);
		arr[key]=val;
    }
    int query(int x){
		int res=0;
		for(int i=x;i>0;i-=lowbit(i)){
			res+=tree[i];
		}
		return res;
	}
    int sumRegion(int row1, int col1, int row2, int col2) {
		int res=0;
		for(int i=row1;i<=row2;i++){
			//printf("n1 is %d,n2 is %d\n",n*i+col2+1,n*i+col1);
            res+=query(n*i+col2+1)-query(n*i+col1);
            // cout<<query(n*i+col2+1)<<" "<<query(n*i+col1)<<" "<<res<<endl;
		}
		return res;
    }
private:
	vector<int> tree,arr;
	int m,n;
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * obj->update(row,col,val);
 * int param_2 = obj->sumRegion(row1,col1,row2,col2);
 */