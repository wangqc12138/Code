#include "../head.h"
/* 
给你一个仅由数字组成的字符串 s 。

请你判断能否将 s 拆分成两个或者多个 非空子字符串 ，使子字符串的 数值 按 降序 排列，且每两个 相邻子字符串 的数值之 差 等于 1 。

    例如，字符串 s = "0090089" 可以拆分成 ["0090", "089"] ，数值为 [90,89] 。这些数值满足按降序排列，且相邻值相差 1 ，这种拆分方法可行。
    另一个例子中，字符串 s = "001" 可以拆分成 ["0", "01"]、["00", "1"] 或 ["0", "0", "1"] 。然而，所有这些拆分方法都不可行，因为对应数值分别是 [0,1]、[0,1] 和 [0,0,1] ，都不满足按降序排列的要求。

如果可以按要求拆分 s ，返回 true ；否则，返回 false 。

子字符串 是字符串中的一个连续字符序列。

 */
class Solution {
public:
    bool res=false;
    bool splitString(string s) {
        int n=s.size();
        vector<vector<unsigned long long>> nums(n,vector<unsigned long long>(n,0));
        for(int i=0;i<n;i++){
            for(int j=i;j<n;j++){
                if(i==0&&j==n-1){
                    continue;
                }
                nums[i][j]=stoull(s.substr(i,j-i+1));
            }
        }
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                dfs(i+1,j,nums[0][i],n,nums);
            }
        }
        return res;
    }
    void dfs(int i,int j,unsigned long long pre,int n,vector<vector<unsigned long long>> nums){
        if(pre!=-1&&nums[i][j]-pre!=-1){
            return;
        }
        if(j==n-1){
            res=true;
        }
        for(int k=j+1;k<n;k++){
            dfs(j+1,k,nums[i][j],n,nums);
        }
    }
};
/* 
给你一个表示大整数的字符串 num ，和一个整数 k 。

如果某个整数是 num 中各位数字的一个 排列 且它的 值大于 num ，则称这个整数为 妙数 。可能存在很多妙数，但是只需要关注 值最小 的那些。

    例如，num = "5489355142" ：
        第 1 个最小妙数是 "5489355214"
        第 2 个最小妙数是 "5489355241"
        第 3 个最小妙数是 "5489355412"
        第 4 个最小妙数是 "5489355421"

返回要得到第 k 个 最小妙数 需要对 num 执行的 相邻位数字交换的最小次数 。

测试用例是按存在第 k 个最小妙数而生成的。
 */