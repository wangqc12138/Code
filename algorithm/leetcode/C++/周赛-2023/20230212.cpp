#include "head.h"
/*
给你一个下标从 0 开始的整数数组 nums 。

现定义两个数字的 串联 是由这两个数值串联起来形成的新数字。

    例如，15 和 49 的串联是 1549 。

nums 的 串联值 最初等于 0 。执行下述操作直到 nums 变为空：

    如果 nums 中存在不止一个数字，分别选中 nums
中的第一个元素和最后一个元素，将二者串联得到的值加到 nums 的 串联值 上，然后从
nums 中删除第一个和最后一个元素。 如果仅存在一个元素，则将该元素的值加到 nums
的串联值上，然后删除这个元素。

返回执行完所有操作后 nums 的串联值。

 */
class Solution {
public:
    long long findTheArrayConcVal(vector<int>& nums) {
        int n = nums.size();
        long long res = 0;
        for (int i = 0; i < n / 2; i++) {
            string temp = to_string(nums[i]) + to_string(nums[n - 1 - i]);
            res += stoll(temp);
        }
        if (n % 2) {
            res += nums[n / 2];
        }
        return res;
    }
};
/*
给你一个下标从 0 开始、长度为 n 的整数数组 nums ，和两个整数 lower 和 upper
，返回 公平数对的数目 。

如果 (i, j) 数对满足以下情况，则认为它是一个 公平数对 ：

    0 <= i < j < n，且
    lower <= nums[i] + nums[j] <= upper
 */
class Solution {
public:
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        sort(nums.begin(), nums.end());
        long long res = 0;
        for (int i : nums) {
            int k = upper_bound(nums.begin(), nums.end(), i) -
                    lower_bound(nums.begin(), nums.end(), i);
            if (i * 2 >= lower && i * 2 <= upper) {
                k--;
            }
            res += k;
        }
        return res / 2;
    }
};

/*
给你一个 二进制字符串 s 和一个整数数组 queries ，其中 queries[i] = [firsti,
secondi] 。

对于第 i 个查询，找到 s 的 最短子字符串 ，它对应的 十进制值 val 与 firsti
按位异或 得到 secondi ，换言之，val ^ firsti == secondi 。

第 i 个查询的答案是子字符串 [lefti, righti] 的两个端点（下标从 0
开始），如果不存在这样的子字符串，则答案为 [-1, -1] 。如果有多个答案，请你选择
lefti 最小的一个。

请你返回一个数组 ans ，其中 ans[i] = [lefti, righti] 是第 i 个查询的答案。

子字符串 是一个字符串中一段连续非空的字符序列。
 */
class Solution {
public:
    vector<vector<int>> substringXorQueries(string s, vector<vector<int>>& queries) {
        vector<vector<int>> res;
        int n = s.size();
        map<int, vector<int>> mp;
        for (int i = 0; i < n; i++) {
            int t = 0;
            for (int j = i; j <= i + 30 && j < n && t <= 1e9; j++) {
                t += s[j] - '0';
                if (!mp.count(t) || mp[t][1] - mp[t][0] > j - i) {
                    mp[t] = {i, j};
                }
                t *= 2;
            }
        }
        for (auto vec : queries) {
            int t = vec[0] ^ vec[1];
            if (mp.count(t)) {
                res.push_back(mp[t]);
            } else {
                res.push_back({-1, -1});
            }
            /* string temp="";
            if(t==0){
                temp="0";
            }
            while(t){
                temp+=to_string(t%2);
                t/=2;
            }
            reverse(temp.begin(),temp.end());
            int l=s.find(temp);
            if(l==string::npos){
                res.push_back({-1,-1});
            }
            int r=l+temp.size();
            res.push_back({l,r}); */
        }
        return res;
    }
};
/*
给你两个字符串 s 和 t 。

你可以从字符串 t 中删除任意数目的字符。

如果没有从字符串 t 中删除字符，那么得分为 0 ，否则：

    令 left 为删除字符中的最小下标。
    令 right 为删除字符中的最大下标。

字符串的得分为 right - left + 1 。

请你返回使 t 成为 s 子序列的最小得分。

一个字符串的 子序列
是从原字符串中删除一些字符后（也可以一个也不删除），剩余字符不改变顺序得到的字符串。（比方说
"ace" 是 "abcde" 的子序列，但是 "aec" 不是）。

 */
class Solution {
public:
    int minimumScore(string s, string t) {
        int m = s.size(), n = t.size(), index = 0, k = -1, p = -1;
        vector<int> v1,v2;
        for(int i=0,j=0;i<n;i++){
            while(j<m){
                if(t[i]==s[j]){
                    v1.emplace_back(j++);
                    break;
                }
                j++;
            }
        }
        if(v1.size()==n){
            return 0;
        }
        for(int i=n-1,j=m-1;i>=0;i--){
            while(j>=0){
                if(t[i]==s[j]){
                    v2.emplace_back(j--);
                    break;
                }
                j--;
            }
        }
        if(v2.size()==n){
            return 0;
        }
        int len=0;
        for(int i=v2.size()-1;i>=0;i--){
            int k=lower_bound(v1.begin(),v1.end(),v2[i])-v1.begin()+i;
            len=max(len,k);
            if(len==k){
                return 0;
            }
        }
        return n-len;
    }
};