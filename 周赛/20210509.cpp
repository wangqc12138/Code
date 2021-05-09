#include"head.h"
/* 
给你一个二维整数数组 logs ，其中每个 logs[i] = [birthi, deathi] 表示第 i 个人的出生和死亡年份。

年份 x 的 人口 定义为这一年期间活着的人的数目。第 i 个人被计入年份 x 的人口需要满足：x 在闭区间 [birthi, deathi - 1] 内。注意，人不应当计入他们死亡当年的人口中。

返回 人口最多 且 最早 的年份。
1 <= logs.length <= 100
1950 <= birthi < deathi <= 2050
 */
class Solution {
public:
    int maximumPopulation(vector<vector<int>>& logs) {
        map<int,int> m;
        for(auto h:logs){
            for(int i=h[0];i<h[1];i++){
                m[i]++;
            }
        }
        int res=0,maxh=0;
        //vscode报错，故注释
        /* for(auto[x,y]:m){
            if(y>maxh){
                maxh=y;
                res=x;
            }
        } */
        return res;
    }
};
/* 
给你两个 非递增 的整数数组 nums1​​​​​​ 和 nums2​​​​​​ ，数组下标均 从 0 开始 计数。
下标对 (i, j) 中 0 <= i < nums1.length 且 0 <= j < nums2.length 。如果该下标对同时满足 i <= j 且 nums1[i] <= nums2[j] ，则称之为 有效 下标对，该下标对的 距离 为 j - i​​ 。​​
返回所有 有效 下标对 (i, j) 中的 最大距离 。如果不存在有效下标对，返回 0 。
一个数组 arr ，如果每个 1 <= i < arr.length 均有 arr[i-1] >= arr[i] 成立，那么该数组是一个 非递增 数组。
1 <= nums1.length <= 105
1 <= nums2.length <= 105
1 <= nums1[i], nums2[j] <= 105
nums1 和 nums2 都是 非递增 数组
 */
class Solution {
public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        int res=0;
        for(int i=0;i<nums1.size();i++){
            int left=i,right=nums2.size()-1;
            while(left<right){
                int mid=left+(right-left)/2+1;
                int n=nums2[mid];
                if(n>=nums1[i]){
                    left=mid;
                }else{
                    right=mid-1;
                }
            }
            res=max(res,left-i);
        }
        return res;
    }
};
/* 
一个数组的 最小乘积 定义为这个数组中 最小值 乘以 数组的 和 。

比方说，数组 [3,2,5] （最小值是 2）的最小乘积为 2 * (3+2+5) = 2 * 10 = 20 。
给你一个正整数数组 nums ，请你返回 nums 任意 非空子数组 的最小乘积 的 最大值 。由于答案可能很大，请你返回答案对  109 + 7 取余 的结果。

请注意，最小乘积的最大值考虑的是取余操作 之前 的结果。题目保证最小乘积的最大值在 不取余 的情况下可以用 64 位有符号整数 保存。

子数组 定义为一个数组的 连续 部分。
1 <= nums.length <= 105
1 <= nums[i] <= 107
 */
class Solution {
public:
    int maxSumMinProduct(vector<int>& nums) {
        int n=nums.size();
        vector<int> sum(n);
        long long t=0;
        long long res=0;
        for(auto i:nums){
            t+=i;
            printf("t %lld\n",t);
            sum.push_back(t+=i);
        }
        for(int i=0;i<n;i++){
            for(int j=i;j<n;j++){
                if(i==0){
                    t=sum[j];
                }else{
                    t=sum[j]-sum[i-1];
                }
                long long minx=*min_element(nums.begin()+i,nums.begin()+j);
                printf("t %lld,minx %lld,t*minx %lld\n",t,minx,t*minx);
                res=max(t*minx,res);
            }
        }
        return res%1000000007;
    }
};

/* 
给你一个 有向图 ，它含有 n 个节点和 m 条边。节点编号从 0 到 n - 1 。

给你一个字符串 colors ，其中 colors[i] 是小写英文字母，表示图中第 i 个节点的 颜色 （下标从 0 开始）。同时给你一个二维数组 edges ，其中 edges[j] = [aj, bj] 表示从节点 aj 到节点 bj 有一条 有向边 。

图中一条有效 路径 是一个点序列 x1 -> x2 -> x3 -> ... -> xk ，对于所有 1 <= i < k ，从 xi 到 xi+1 在图中有一条有向边。路径的 颜色值 是路径中 出现次数最多 颜色的节点数目。

请你返回给定图中有效路径里面的 最大颜色值 。如果图中含有环，请返回 -1 。
 */