#include "head.h"
/* 
给你一个二维整数数组 ranges 和两个整数 left 和 right 。每个 ranges[i] = [starti, endi] 表示一个从 starti 到 endi 的 闭区间 。

如果闭区间 [left, right] 内每个整数都被 ranges 中 至少一个 区间覆盖，那么请你返回 true ，否则返回 false 。

已知区间 ranges[i] = [starti, endi] ，如果整数 x 满足 starti <= x <= endi ，那么我们称整数x 被覆盖了。
 */
class Solution {
public:
    bool isCovered(vector<vector<int>>& ranges, int left, int right) {
        unordered_set<int> uset;
        for(auto vec:ranges){
            for(int i=vec[0];i<=vec[1];i++){
                uset.emplace(i);
            }
        }
        for(int i=left;i<=right;i++){
            if(!uset.count(i)){
                return false;
            }
        }
        return true;
    }
};
/* 
一个班级里有 n 个学生，编号为 0 到 n - 1 。每个学生会依次回答问题，编号为 0 的学生先回答，然后是编号为 1 的学生，
以此类推，直到编号为 n - 1 的学生，然后老师会重复这个过程，重新从编号为 0 的学生开始回答问题。

给你一个长度为 n 且下标从 0 开始的整数数组 chalk 和一个整数 k 。一开始粉笔盒里总共有 k 支粉笔。
当编号为 i 的学生回答问题时，他会消耗 chalk[i] 支粉笔。如果剩余粉笔数量 严格小于 chalk[i] ，那么学生 i 需要 补充 粉笔。

请你返回需要 补充 粉笔的学生 编号 。
 */
class Solution {
public:
    int chalkReplacer(vector<int>& chalk, int k) {
        long long sum=0;
        for(int i=0;i<chalk.size();i++){
            sum+=chalk[i];
        }
        sum=k%sum;
        for(int i=0;i<chalk.size();i++){
            if(chalk[i]>sum){
                return i;
            }
            sum-=chalk[i];
        }
        return 0;
    }
};
/* 
一个 k x k 的 幻方 指的是一个 k x k 填满整数的方格阵，且每一行、每一列以及两条对角线的和 全部相等 。幻方中的整数 不需要互不相同 。显然，每个 1 x 1 的方格都是一个幻方。

给你一个 m x n 的整数矩阵 grid ，请你返回矩阵中 最大幻方 的 尺寸 （即边长 k）。
 */
class Solution {
public:
    vector<vector<int>> vec1,vec2;
    int m,n;
    int largestMagicSquare(vector<vector<int>>& grid) {
        int res=0;
        m=grid.size(),n=grid[0].size();
        if(m==1||n==1){
            return 1;
        }
        vec1.resize(m);
        vec2.resize(n);
        for(int i=0;i<m;i++){
            int sum=0;
            for(int j=0;j<n;j++){
                sum+=grid[i][j];
                vec1[i].emplace_back(sum);
            } 
        }
        for(int i=0;i<n;i++){
            int sum=0;
            for(int j=0;j<m;j++){
                sum+=grid[j][i];
                vec1[i].emplace_back(sum);
            } 
        }
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                for(int len=1;len+i<m&&len+j<n&&len>res;len++){
                    if(help(grid,i,j,i+len,j+len)){
                        res=max(res,len);
                    }
                }
            }
        }
        return res;
    }
    bool help(vector<vector<int>>& grid,int a,int b,int c,int d){
        if(c>=m||d>=n){
            return false;
        }
        int k=vec1[a][d]-vec1[a][b]+grid[a][b];
        for(int i=a+1;i<=c;i++){
            if(vec1[i][d]-vec1[i][b]+grid[i][b]!=k){
                return false;
            }
        }
        for(int i=b+1;i<=d;i++){
            if(vec1[i][c]-vec1[i][a]+grid[i][a]!=k){
                return false;
            }
        }
        int sum=0;
        for(int i=a,j=b;i<=c;i++,j++){
            sum+=grid[i][j];
        }
        if(sum!=k){
            return false;
        }
        for(int i=a,j=d;i<=c;i++,j--){
            sum+=grid[i][j];
        }
        if(k!=sum){
            return false;
        }
        return true;
    } 
};
/* 
给你一个 有效的 布尔表达式，用字符串 expression 表示。这个字符串包含字符 '1'，'0'，'&'（按位 与 运算），'|'（按位 或 运算），'(' 和 ')' 。

比方说，"()1|1" 和 "(1)&()" 不是有效 布尔表达式。而 "1"， "(((1))|(0))" 和 "1|(0&(1))" 是 有效 布尔表达式。
你的目标是将布尔表达式的 值 反转 （也就是将 0 变为 1 ，或者将 1 变为 0），请你返回达成目标需要的 最少操作 次数。

比方说，如果表达式 expression = "1|1|(0&0)&1" ，它的 值 为 1|1|(0&0)&1 = 1|1|0&1 = 1|0&1 = 1&1 = 1 。我们想要执行操作将 新的 表达式的值变成 0 。
可执行的 操作 如下：

将一个 '1' 变成一个 '0' 。
将一个 '0' 变成一个 '1' 。
将一个 '&' 变成一个 '|' 。
将一个 '|' 变成一个 '&' 。
注意：'&' 的 运算优先级 与 '|' 相同 。计算表达式时，括号优先级 最高 ，然后按照 从左到右 的顺序运算。
 */
class Solution {
public:
    int minOperationsToFlip(string expression) {
        int start=0,end=expression.size()-1;
        while(start<end){
            if(expression[start]=='('&&expression[end]==')'){
                start++;end--;
            }
        }
        stack<char> ms;
        for(;start<=end;start++){
            if(expression[start]==')'){
                
            }else{
                ms.emplace(expression[start]);
            }
        }
    }
};