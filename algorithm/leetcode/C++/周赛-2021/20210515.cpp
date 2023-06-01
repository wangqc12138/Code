#include "head.h"
/* 
一个 句子 指的是一个序列的单词用单个空格连接起来，且开头和结尾没有任何空格。每个单词都只包含小写或大写英文字母。

我们可以给一个句子添加 从 1 开始的单词位置索引 ，并且将句子中所有单词 打乱顺序 。

比方说，句子 "This is a sentence" 可以被打乱顺序得到 "sentence4 a3 is2 This1" 或者 "is2 sentence4 This1 a3" 。
给你一个 打乱顺序 的句子 s ，它包含的单词不超过 9 个，请你重新构造并得到原本顺序的句子。
 */
class Solution {
public:
    string sortSentence(string s) {
        string str[9];
        string temp;
        int num=0;
        for(int i=0;i<s.size();i++){
            if(s[i]>='1'&&s[i]<='9'){
                str[s[i]-'1']=temp;
                temp="";
                num++;
                i++;
                continue;
            }
            temp+=s[i];
        }
        string res;
        for(int i=0;i<num;i++){
            res+=str[i];
            if(i==num-1){
                break;
            }else{
                res+=" ";
            }
        }
        return res;
    }
};
/* 
给你两个整数 memory1 和 memory2 分别表示两个内存条剩余可用内存的位数。现在有一个程序每秒递增的速度消耗着内存。

在第 i 秒（秒数从 1 开始），有 i 位内存被分配到 剩余内存较多 的内存条（如果两者一样多，则分配到第一个内存条）。如果两者剩余内存都不足 i 位，那么程序将 意外退出 。

请你返回一个数组，包含 [crashTime, memory1crash, memory2crash] ，其中 crashTime是程序意外退出的时间（单位为秒）， memory1crash 和 memory2crash 分别是两个内存条最后剩余内存的位数。
 */
class Solution {
public:
    vector<int> memLeak(int memory1, int memory2) {
        int i=1;
        while(memory1>=i||memory2>=i){
            if(memory1>=memory2){
                memory1-=i;
            }else{
                memory2-=i;
            }
            i++;
        }
        return vector<int>{i,memory1,memory2};
    }
};
/* 
给你一个 m x n 的字符矩阵 box ，它表示一个箱子的侧视图。箱子的每一个格子可能为：

'#' 表示石头
'*' 表示固定的障碍物
'.' 表示空位置
这个箱子被 顺时针旋转 90 度 ，由于重力原因，部分石头的位置会发生改变。每个石头会垂直掉落，直到它遇到障碍物，另一个石头或者箱子的底部。重力 不会 影响障碍物的位置，同时箱子旋转不会产生惯性 ，也就是说石头的水平位置不会发生改变。

题目保证初始时 box 中的石头要么在一个障碍物上，要么在另一个石头上，要么在箱子的底部。

请你返回一个 n x m的矩阵，表示按照上述旋转后，箱子内的结果。
 */
class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& box) {
        int m=box.size(),n=box[0].size();
        vector<vector<char>> res(n,vector<char>(m));
        vector<char> temp;
        for(int j=0;j<n;j++){
            for(int i=m-1;i>=0;i--){
                temp.push_back(box[i][j]);
            }
        }
        int k=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                res[i][j]=temp[k++];
                cout<<res[i][j]<<" ";
            }
            cout<<endl;
        }

        for(int j=0;j<m;j++){
            int d=0;
            for(int i=0;i<n;i++){
                if(res[i][j]=='#'){
                    d++;
                }
                if(res[i][j]=='*'){
                    for(int k=i-1;k>=0;k--){
                        if(res[k][j]=='*'){
                            break;
                        }
                        if(d>0){
                            res[k][j]='#';
                            d--;
                        }else{
                            res[k][j]='.';
                        }
                    }
                }
            }
            if(d>0){
                for(int k=n-1;k>=0;k--){
                    if(res[k][j]=='*'){
                        break;
                    }
                    if(d>0){
                        res[k][j]='#';
                        d--;
                    }else{
                        res[k][j]='.';
                    }
                }
            }
        }
        return res;
    }
};
/* 
给你一个整数数组 nums ，请你返回所有下标对 0 <= i, j < nums.length 的 floor(nums[i] / nums[j]) 结果之和。由于答案可能会很大，请你返回答案对109 + 7 取余 的结果。

函数 floor() 返回输入数字的整数部分。
 */
class Solution {
public:
    int sumOfFlooredPairs(vector<int>& nums) {
        int n=nums.size();
        long long res=n;
        sort(nums.begin(),nums.end());
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                res+=floor(nums[j]/nums[i]);
            }
        }
        return (int)res%1000000007;
    }
};