#include "head.h"
/* 
一个数组的 异或总和 定义为数组中所有元素按位 XOR 的结果；如果数组为 空 ，则异或总和为 0 。

例如，数组 [2,5,6] 的 异或总和 为 2 XOR 5 XOR 6 = 1 。
给你一个数组 nums ，请你求出 nums 中每个 子集 的 异或总和 ，计算并返回这些值相加之 和 。

注意：在本题中，元素 相同 的不同子集应 多次 计数。

数组 a 是数组 b 的一个 子集 的前提条件是：从 b 删除几个（也可能不删除）元素能够得到 a 。
 */
class Solution {
public:
    int res=0;
    int subsetXORSum(vector<int>& nums) {
        dfs(nums,0,0);
        return res;
    }
    void dfs(vector<int>& nums,int index,int t){
        res+=t;
        for(int i=index;i<nums.size();i++){
            t^=nums[i];
            dfs(nums,i+1,t);
            t^=nums[i];
        }
    }
};
/* 
给你一个二进制字符串 s ，现需要将其转化为一个 交替字符串 。请你计算并返回转化所需的 最小 字符交换次数，如果无法完成转化，返回 -1 。

交替字符串 是指：相邻字符之间不存在相等情况的字符串。例如，字符串 "010" 和 "1010" 属于交替字符串，但 "0100" 不是。

任意两个字符都可以进行交换，不必相邻 。
1 <= s.length <= 1000
s[i] 的值为 '0' 或 '1'
 */
class Solution {
public:
    int minSwaps(string s) {
        int n=0;
        for(auto i:s){
            if(i=='0'){
                n++;
            }else{
                n--;
            }
        }
        if(n<-1||n>1){
            return -1;
        }
        int res,j=0,n0=0,n1=0;
        for(int i=0;i<s.size();i+=2){
            if(s[i]=='0'){
                n0++;
            }else{
                n1++;
            }
            j++;
        }
        if(n==0){
            res=min(n0,n1);
        }
        if(n==1){
            res=n1;
        }
        if(n==-1){
            res=n0;
        }
        return res;
    }
};
/* 
给你两个整数数组 nums1 和 nums2 ，请你实现一个支持下述两类查询的数据结构：

累加 ，将一个正整数加到 nums2 中指定下标对应元素上。
计数 ，统计满足 nums1[i] + nums2[j] 等于指定值的下标对 (i, j) 数目（0 <= i < nums1.length 且 0 <= j < nums2.length）。
实现 FindSumPairs 类：

FindSumPairs(int[] nums1, int[] nums2) 使用整数数组 nums1 和 nums2 初始化 FindSumPairs 对象。
void add(int index, int val) 将 val 加到 nums2[index] 上，即，执行 nums2[index] += val 。
int count(int tot) 返回满足 nums1[i] + nums2[j] == tot 的下标对 (i, j) 数目。
1 <= nums1.length <= 1000
1 <= nums2.length <= 105
1 <= nums1[i] <= 109
1 <= nums2[i] <= 105
0 <= index < nums2.length
1 <= val <= 105
1 <= tot <= 109
最多调用 add 和 count 函数各 1000 次
 */
class FindSumPairs {
public:
    FindSumPairs(vector<int>& nums1, vector<int>& nums2) {
        for(int i:nums1){
            mp1[i]++;
        }
        for(int i:nums2){
            nums.push_back(i);
            mp2[i]++;
        }
    }
    
    void add(int index, int val) {
        int n=nums[index];
        if(--mp2[n]==0){
            mp2.erase(n);
        }
        nums[index]+=val;
        mp2[n+val]++;
    }
    
    int count(int tot) {
        int res=0;
        for(auto [i,j]:mp1){
            if(mp2.count(tot-i)){
                res+=j*mp2[tot-i];
            }
        }
        return res;
    }
    unordered_map<int,int> mp1;
    unordered_map<int,int> mp2;
    vector<int> nums;
};
/**
 * Your FindSumPairs object will be instantiated and called as such:
 * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
 * obj->add(index,val);
 * int param_2 = obj->count(tot);
 */