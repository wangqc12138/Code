#include "head.h"
/* 
给你一个按 非递减顺序 排列的数组 nums ，返回正整数数目和负整数数目中的最大值。

    换句话讲，如果 nums 中正整数的数目是 pos ，而负整数的数目是 neg ，返回 pos 和 neg二者中的最大值。

注意：0 既不是正整数也不是负整数。
 */
class Solution {
public:
    int maximumCount(vector<int>& nums) {
        int m=0,n=0;
        for(int i:nums){
            m+=i>0;
            n+=i<0;
        }
        return max(m,n);
    }
};
/* 
给你一个下标从 0 开始的整数数组 nums 和一个整数 k 。你的 起始分数 为 0 。

在一步 操作 中：

    选出一个满足 0 <= i < nums.length 的下标 i ，
    将你的 分数 增加 nums[i] ，并且
    将 nums[i] 替换为 ceil(nums[i] / 3) 。

返回在 恰好 执行 k 次操作后，你可能获得的最大分数。

向上取整函数 ceil(val) 的结果是大于或等于 val 的最小整数。
 */
class Solution {
public:
    long long maxKelements(vector<int>& nums, int k) {
        priority_queue<int> mpq;
        for(int i:nums){
            mpq.emplace(i);
        }
        int res=0;
        while(!mpq.empty()&&k--){
            int t=mpq.top();
            mpq.pop();
            res+=t;
            mpq.emplace((t+2)/3);
        }
        return res;
    }
};
/* 
给你两个下标从 0 开始的字符串 word1 和 word2 。

一次 移动 由以下两个步骤组成：

    选中两个下标 i 和 j ，分别满足 0 <= i < word1.length 和 0 <= j < word2.length ，
    交换 word1[i] 和 word2[j] 。

如果可以通过 恰好一次 移动，使 word1 和 word2 中不同字符的数目相等，则返回 true ；否则，返回 false 。
 */
class Solution {
public:
    bool isItPossible(string word1, string word2) {
        map<int,int> m1,m2;
        for(auto c:word1){
            m1[c]++;
        }
        for(auto c:word2){
            m2[c]++;
        }
        for(int i='a';i<='z';i++){
            for(int j='a';j<='z';j++){
                if(m1.count(i)&&m2.count(j)){
                    auto t1=m1,t2=m2;
                    if(--t1[i]==0){
                        t1.erase(i);
                    }
                    t2[i]++;
                    if(--t2[j]==0){
                        t2.erase(j);
                    }
                    t1[j]++;
                    if(t1.size()==t2.size()){
                        return true;
                    }
                }
            }
        }
        return false;
    }
};