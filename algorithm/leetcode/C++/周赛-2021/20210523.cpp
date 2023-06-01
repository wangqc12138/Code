#include "head.h"
/* 
给你一个二进制字符串 s 。如果字符串中由 1 组成的 最长 连续子字符串 严格长于 由 0 组成的 最长 连续子字符串，返回 true ；否则，返回 false 。

例如，s = "110100010" 中，由 1 组成的最长连续子字符串的长度是 2 ，由 0 组成的最长连续子字符串的长度是 3 。
注意，如果字符串中不存在 0 ，此时认为由 0 组成的最长连续子字符串的长度是 0 。字符串中不存在 1 的情况也适用此规则。
 */
class Solution {
public:
    bool checkZeroOnes(string s) {
        int len_1=0,len_0=0;
        if(s[0]=='1'){
            len_1++;
        }else{
            len_0++;
        }
        int m_1=0,m_0=0;
        for(int i=1;i<s.size();i++){
            if(s[i]==s[i-1]){
                if(s[i]=='1'){
                    len_1++;
                }else{
                    len_0++;
                }
            }else{
                m_1=max(m_1,len_1);
                m_0=max(len_0,m_0);
            }
        }
        return m_1>m_0;
    }
};
/* 
给你一个浮点数 hour ，表示你到达办公室可用的总通勤时间。要到达办公室，你必须按给定次序乘坐 n 趟列车。另给你一个长度为 n 的整数数组 dist ，其中 dist[i] 表示第 i 趟列车的行驶距离（单位是千米）。

每趟列车均只能在整点发车，所以你可能需要在两趟列车之间等待一段时间。

例如，第 1 趟列车需要 1.5 小时，那你必须再等待 0.5 小时，搭乘在第 2 小时发车的第 2 趟列车。
返回能满足你准时到达办公室所要求全部列车的 最小正整数 时速（单位：千米每小时），如果无法准时到达，则返回 -1 。

生成的测试用例保证答案不超过 107 ，且 hour 的 小数点后最多存在两位数字 。
 */

class Solution {
public:
    int minSpeedOnTime(vector<int>& dist, double hour) {
        int n=dist.size();
        if(hour<n-1){
            return -1;
        }
        int left=0,right=INT_MAX;
        while(left<right){
            int mid=(right-left)/2+left;
            int sh=0;
            for(int i:dist){
                sh+=ceil(i/mid);
            }
            if(sh>hour){
                left=mid+1;
            }else{
                right=mid;
            }
        }
        return left;
    }
};
/* 
给你一个下标从 0 开始的二进制字符串 s 和两个整数 minJump 和 maxJump 。一开始，你在下标 0 处，且该位置的值一定为 '0' 。当同时满足如下条件时，你可以从下标 i 移动到下标 j 处：

i + minJump <= j <= min(i + maxJump, s.length - 1) 且
s[j] == '0'.
如果你可以到达 s 的下标 s.length - 1 处，请你返回 true ，否则返回 false 。
*/
class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n=s.size(),maxlen=0;
        if(s[n-1]=='1'){
            return false;
        }
        vector<bool> dp(n,false);
        dp[0]=true;
        for(int i=0;i<n;i++){
            for(int j=i+minJump;j<i+maxJump&&j<n;j++){
                if(s[j]=='0'){
                    dp[j]=dp[i];
                }
            }
        }
        return dp[n-1];
    }
};