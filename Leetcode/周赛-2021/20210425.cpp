/*
给你一个整数 n（10 进制）和一个基数 k ，请你将 n 从 10 进制表示转换为 k 进制表示，计算并返回转换后各位数字总和 。
转换后，各位数字应当视作是 10 进制数字，且它们的总和也应当按 10 进制表示返回。
除整取余
*/
class Solution {
public:
    int sumBase(int n, int k) {
    	int res=0;
    	while(n){
    		res+=n%k;
    		n=n/k;
    	}
    	return res;
    }
};
/*
元素的 频数 是该元素在一个数组中出现的次数。
给你一个整数数组 nums 和一个整数 k 。在一步操作中，你可以选择 nums 的一个下标，并将该下标对应元素的值增加 1 。
执行最多 k 次操作后，返回数组中最高频元素的 最大可能频数 。
*/
/*
[9930,9923,9983,9997,9934,9952,9945,9914,9985,9982,9970,9932,9985,9902,9975,9990,9922,9990,9994,9937,9996,9964,9943,9963,9911,9925,9935,9945,9933,9916,9930,9938,10000,9916,9911,9959,9957,9907,9913,9916,9993,9930,9975,9924,9988,9923,9910,9925,9977,9981,9927,9930,9927,9925,9923,9904,9928,9928,9986,9903,9985,9954,9938,9911,9952,9974,9926,9920,9972,9983,9973,9917,9995,9973,9977,9947,9936,9975,9954,9932,9964,9972,9935,9946,9966]
3056
*/
/*
解法有问题！
*/
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
    	sort(nums.begin(),nums.end());
    	vector<int> d,vec;
    	for(int i=0;i<nums.size()-1;i++){
    		d.push_back(nums[i+1]-nums[i]);
    	}
    	sort(d.begin(),d.end());
    	int res=1,sum=0;
    	for(int i=0;i<d.size();i++){
    		sum+=(i+1)*d[i];
    		vec.push_back(sum);
    	}
    	for(int i=0;i<vec.size();i++){
    		if(vec[i]>k){
    			return i+1;
    		}
    	}
    	return nums.size();
    }
};

/*
当一个字符串满足如下条件时，我们称它是 美丽的 ：
    所有 5 个英文元音字母（'a' ，'e' ，'i' ，'o' ，'u'）都必须 至少 出现一次。
    这些元音字母的顺序都必须按照 字典序 升序排布（也就是说所有的 'a' 都在 'e' 前面，所有的 'e' 都在 'i' 前面，以此类推）
比方说，字符串 "aeiou" 和 "aaaaaaeiiiioou" 都是 美丽的 ，但是 "uaeio" ，"aeoiu" 和 "aaaeeeooo" 不是美丽的 。
给你一个只包含英文元音字母的字符串 word ，请你返回 word 中 最长美丽子字符串的长度 。如果不存在这样的子字符串，请返回 0 。
子字符串 是字符串中一个连续的字符序列。
*/
class Solution {
public:
    int longestBeautifulSubstring(string word) {
    	int res=0,pre=1;set<char> s;
    	s.insert(word[0]);
    	for(int i=1;i<word.size();i++){
    		int cur=1;
    		if(word[i]>=word[i-1]){
    			s.insert(word[i]);
    			cur+=pre;
    		}else{
    			s.clear();
    			s.insert(word[i]);
    		}
    		if(s.size()==5){
    			res=max(res,cur);
    		}
    		pre=cur;
    	}
    	return res;
    }
};