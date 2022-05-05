#include "head.h"
class Solution {
public:
    string removeDigit(string number, char digit) {
        string res="";
        for(int i=0;i<number.size();i++){
            if(number[i]==digit){
                string str=number.substr(0,i)+number.substr(i+1);
                if(res==""||res<str){
                    res=str;
                }
            }
        }
        return res;
    }
};
class Solution {
public:
    int minimumCardPickup(vector<int>& cards) {
        map<int,int> win;
        int n=cards.size(),L=0,R=0,res=-1;
        while(R<n){
            while(R<n){
                if(++win[cards[R++]]==2){
                    break;
                }
            }
            while(L<R){
                if(win[cards[L++]]--==2){
                    res=R-L;
                }
            }
        }      
        return res;
    }
};
class Solution {
public:
    int countDistinct(vector<int>& nums, int k, int p) {
        int n=nums.size(),res=0;
        vector<int> sum(n+1,0);
        set<vector<int>> visit;
        for(int i=0;i<n;i++){
            sum[i+1]=nums[i]%p==0+sum[i];
        }
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(sum[j+1]-sum[i]>k){
                    break;
                }
                vector<int> temp(nums.begin()+i,nums.begin()+j);
                if(!visit.count(temp)){
                    res++;
                    visit.emplace(temp);
                }
            }
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