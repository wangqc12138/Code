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
/* 
树状数组：按桶存放，比如4 1 2 3 2 3 5
1 2 3 4 5
1 2 2 1 1
从后往前遍历，遍历过则入桶，然后找这个桶之前的前缀和就是能产生的逆序对，因为都是在此刻之前入的桶
离散化：只追求相对大小，不然100000000要开的桶太大了
 */
class Solution {
public:
	int tree[200002];
    int N;
	int lowbit(int x){
		return x&(-x);
	}
	void add(int x,int val){
		for(int i=x;i<=N;i+=lowbit(i)){
			tree[i]+=val;
		}
	}
	int query(int x){
		int res=0;
		for(int i=x;i>0;i-=lowbit(i)){
			res+=tree[i];
		}
        return res;
	}
	vector<int> countSmaller(vector<int>& nums) {
        memset(tree,0,sizeof(tree));
		auto temp=nums;
		sort(temp.begin(),temp.end());
		for(int& num:nums){
			num=lower_bound(temp.begin(),temp.end(),num)-temp.begin()+1;
		}
		N=nums.size();
		vector<int> res(N,0);
		for(int i=N-1;i>=0;i--){
			add(nums[i],1);
			res[i]=query(nums[i]-1);
		}
		return res;
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
//-------------------20220421-----------------------------------
//线段树
class STree{
public:
	STree(){

	};
	int update();
	int query();
private:

};
class NumArray {
public:
    NumArray(vector<int>& nums) {

    }
    
    void update(int index, int val) {

    }
    
    int sumRange(int left, int right) {

    }
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
/* 
在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组，求出这个数组中的逆序对的总数。
剑指 Offer 51. 数组中的逆序对
 */
class Solution {
public:
	int tree[200002];
    int N;
	int lowbit(int& x){
		return x&(-x);
	}
	void add(int x,int val){
		for(int i=x;i<=N;i+=lowbit(i)){
			tree[i]+=val;
		}
	}
	int query(int x){
		int res=0;
		for(int i=x;i>0;i-=lowbit(i)){
			res+=tree[i];
		}
        return res;
	}
	int reversePairs(vector<int>& nums) {
        memset(tree,0,sizeof(tree));
		auto temp=nums;
		sort(temp.begin(),temp.end());
		for(int& num:nums){
			num=lower_bound(temp.begin(),temp.end(),num)-temp.begin()+1;
		}
		N=nums.size();
		int res=0;
		for(int i=N-1;i>=0;i--){
			add(nums[i],1);
			res+=query(nums[i]-1);
		}
		return res;
    }
};
/* 
 n 名士兵站成一排。每个士兵都有一个 独一无二 的评分 rating 。

每 3 个士兵可以组成一个作战单位，分组规则如下：

    从队伍中选出下标分别为 i、j、k 的 3 名士兵，他们的评分分别为 rating[i]、rating[j]、rating[k]
    作战单位需满足： rating[i] < rating[j] < rating[k] 或者 rating[i] > rating[j] > rating[k] ，其中  0 <= i < j < k < n

请你返回按上述条件可以组建的作战单位数量。每个士兵都可以是多个作战单位的一部分。
1395
n == rating.length
3 <= n <= 1000
1 <= rating[i] <= 10^5
树状数组每次找这个数的前和，后和，ans为乘积
 */
class Solution {
public:
	int tree[1001];
	int N;
	int lowbit(int x){
		return x&(-x);
	}
	void add(int x,int val){
		for(int i=x;i<=N;i+=lowbit(i)){
			tree[i]+=val;
		}
	}
	int query(int x){
		int res=0;
		for(int i=x;i>0;i-=lowbit(i)){
			res+=tree[i];
		}
		return res;
	}
    int numTeams(vector<int>& rating) {
		//离散化
		set<int> st(rating.begin(),rating.end());
		vector<int> temp;
		for(auto i:st){
			temp.emplace_back(i);
		}
		for(auto &i:rating){
			i=lower_bound(temp.begin(),temp.end(),i)-temp.begin()+1;
		}
		N=rating.size();
		int res=0;
		int M1[N],m1[N],M2[N],m2[N];
		for(int i=0;i<N;i++){
			m1[i]=query(rating[i]-1);
            m2[i]=query(N)-query(rating[i]);
			add(rating[i],1);
		}
		memset(tree,0,sizeof(tree));
		for(int i=N-1;i>=0;i--){
			M1[i]=query(rating[i]-1);
            M2[i]=query(N)-query(rating[i]);
			add(rating[i],1);
		}
		for(int i=0;i<N;i++){
			res+=M2[i]*m1[i]+M1[i]*m2[i];
		}
		return res;
	}
};
/* 
给你一个二维整数数组 rectangles ，其中 rectangles[i] = [li, hi] 表示第 i 个矩形长为 li 高为 hi 。给你一个二维整数数组 points ，其中 points[j] = [xj, yj] 是坐标为 (xj, yj) 的一个点。

第 i 个矩形的 左下角 在 (0, 0) 处，右上角 在 (li, hi) 。

请你返回一个整数数组 count ，长度为 points.length，其中 count[j]是 包含 第 j 个点的矩形数目。

如果 0 <= xj <= li 且 0 <= yj <= hi ，那么我们说第 i 个矩形包含第 j 个点。如果一个点刚好在矩形的 边上 ，这个点也被视为被矩形包含。
6043
 */
class Solution {
public:
    vector<int> countRectangles(vector<vector<int>>& rectangles, vector<vector<int>>& points) {
        
    }
};
/* 
给你一个整数数组 nums 以及两个整数 lower 和 upper 。求数组中，值位于范围 [lower, upper] （包含 lower 和 upper）之内的 区间和的个数 。

区间和 S(i, j) 表示在 nums 中，位置从 i 到 j 的元素之和，包含 i 和 j (i ≤ j)。
327
5 15
1 1 2 5 6 7 1 1 2
1 2 4 9 15 22 23 24 26

    1 <= nums.length <= 105
    -231 <= nums[i] <= 231 - 1
    -105 <= lower <= upper <= 105
    题目数据保证答案是一个 32 位 的整数
 */
class Solution {
public:
	int tree[100002];
	int N;
	int lowbit(int x){
		return x&(-x);
	}
	void add(int x,int val){
		for(int i=x;i<=N;i+=lowbit(i)){
			tree[i]+=val;
		}
	}
	int query(int x){
		int res=0;
		for(int i=x;i>0;i-=lowbit(i)){
			res+=tree[i];
		}
		return res;
	}
    int countRangeSum(vector<int>& nums, int lower, int upper) {
		N=nums.size();
		vector<int> presum=nums;
		for(int i=1;i<N;i++){
			presum[i]+=presum[i-1];
		}
		//离散化
		set<int> st(presum.begin(),presum.end());
		vector<int> temp(st.begin(),st.end());
        for(int i:temp){
            cout<<i<<" ";
        }
        cout<<endl;
		auto help=presum;
		for(int &i:presum){
			i=lower_bound(temp.begin(),temp.end(),i)-temp.begin()+1;
            cout<<i<<" ";
		}
        cout<<endl;
		int res=0;
        memset(tree,0,sizeof(tree));
		for(int i=0;i<N;i++){
			int l=lower_bound(temp.begin(),temp.end(),help[i]-upper)-temp.begin();
			int r=upper_bound(temp.begin(),temp.end(),help[i]-lower)-temp.begin();
            cout<<help[i]-upper<<" "<<help[i]-lower<<endl;
            cout<<l<<" "<<r<<endl;
            res+=query(r)-query(l-1);
            add(presum[i],1);
		}
		return res;
    }
};