#include "../head.h"
/*
给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。
不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。
元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。
27
*/
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
    	//双指针
    	int j=0;
    	for(int i=0;i<nums.size();i++){
    		if(nums[i]!=val){
    			nums[j++]=nums[i];
    		}
    	}
    	return j;

    }
};
/*
实现 strStr() 函数。
给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 needle 字符串出现的第一个位置（下标从 0 开始）。如果不存在，则返回  -1 。
KMP算法
*/
class Solution {
public:
    int strStr(string haystack, string needle) {
        int m=needle.size(),n=haystack.size(),j=0,i=1;
        vector<int> next(m,0);
        //填入next数组
        for(;i<m;i++){
            while(needle[i]!=needle[j]){
                if(j==0){
                    next[i]=0;
                    break;
                }else{
                    j=next[j-1];
                }
            }
            if(needle[i]==needle[j]){
                next[i]=++j;
            }
        }
        //利用next数组比较
        i=0,j=0;
        while(i<n&&j<m){
            if(needle[j]==haystack[i]){
                i++;
                j++;
            }else if(j==0){
                i++;
            }
            else{
                j=next[j-1];
            } 
        }
        return j!=m?-1:i-m;
    }
};
/*
一条包含字母 A-Z 的消息通过以下映射进行了 编码 ：

'A' -> 1
'B' -> 2
...
'Z' -> 26

要 解码 已编码的消息，所有数字必须基于上述映射的方法，反向映射回字母（可能有多种方法）。例如，"11106" 可以映射为：

    "AAJF" ，将消息分组为 (1 1 10 6)
    "KJF" ，将消息分组为 (11 10 6)

注意，消息不能分组为  (1 11 06) ，因为 "06" 不能映射为 "F" ，这是由于 "6" 和 "06" 在映射中并不等价。

给你一个只含数字的 非空 字符串 s ，请计算并返回 解码 方法的 总数 。

题目数据保证答案肯定是一个 32 位 的整数。
91
*/
class Solution {
public:
    int numDecodings(string s) {
        int n=s.size();
        vector<int> dp(n+1);//下标可以理解为字符串长度
        dp[0]=1;//空字符有一种解码方法
        for(int i=1;i<=n;i++){
            if(s[i-1]!='0'){//当前所指不为‘0’，则为前一个长度的总数
                dp[i]=dp[i-1];
            }
            if(i>1&&s[i-2]!='0'&&10*(s[i-2]-'0')+s[i-1]-'0'<=26){//可以与前一个字符映射
                dp[i]+=dp[i-2];
            }
        }
        return dp[n];
    }
};

/*
给你一个 m x n 的矩阵 matrix 和一个整数 k ，找出并返回矩阵内部矩形区域的不超过 k 的最大数值和。

题目数据保证总会存在一个数值和不超过 k 的矩形区域。
363
*/
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
给你一个由 无重复 正整数组成的集合 nums ，请你找出并返回其中最大的整除子集 answer ，子集中每一元素对 (answer[i], answer[j]) 都应当满足：

    answer[i] % answer[j] == 0 ，或
    answer[j] % answer[i] == 0

如果存在多个有效解子集，返回其中任何一个均可。
368
*/
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int n=nums.size(),maxVal,maxSize=1;
        vector<int> dp(n,1),res;
        sort(nums.begin(),nums.end());
        for(int i=1;i<n;i++){
            for(int j=0;j<i;j++){
                if(nums[i]%nums[j]==0){
                    dp[i]=max(dp[i],dp[j]+1);
                }
            }
            if(dp[i]>maxSize){
                maxSize=dp[i];
                maxVal=nums[i];
            }
        }
        if(maxSize==1){
            return vector<int>{nums[0]};
        }
        for(int i=n-1;i>=0&&maxSize>0;i--){
            if(dp[i]==maxSize&&maxVal%nums[i]==0){
                res.push_back(nums[i]);
                maxSize--;
                maxVal=nums[i];
            }
        }
        return res;
    }
};
//20210424
/*
给你一个由不同整数组成的数组 nums ，和一个目标整数 target 。请你从 nums 中找出并返回总和为 target 的元素组合的个数。

题目数据保证答案符合 32 位整数范围。
377
*/
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        
    }
};
//20210425
/*
给你一棵二叉搜索树，请你 按中序遍历 将其重新排列为一棵递增顺序搜索树，使树中最左边的节点成为树的根节点，并且每个节点没有左子节点，只有一个右子节点。
897
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* dum=new TreeNode(0);
    TreeNode* increasingBST(TreeNode* root) {
        TreeNode* res=dum; 
        inorder(root);
        return res->right;
    }
    void inorder(TreeNode *root){
        if(root==nullptr){
            return;
        }
        inorder(root->left);
        dum->right=root;
        root->left=nullptr;
        dum=root;
        inorder(root->right);
    }
};
//20210426
/*
传送带上的包裹必须在 D 天内从一个港口运送到另一个港口。
传送带上的第 i 个包裹的重量为 weights[i]。每一天，我们都会按给出重量的顺序往传送带上装载包裹。我们装载的重量不会超过船的最大运载重量。
返回能在 D 天内将传送带上的所有包裹送达的船的最低运载能力。
1011
*/
//二分
class Solution {
public:
    int shipWithinDays(vector<int>& weights, int D) {
        int n=weights.size();
        int left=*max_element(weights.begin(),weights.end());
        int right=accumulate(weights.begin(),weights.end(),0);
        while(left<right){
            int mid=left+(right-left)/2;
            int temp=0,day=1;
            for(int w:weights){
                temp+=w;
                if(temp>mid){
                    day++;
                    temp=w;
                }
            }
            if(day>D){
                left=mid+1;
            }else{
                right=mid;
            }
        }
        return left;
    }
};
/*
给定二叉搜索树的根结点 root，返回值位于范围 [low, high] 之间的所有结点的值的和。
938
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int res=0;
    int rangeSumBST(TreeNode* root, int low, int high) {
        inorder(root,low,high);
        return res;
    }
    void inorder(TreeNode* root,int low, int high){
        if(root==nullptr){
            return;
        }
        inorder(root,low,high);
        if(root->val>=low&&root->val<=high){
            res+=root->val;
        }
        inorder(root,low,high);
    }
};
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
你的面前有一堵矩形的、由 n 行砖块组成的砖墙。这些砖块高度相同（也就是一个单位高）但是宽度不同。每一行砖块的宽度之和相等。

你现在要画一条 自顶向下 的、穿过 最少 砖块的垂线。如果你画的线只是从砖块的边缘经过，就不算穿过这块砖。
你不能沿着墙的两个垂直边缘之一画线，这样显然是没有穿过一块砖的。

给你一个二维数组 wall ，该数组包含这堵墙的相关信息。其中，wall[i] 是一个代表从左至右每块砖的宽度的数组。
你需要找出怎样画才能使这条线 穿过的砖块数量最少 ，并且返回 穿过的砖块数量 。
554
 */
class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        map<int,int> m;
        int n=wall.size();
        for(auto vec:wall){
            int k=0;
            for(auto i:vec){
                k+=i;
                m[k]++;
            }
            m.erase(k);
        }
        int res=n;
        /* for(auto [i,j]:m){
            //min函数不能包含size()?
            res=min(res,n-j);
        } */
        for(auto itr:m){
            res=min(res,n-itr.second);
        }
        return res;
    }
};
/* 
给你一个 32 位的有符号整数 x ，返回将 x 中的数字部分反转后的结果。

如果反转后整数超过 32 位的有符号整数的范围 [−231,  231 − 1] ，就返回 0。
假设环境不允许存储 64 位整数（有符号或无符号）。
7
 */
class Solution {
public:
    int reverse(int x) {
        long long res=0;
        while(x){
            res=res*10+x%10;
            x/=10;
        }
        return res==(int)res?res:0;
    }
};
/* 
给你一个整数数组 nums ，你可以对它进行一些操作。
每次操作中，选择任意一个 nums[i] ，删除它并获得 nums[i] 的点数。之后，你必须删除 所有 等于 nums[i] - 1 和 nums[i] + 1 的元素。
开始你拥有 0 个点数。返回你能通过这些操作获得的最大点数。
740
    1 <= nums.length <= 2 * 104
    1 <= nums[i] <= 104
 */
// 打家劫舍的变种，即选择抢一家就不能抢邻居
class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        int k=*max_element(nums.begin(),nums.end());
        vector<int> vec(k+1,0);
        for(int i:nums){
            vec[i]=i;
        }
        vector<int> dp(k+1);
        for(int i=2;i<k+1;i++){
            if(i==0){
                dp[i]=nums[i];
            }else if(i==1){
                dp[i]=max(dp[0],dp[1]);
            }else{
                dp[i]=max(dp[i-1],dp[i-2]+nums[i]);
            }
        }
        return dp[k];
    }
};
/* 
给你两个整数，n 和 start 。

数组 nums 定义为：nums[i] = start + 2*i（下标从 0 开始）且 n == nums.length 。

请返回 nums 中所有元素按位异或（XOR）后得到的结果。
1486
 */
class Solution {
public:
    int xorOperation(int n, int start) {
        int res=start;
        for(int i=1;i<n;i++){
            res^=(start+2*i);
        }
        return res;
    }
};