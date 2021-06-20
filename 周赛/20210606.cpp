#include "head.h"
/* 
给你两个大小为 n x n 的二进制矩阵 mat 和 target 。现 以 90 度顺时针轮转 矩阵 mat 中的元素 若干次 ，如果能够使 mat 与 target 一致，返回 true ；否则，返回 false 。
 */
class Solution {
public:
    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
        int x1=0,x2=mat.size()-1,y1=0,y2=mat.size()-1;
        while(x1<x2){
            if(process(mat,x1,x2,y1,y2)!=process(target,x1,x2,y1,y2)){
                return false;
            }
        }
    }
    vector<int> process(vector<vector<int>> matrix,int x1,int x2,int y1,int y2){
        vector<int> res;
        int a1=x1,a2=x2,b1=y1,b2=y2;
        while(b1<y2){
            res.emplace_back(matrix[a1,b1++]);
        }
        while(a1<x2){
            res.emplace_back(matrix[a1++][b1]);
        }
        while(b2>y1){
            res.emplace_back(matrix[a2][b2--]);
        }
        while(a2>x1){
            res.emplace_back(matrix[a2--][b2]);
        }
        return res;
    }
};