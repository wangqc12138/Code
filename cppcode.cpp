
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