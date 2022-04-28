
#include "head.h"
/* 
给出一个字符串 s（仅含有小写英文字母和括号）。
请你按照从括号内到外的顺序，逐层反转每对匹配括号中的字符串，并返回最终的结果。
注意，您的结果中 不应 包含任何括号
1190
 */
class Solution {
public:
    string reverseParentheses(string s) {
		stack<char> sk;
		queue<char> qe;
		for(char c:s){
			if(c!=')'){
				sk.push(c);
			}else{
				while(!sk.empty()&&sk.top()!='('){
					qe.push(sk.top());
					sk.pop();
				}
				if(!sk.empty()&&sk.top()=='('){
					sk.pop();
				}
				while(!qe.empty()){
					sk.push(qe.front());
					qe.pop();
				}
			}
		}
		string res;
		while(!sk.empty()){
			res+=sk.top();
			sk.pop();
		}
		reverse(res.begin(),res.end());
		return res;
    }
};
/* 
给定一个经过编码的字符串，返回它解码后的字符串。

编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。

你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。

此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。
394
 */
class Solution {
public:
    string decodeString(string s) {
		vector<int> nums;
		stack<char> sk;
		int n=0;
		for(int idx=0;idx<s.size();idx++){
			char c=s[idx];
			if(c>='0'&&c<='9'){
				n=10*n+c-'0';
			}else if(c!=']'){
				if(c=='['){
					nums.push_back(n);
					n=0;
				}
				sk.push(c);
			}else{
				string temp;
				while(sk.top()!='['){
					temp+=sk.top();
					sk.pop();
				}
				sk.pop();
				int cnt=nums.back();
				nums.pop_back();
				for(int i=0;i<cnt;i++){
					for(int j=temp.size()-1;j>=0;j--){
						sk.push(temp[j]);
					}
				}
			}
		}
		string res;
		while(!sk.empty()){
			res+=sk.top();
			sk.pop();
		}
		reverse(res.begin(),res.end());
		return res;
    }
};
/* 
将一个给定字符串 s 根据给定的行数 numRows ，以从上往下、从左到右进行 Z 字形排列。
比如输入字符串为 "PAYPALISHIRING" 行数为 3 时，排列如下：
P   A   H   N
A P L S I I G
Y   I   R
之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："PAHNAPLSIIGYIR"。
请你实现这个将字符串进行指定行数变换的函数：
string convert(string s, int numRows);
 */
class Solution {
public:
    string convert(string s, int numRows) {
		if(numRows==1||numRows>s.size()){
			return s;
		}
		int i=0,nr=numRows;
		bool dir=false;
		vector<string> temp(nr);
		for(char c:s){
			temp[i]+=c;
			if(i==0||i==nr-1){
				dir=!dir;
			}
			i+=dir?1:-1;
		}
		string res;
		for(auto str:temp){
			res+=str;
		}
		return res;
    }
};