
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
/* 
请你来实现一个 myAtoi(string s) 函数，使其能将字符串转换成一个 32 位有符号整数（类似 C/C++ 中的 atoi 函数）。

函数 myAtoi(string s) 的算法如下：

    读入字符串并丢弃无用的前导空格
    检查下一个字符（假设还未到字符末尾）为正还是负号，读取该字符（如果有）。 确定最终结果是负数还是正数。 如果两者都不存在，则假定结果为正。
    读入下一个字符，直到到达下一个非数字字符或到达输入的结尾。字符串的其余部分将被忽略。
    将前面步骤读入的这些数字转换为整数（即，"123" -> 123， "0032" -> 32）。如果没有读入数字，则整数为 0 。必要时更改符号（从步骤 2 开始）。
    如果整数数超过 32 位有符号整数范围 [−231,  231 − 1] ，需要截断这个整数，使其保持在这个范围内。具体来说，小于 −231 的整数应该被固定为 −231 ，大于 231 − 1 的整数应该被固定为 231 − 1 。
    返回整数作为最终结果。

注意：

    本题中的空白字符只包括空格字符 ' ' 。
    除前导空格或数字后的其余字符串外，请勿忽略 任何其他字符。
8
 */
class Solution {
public:
    int myAtoi(string s) {
        int begin=-1;
        for(int i=0;i<s.size();i++){
            if(s[i]!=' '){
                begin=i;
                break;
            }
        }
        // if(begin==-1)return 0;
        s=s.substr(begin);
        bool flag=false;
        if(s[0]=='-'||s[0]=='+'){
            flag=s[0]=='-';
            s=s.substr(1);
        }
        for(int i=0;i<s.size();i++){
            if(s[i]<='0'||s[i]>='9'){
                s=s.substr(0,i);
                break;
            }
        }
        int res=0;
        for(auto c:s){
            long long t=res;
            t*=10;
            t+=c-'0';
            if(flag&&t>pow(2,31)){
                res=-res;
                break;
            }
            if(t>pow(2,31)-1){
                break;
            }
            res=t;
        }
        return res;
    }
};