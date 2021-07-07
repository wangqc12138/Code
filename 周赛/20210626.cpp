#include "head.h"
/* 
给你一个下标从 0 开始的整数数组 nums ，如果 恰好 删除 一个 元素后，数组 严格递增 ，那么请你返回 true ，否则返回 false 。
如果数组本身已经是严格递增的，请你也返回 true 。

数组 nums 是 严格递增 的定义为：对于任意下标的 1 <= i < nums.length 都满足 nums[i - 1] < nums[i] 。
 */
class Solution {
public:
    bool canBeIncreasing(vector<int>& nums) {
        for(int i=0;i<nums.size();i++){
            vector<int> temp;
            for(int j=0;j<nums.size();j++){
                if(j==i){
                    continue;
                }
                temp.emplace_back(nums[j]);
            }
            int j=1;
            for(;j<temp.size();j++){
                if(temp[j]<=temp[j-1]){
                    break;
                }
            }
            if(j==temp.size()){
                return true;
            }
        }
        return false;
    }
};
/* 
给你两个字符串 s 和 part ，请你对 s 反复执行以下操作直到 所有 子字符串 part 都被删除：

找到 s 中 最左边 的子字符串 part ，并将它从 s 中删除。
请你返回从 s 中删除所有 part 子字符串以后得到的剩余字符串。

一个 子字符串 是一个字符串中连续的字符序列。
 */
class Solution {
public:
    string removeOccurrences(string s, string part) {
        string res;

    }
};