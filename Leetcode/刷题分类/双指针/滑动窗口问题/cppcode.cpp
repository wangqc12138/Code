#include "head.h"
/*
1、给定两个字符串 s1 和 s2，写一个函数来判断 s2 是否包含 s1 的排列。
换句话说，第一个字符串的排列之一是第二个字符串的子串。
567. 字符串的排列
*/
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
    	int right=0,left=0,k=0;
    	map<char,int> need;
    	map<char,int> window;
    	for(auto c:s1){
    		need[c]++;
    	}
    	while(right<s2.size()){
    		while(right<s2.size()&&k<need.size()){
    			char rc=s2[right];
    			if(need.count(rc)){
    				window[rc]++;
    				if(window[rc]==need[rc]){
    					k++;
    				}
    			}
    			right++;
    		}
    		while(k==need.size()){
    			if(right-left==s1.size()){
    				return true;
    			}
    			char lc=s2[left];
    			if(need.count(lc)){
    				if(window[lc]==need[lc]){
    					k--;
    				}
    				window[lc]--;
    			}
    			left++;
    		}
    	}
    	return false;
    }
};
/*
给你一个仅由大写英文字母组成的字符串，你可以将任意位置上的字符替换成另外的字符，总共可最多替换 k 次。在执行上述操作后，找到包含重复字母的最长子串的长度。
注意：字符串长度 和 k 不会超过 104。
424
*/
/*
给定一个由若干 0 和 1 组成的数组 A，我们最多可以将 K 个值从 0 变成 1 。
返回仅包含 1 的最长（连续）子数组的长度。
1004
*/
/*
给你一个二进制数组 nums ，你需要从中删掉一个元素。
请你在删掉元素的结果数组中，返回最长的且只包含 1 的非空子数组的长度。
如果不存在这样的子数组，请返回 0 。
1493
*/
/*
给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。
3
*/
/*
给定一个含有 n 个正整数的数组和一个正整数 target 。
找出该数组中满足其和 ≥ target 的长度最小的 连续子数组 [numsl, numsl+1, ..., numsr-1, numsr] ，并返回其长度。如果不存在符合条件的子数组，返回 0 。
209
*/
/*
给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。
注意：如果 s 中存在这样的子串，我们保证它是唯一的答案。
76
*/
/*
给定一个字符串 s 和一个非空字符串 p，找到 s 中所有是 p 的字母异位词的子串，返回这些子串的起始索引。

字符串只包含小写英文字母，并且字符串 s 和 p 的长度都不超过 20100。

说明：

    字母异位词指字母相同，但排列不同的字符串。
    不考虑答案输出的顺序。
438
*/
/*
中位数是有序序列最中间的那个数。如果序列的长度是偶数，则没有最中间的数；此时中位数是最中间的两个数的平均数。

例如：

    [2,3,4]，中位数是 3
    [2,3]，中位数是 (2 + 3) / 2 = 2.5

给你一个数组 nums，有一个长度为 k 的窗口从最左端滑动到最右端。窗口中有 k 个数，每次窗口向右移动 1 位。你的任务是找出每次窗口移动后得到的新窗口中元素的中位数，并输出由它们组成的数组。
480
*/
/*
给定 n 个整数，找出平均数最大且长度为 k 的连续子数组，并输出该最大平均数。
643
*/
/*
给你两个长度相同的字符串，s 和 t。
将 s 中的第 i 个字符变到 t 中的第 i 个字符需要 |s[i] - t[i]| 的开销（开销可能为 0），也就是两个字符的 ASCII 码值的差的绝对值。
用于变更字符串的最大预算是 maxCost。在转化字符串时，总开销应当小于等于该预算，这也意味着字符串的转化可能是不完全的。
如果你可以将 s 的子字符串转化为它在 t 中对应的子字符串，则返回可以转化的最大长度。
如果 s 中没有子字符串可以转化成 t 中对应的子字符串，则返回 0。
1208
*/
/*
几张卡牌 排成一行，每张卡牌都有一个对应的点数。点数由整数数组 cardPoints 给出。
每次行动，你可以从行的开头或者末尾拿一张卡牌，最终你必须正好拿 k 张卡牌。
你的点数就是你拿到手中的所有卡牌的点数之和。
给你一个整数数组 cardPoints 和整数 k，请你返回可以获得的最大点数。
1423
*/
/*
今天，书店老板有一家店打算试营业 customers.length 分钟。每分钟都有一些顾客（customers[i]）会进入书店，所有这些顾客都会在那一分钟结束后离开。
在某些时候，书店老板会生气。 如果书店老板在第 i 分钟生气，那么 grumpy[i] = 1，否则 grumpy[i] = 0。 当书店老板生气时，那一分钟的顾客就会不满意，不生气则他们是满意的。
书店老板知道一个秘密技巧，能抑制自己的情绪，可以让自己连续 X 分钟不生气，但却只能使用一次。
请你返回这一天营业下来，最多有多少客户能够感到满意的数量。
1052
*/
/*
给你一个整数数组 nums ，和一个表示限制的整数 limit，请你返回最长连续子数组的长度，该子数组中的任意两个元素之间的绝对差必须小于或者等于 limit 。

如果不存在满足条件的子数组，则返回 0 。
1438
*/
/* 
给定一个字符串 s 和一些 长度相同 的单词 words 。找出 s 中恰好可以由 words 中所有单词串联形成的子串的起始位置。

注意子串要与 words 中的单词完全匹配，中间不能有其他字符 ，但不需要考虑 words 中单词串联的顺序。
30
 */
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
		vector<int> res;
		map<string,int> wm;
		for(auto word:words){
			wm[word]++;
		}
		int len=words[0].size()*words.size();
		int l=words[0].size();
		int left=0;
		while(left+len<s.size()){
			map<string,int> sm=wm;
			int i=left;
			for(;i<left+len;i+=l){
				string str=s.substr(i,l);
				if(!sm.count(str)){
					break;
				}else{
					if(sm[str]==0){
						break;
					}
					sm[str]--;
				}
			}
			if(i==left+len){
				res.emplace_back(left);
			}
			left++;
		}
    }
};
/*
给定一个字符串 s ，找出 至多 包含两个不同字符的最长子串 t ，并返回该子串的长度。
159
 */
class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
		map<char,int> wind;
		int left=0,right=0,n=s.size(),res=0;
		while(right<n){
			while(right<n&&wind.size()<=2){
				if(wind.count(s[right])){
					wind[s[right]]++;
				}else if(wind.size()==2){
					break;
				}else{
					wind[s[right]]++;
				}
				right++;
			}
			res=max(right-left,res);
            //cout<<left<<" "<<right<<endl;
			while(left<right){
				if(--wind[s[left]]==0){
					wind.erase(s[left++]);
					break;
				}
                left++;
			}
		}
        res=max(right-left-1,res);
		return res;
    }
};
/* 
给定一个字符串 s ，找出 至多 包含 k 个不同字符的最长子串 T。
340
 */
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        if(k==0){
            return 0;
        }
		map<char,int> wind;
		int left=0,right=0,n=s.size(),res=0;
		while(right<n){
			while(right<n&&wind.size()<=k){
				if(wind.count(s[right])){
					wind[s[right]]++;
				}else if(wind.size()==k){
					break;
				}else{
					wind[s[right]]++;
				}
				right++;
			}
			res=max(right-left,res);
            //cout<<left<<" "<<right<<endl;
			while(left<right){
				if(--wind[s[left]]==0){
					wind.erase(s[left++]);
					break;
				}
                left++;
			}
		}
        res=max(right-left-1,res);
		return res;
    }
};