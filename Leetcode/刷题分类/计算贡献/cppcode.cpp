#include "head.h"
/* 
我们定义了一个函数 countUniqueChars(s) 来统计字符串 s 中的唯一字符，并返回唯一字符的个数。

例如：s = "LEETCODE" ，则其中 "L", "T","C","O","D" 都是唯一字符，因为它们只出现一次，所以 countUniqueChars(s) = 5 。

本题将会给你一个字符串 s ，我们需要返回 countUniqueChars(t) 的总和，其中 t 是 s 的子字符串。
注意，某些子字符串可能是重复的，但你统计时也必须算上这些重复的子字符串（也就是说，你必须统计 s 的所有子字符串中的唯一字符）。

由于答案可能非常大，请将结果 mod 10 ^ 9 + 7 后再返回。
828
 */
//ABBABBABBBBBABBBBBABBBBA
class Solution {
public:
    int uniqueLetterString(string s) {
        int index[26][2];
        memset(index,-1,sizeof(int)*26*2);
        int res=0,n=s.size();
        for(int i=0;i<n;i++){
            int k=s[i]-'A';
            res+=(i-index[k][1])*(index[k][1]-index[k][0]);
            index[k][0]=index[k][1],index[k][1]=i;
        }
        for(auto &[l,r]:index){
            res+=(n-r)*(r-l);
        }
        return res;
    }
};
//第二种写法:
class Solution {
public:
    int uniqueLetterString(string s) {
        int index[26];
        memset(index,-1,sizeof(int)*26);
        int n=s.size(),res=0,sum=0;
        for(int i=0;i<n;i++){
            int k=s[i]-'A';
            sum+=i-index[k];
            if(index[k]!=-1){
                sum-=index[k];
            }
            res+=sum;
            index[k]=i;
        }
        return res;
    }
};
/* 
字符串的 引力 定义为：字符串中 不同 字符的数量。

    例如，"abbca" 的引力为 3 ，因为其中有 3 个不同字符 'a'、'b' 和 'c' 。

给你一个字符串 s ，返回 其所有子字符串的总引力 。

子字符串 定义为：字符串中的一个连续字符序列。
2262
 */
/* 
以s[i]结尾的字符串：出现过，总的引力+上次出现过的位置以后的子串，没出现，总的引力+前面所有位置的子串
子串指代以s[i]结尾的
 */
class Solution {
public:
    long long appealSum(string s) {
        int index[26];
        memset(index,-1,sizeof(int)*26);
        int n=s.size(),sum=0;
        long long res=0;
        for(int i=0;i<n;i++){
            int k=s[i]-'a';
            sum+=(i-index[k]);
            res+=sum;
            index[k]=i;
        }
        return res;
    }
};