/*
给定一个整数数组  nums，求出数组从索引 i 到 j（i ≤ j）范围内元素的总和，包含 i、j 两点。
实现 NumArray 类：
    NumArray(int[] nums) 使用数组 nums 初始化对象
    int sumRange(int i, int j) 返回数组 nums 从索引 i 到 j（i ≤ j）范围内元素的总和，包含 i、j 两点（也就是 sum(nums[i], nums[i + 1], ... , nums[j])）
303
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