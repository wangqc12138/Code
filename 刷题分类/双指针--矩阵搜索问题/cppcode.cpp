#include "../../head.h"
/* 
给定一个非负整数 c ，你要判断是否存在两个整数 a 和 b，使得 a2 + b2 = c 。
633
0 <= c <= 231 - 1
不能用int 会超出int范围
相当于在一个矩阵中找值
矩阵行递增，列递增
*/
class Solution {
public:
    bool judgeSquareSum(int c) {
        long long left=0,right=(int)sqrt(c);
        while(left<=right){
            long long tmp=left*left+right*right;
            if(tmp==c){
                return true;
            }else if(tmp>c){
                right--;
            }else{
                left++;
            }
        }
        return false;
    }
};
/* 
编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target 。该矩阵具有以下特性：

    每行的元素从左到右升序排列。
    每列的元素从上到下升序排列。
240
 */
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m=matrix.size(),n=matrix[0].size();
        int i=0,j=n-1;
        while(i<m&&j>=0){
            if(matrix[i][j]==target){
                return true;
            }else if(matrix[i][j]<target){
                i++;
            }else{
                j--;
            }
        }
        return false;
    }
};
//此题也是可以用二分来做
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        
    }
};
/* 
编写一个高效的算法来判断 m x n 矩阵中，是否存在一个目标值。该矩阵具有如下特性：

    每行中的整数从左到右按升序排列。
    每行的第一个整数大于前一行的最后一个整数。
74
 */
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m=matrix.size(),n=matrix[0].size();
        int i=0,j=n-1;
        while(i<m&&j>=0){
            if(matrix[i][j]==target){
                return true;
            }else if(matrix[i][j]<target){
                i++;
            }else{
                j--;
            }
        }
        return false;
    }
};
/* 
给你 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0) 。找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
11
 */
class Solution {
public:
    int maxArea(vector<int>& height) {
        int left=0,right=height.size()-1;
        int res=0;
        while(left<right){
            int l=height[left],r=height[right],w=right-left;
            if(l<r){
                res=max(res,l*w);
                left++;
            }else{
                res=max(res,r*w);
                right--;
            }
        }
        return res;
        
    }
};