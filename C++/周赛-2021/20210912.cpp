#include "head.h"
/* 
给你一个下标从 0 开始的字符串 word 和一个字符 ch 。找出 ch 第一次出现的下标 i ，反转 word 中从下标 0 开始、直到下标 i 结束（含下标 i ）的那段字符。
如果 word 中不存在字符 ch ，则无需进行任何操作。

    例如，如果 word = "abcdefd" 且 ch = "d" ，那么你应该 反转 从下标 0 开始、直到下标 3 结束（含下标 3 ）。结果字符串将会是 "dcbaefd" 。

返回 结果字符串 。
 */
class Solution {
public:
    string reversePrefix(string word, char ch) {
        int i=0;
        for(;i<word.size();i++){
            if(word[i]==ch){
                break;
            }
        }
        string res;
        if(i==word.size()){
            return word;
        }
        for(int j=i;j>=0&&j<word.size();j--){
            res+=word[j];
        }
        i++;
        for(;i<word.size();i++){
            res+=word[i];
        }
        return res;
    }
};
/* 
用一个下标从 0 开始的二维整数数组 rectangles 来表示 n 个矩形，其中 rectangles[i] = [widthi, heighti] 表示第 i 个矩形的宽度和高度。

如果两个矩形 i 和 j（i < j）的宽高比相同，则认为这两个矩形 可互换 。更规范的说法是，两个矩形满足 widthi/heighti == widthj/heightj（使用实数除法而非整数除法），则认为这两个矩形 可互换 。

计算并返回 rectangles 中有多少对 可互换 矩形。
 */
class Solution {
public:
    long long interchangeableRectangles(vector<vector<int>>& rectangles) {
        map<double,int> mp;
        for(auto vec:rectangles){
            double i=vec[1]/vec[0];
            mp[i]++;
        }
        long long res;
        for(auto [x,y]:mp){
            if(y>1){
                res+=(y-1)*y/2;
            }
        }
        return res;
    }
};
/* 
给你一个字符串 s ，请你找到 s 中两个 不相交回文子序列 ，使得它们长度的 乘积最大 。两个子序列在原字符串中如果没有任何相同下标的字符，则它们是 不相交 的。

请你返回两个回文子序列长度可以达到的 最大乘积 。

子序列 指的是从原字符串中删除若干个字符（可以一个也不删除）后，剩余字符不改变顺序而得到的结果。如果一个字符串从前往后读和从后往前读一模一样，那么这个字符串是一个 回文字符串 。
 */
class Solution {
public:
    int maxProduct(string s) {
        
    }
};
/* 
有一棵根节点为 0 的 家族树 ，总共包含 n 个节点，节点编号为 0 到 n - 1 。给你一个下标从 0 开始的整数数组 parents ，其中 parents[i] 是节点 i 的父节点。由于节点 0 是 根 ，所以 parents[0] == -1 。

总共有 105 个基因值，每个基因值都用 闭区间 [1, 105] 中的一个整数表示。给你一个下标从 0 开始的整数数组 nums ，其中 nums[i] 是节点 i 的基因值，且基因值 互不相同 。

请你返回一个数组 ans ，长度为 n ，其中 ans[i] 是以节点 i 为根的子树内 缺失 的 最小 基因值。

节点 x 为根的 子树 包含节点 x 和它所有的 后代 节点。
 */
class node{
public:
    int val;
    int index;
    node *left,*right;
    node(int val,int index):val(val),index(index),left(nullptr),right(nullptr){};
};
class Solution {
public:
    map<int,vector<int>> mp;
    map<int,set<int>> msp;
    node* buildtree(vector<int>& nums, int index){
        node* root=new node(nums[index],index);
        msp[index].emplace(nums[index]);
        if(mp.count(index)){
            int l=mp[index][0];
            root->left=buildtree(nums,l);
            msp[index].emplace(msp[l]);
            if(mp[index].size()>1){
                int r=mp[index][1];
                root->left=buildtree(nums,r);
                msp[index].emplace(msp[r]);
            }
        }
        return root;
    }
    vector<int> smallestMissingValueSubtree(vector<int>& parents, vector<int>& nums) {
        for(int i=0;i<parents.size();i++){
            mp[parents[i]].emplace_back(i);
        }
        node* root=buildtree(nums,0);
        vector<int> res;
        for(int i=0;i<nums.size();i++){
            int index=1;
            for(auto j:msp[i]){
                if(j!=index){
                    res.emplace_back(index);
                    break;
                }
                index++;
            }
        }
        return res;
    }
};
