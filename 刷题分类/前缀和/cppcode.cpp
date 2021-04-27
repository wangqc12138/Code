/*
给定一个整数数组  nums，求出数组从索引 i 到 j（i ≤ j）范围内元素的总和，包含 i、j 两点。
实现 NumArray 类：
    NumArray(int[] nums) 使用数组 nums 初始化对象
    int sumRange(int i, int j) 返回数组 nums 从索引 i 到 j（i ≤ j）范围内元素的总和，包含 i、j 两点（也就是 sum(nums[i], nums[i + 1], ... , nums[j])）
303
*/
class NumArray {
public:
    vector<int> vec;
    NumArray(vector<int>& nums) {
        vec.resize(nums.size());
        
        for(int i=0;i<nums.size();i++){
            if(i==0){
                vec[0]=nums[0];  
            }else{
                vec[i]=vec[i-1]+nums[i];
            }
        }
    }
    
    int sumRange(int i, int j) {
        return i==0?vec[j]:vec[j]-vec[i-1];
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(i,j);
 */
/*
给定一个二维矩阵，计算其子矩形范围内元素的总和，该子矩阵的左上角为 (row1, col1) ，右下角为 (row2, col2) 。
304
*/
class NumMatrix {
public:
    NumMatrix(vector<vector<int>>& matrix) {
    	int m=matrix.size(),n=matrix[0].size();
    	sumMatrix=vector<vector<int>>(m,vector<int>(n));
    	for(int i=0;i<m;i++){
    		for(int j=0;j<n;j++){
    			if(i>0&&j>0){
    				sumMatrix[i][j]=sumMatrix[i-1][j]+sumMatrix[i][j-1]-sumMatrix[i-1][j-1]+matrix[i][j];
    			}else if(i>0){
    				sumMatrix[i][j]=sumMatrix[i-1][j]+matrix[i][j];
    			}else if(j>0){
    				sumMatrix[i][j]=sumMatrix[i][j-1]+matrix[i][j];
    			}else{
    				sumMatrix[i][j]=matrix[i][j];
    			}
    		}
    	}
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
    	if(row1==0&&col1==0){
    		return sumMatrix[row2][col2];
    	}else if(row1==0){
    		return sumMatrix[row2][col2]-sumMatrix[row2][col1-1];
    	}else if(col1==0){
    		return sumMatrix[row2][col2]-sumMatrix[row1-1][col2];
    	}else{
            return sumMatrix[row2][col2]-sumMatrix[row2][col1-1]-sumMatrix[row1-1][col2]+sumMatrix[row1-1][col1-1];
        }        
        return 0;
    }
private:
	vector<vector<int>> sumMatrix;
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */
/*
给你一个 m x n 的矩阵 matrix 和一个整数 k ，找出并返回矩阵内部矩形区域的不超过 k 的最大数值和。

题目数据保证总会存在一个数值和不超过 k 的矩形区域。
363
*/
//使用vector会超时
class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int m=matrix.size(),n=matrix[0].size(),res=INT_MIN;
        int sumMatrix[m][n];
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(i>0&&j>0){
                    sumMatrix[i][j]=sumMatrix[i-1][j]+sumMatrix[i][j-1]-sumMatrix[i-1][j-1]+matrix[i][j];
                }else if(i>0){
                    sumMatrix[i][j]=sumMatrix[i-1][j]+matrix[i][j];
                }else if(j>0){
                    sumMatrix[i][j]=sumMatrix[i][j-1]+matrix[i][j];
                }else{
                    sumMatrix[i][j]=matrix[i][j];
                }
            }
        }
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                for(int a=i;a<m;a++){
                    for(int b=j;b<n;b++){
                        int sum=0;
                        if(i==0&&j==0){
                            sum=sumMatrix[a][b];
                        }else if(i==0){
                            sum=sumMatrix[a][b]-sumMatrix[a][j-1];
                        }else if(j==0){
                            sum=sumMatrix[a][b]-sumMatrix[i-1][b];
                        }else{
                            sum=sumMatrix[a][b]-sumMatrix[a][j-1]-sumMatrix[i-1][b]+sumMatrix[i-1][j-1];
                        }
                        if(sum<k){
                            res=max(res,sum);
                        }else if(sum==k){
                            return k;
                        }
                    }
                }
            }
        }
        return res;
    }
};
/*
给定一个正整数、负整数和 0 组成的 N × M 矩阵，编写代码找出元素总和最大的子矩阵。

返回一个数组 [r1, c1, r2, c2]，其中 r1, c1 分别代表子矩阵左上角的行号和列号，r2, c2 分别代表右下角的行号和列号。若有多个满足条件的子矩阵，返回任意一个均可。

面试题 17.24. 最大子矩阵
*/
//暴力解--超时
class Solution {
public:
    vector<int> getMaxMatrix(vector<vector<int>>& matrix) {
    	int m=matrix.size(),n=matrix[0].size(),k=INT_MIN;
    	vector<int> res;
        int sumMatrix[m+1][n+1];
        for(int i=0;i<m;i++){
        	for(int j=0;j<n;j++){
            	sumMatrix[i+1][j+1]=sumMatrix[i][j+1]+sumMatrix[i+1][j]-sumMatrix[i][j]+matrix[i][j];
        	}
        }
        
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                for(int a=i;a<m;a++){
                    for(int b=j;b<n;b++){
                        int sum=sumMatrix[a+1][b+1]-sumMatrix[a+1][j]-sumMatrix[i][b+1]+sumMatrix[i][j];
                        if(sum>k){
                        	k=sum;
                        	res=vector<int>{i,j,a,b};
                        }
                    }
                }
            }
        }
        return res;
    }
};
class Solution {
public:
    vector<int> getMaxMatrix(vector<vector<int>>& matrix) {
    	vector<int> res;
    	int m=matrix.size(),n=matrix[0].size(),sum,maxsum=INT_MIN,row1,col1;
    	vector<int> colsum(n,0);
    	for(int i=0;i<m;i++){
    		for(int& cs:colsum){
    			cs=0;
    		}
    		for(int j=i;j<m;j++){
    			sum=0;
    			for(int k=0;k<n;k++){
    				colsum[k]+=matrix[j][k];
    				if(sum+colsum[k]>colsum[k]){
    					sum+=colsum[k];
    				}else{
    					row1=i;
    					col1=k;
    					sum=colsum[k];
    				}
    				if(sum>maxsum){
    					maxsum=sum;
    					res={row1,col1,j,k};
    				}
    			}
    		}
    	}
    	return res;
   	}
};
/*
给定一个数组 nums 和一个目标值 k，找到和等于 k 的最长子数组长度。如果不存在任意一个符合要求的子数组，则返回 0。
注意:
 nums 数组的总和是一定在 32 位有符号整数范围之内的。
 map插入数据
 使用insert：包含key不更新value
 使用【】：直接更新
 325
*/
class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        map<int,int> m;
        m[0]=-1;
        int sum=0,res=0;
        for(int i=0;i<nums.size();i++){
            sum+=nums[i];
            if(m.count(sum-k)){
                res=max(res,i-m[sum-k]);
            }
            if(!m.count(sum)){
                m[sum]=i;
            }
        }
        return res;
    }
};
/*
给定一个二进制数组, 找到含有相同数量的 0 和 1 的最长连续子数组（的长度）。
525
*/
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        map<int,int> m;
        m[0]=-1;
        int sum=0,res=0;
        for(int i=0;i<nums.size();i++){
            sum+=nums[i]==0?-1:1;
            if(m.count(sum)){
                res=max(res,i-m[sum]);
            }
            if(!m.count(sum)){
                m[sum]=i;
            }
        }
        return res;
    }
};
/*
给你一个字符串 s ，请你返回满足以下条件的最长子字符串的长度：每个元音字母，即 'a'，'e'，'i'，'o'，'u' ，在子字符串中都恰好出现了偶数次。
1371

    1 <= s.length <= 5 x 10^5
    s 只包含小写英文字母。

*/
class Solution {
public:
    int findTheLongestSubstring(string s) {

    }
};
/*
给你一个整数数组 nums 和一个整数 k。
如果某个 连续 子数组中恰好有 k 个奇数数字，我们就认为这个子数组是「优美子数组」。
请返回这个数组中「优美子数组」的数目。
1248
*/
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        unordered_map<int,int> um;
        int res=0,sum=0;
        um[0]=1;
        for(int i=0;i<nums.size();i++){
            sum+=nums[i]%2;
            if(um.count(sum-k)){
                //+前面sum-k个奇数的子数组
                res+=um[sum-k];
            }
            //sum个奇数的数组+1
            um[sum]++;
            //求最长的子数组
            /*
            if(um.count(sum-k)){
                res=max(res,i-um[sum-k]);
            }
            if(!um.count(sum)){
                um[sum]=i;
            }
            */
        }
        return res;
    }
};
