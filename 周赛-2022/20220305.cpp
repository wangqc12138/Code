#include "head.h"
class Solution {
public:
    vector<int> sortJumbled(vector<int>& mapping, vector<int>& nums) {
        vector<pair<int,int>> vpii;
        map<int,vector<int>> mp;
        for(auto i:nums){
            string str=to_string(i);
            string temp="";
            for(auto c:str){
                temp+=mapping[c-'0']+'0';
            }
           vpii.emplace_back(stoi(temp),i); 
           mp[stoi(temp)].emplace_back(i);
        }
        sort(vpii.begin(),vpii.end());
        vector<int> res;
        for(auto [x,y]:mp){
            for(auto i:y){
                res.emplace_back(y);
            }
        }
        return res;
    }
};
/* 

给你一个正整数 n ，它表示一个 有向无环图 中节点的数目，节点编号为 0 到 n - 1 （包括两者）。

给你一个二维整数数组 edges ，其中 edges[i] = [fromi, toi] 表示图中一条从 fromi 到 toi 的单向边。

请你返回一个数组 answer，其中 answer[i]是第 i 个节点的所有 祖先 ，这些祖先节点 升序 排序。

如果 u 通过一系列边，能够到达 v ，那么我们称节点 u 是节点 v 的 祖先 节点。
 */
class Solution {
public:
    vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges) {
        vector<set<int>> temp(n);
        map<int,vector<int>> next;
        vector<int> _in(n);
        for(auto vec:edges){
            next[vec[0]].emplace_back(vec[1]);
            _in[vec[1]]++;
        }
        queue<int> mq;
        for(int i=0;i<n;i++){
            if(_in[i]==0){
                mq.emplace(i);
            }
        }
        while(!mq.empty()){
            auto f=mq.front();
            mq.pop();
            for(auto i:next[f]){
                temp[i].emplace(f);
                for(auto j:temp[f]){
                    temp[i].emplace(j);
                }
                if(--_in[i]==0){
                    mq.emplace(i);
                }
            }
        }
        vector<vector<int>> res;
        for(auto i:temp){
            res.emplace_back(i.begin(),i.end());
        }
        return res;
    }
};
string str;
int steps, len, mid = -1, p;

void myswap(int i, int j)
{
	char temp = str[i];
	if (mid != -1)	// 因为跳过了中间位置字母，所以移动位置要对应的往后平移1个位置 
		j++;
	for (int x = i; x < j; x++)
		str[x] = str[x + 1];
	str[j] = temp;
	steps += j - i;
}

int minMovesToMakePalindrome(string s) {
	str = s;
    int len=s.size();

	for (int i = 0; i < len / 2; i++)
	{
		if (mid != -1)
			p = 1;
		if (str[i] == str[len - 1 - i + p])
			continue;
		else
		{
			int flag = 1;	// 假设有字符没找到对应回文 
			for (int j = len - 2 - i + p; j >= i + 1; j--)	// 反向找匹配的字母，以减少步数 
				if (str[j] == str[i])
				{
					myswap(j, len - 1 - i);
					flag = 0;
					break;
				}
			if (flag)
				if (len & 1)	// 若是奇数字符串
				{
					mid = i;	// 记下中间字母的位置，最后来移动 
					continue;
				}
				else	// 偶数字符串且有单个字符，直接打印结果返回
				{
					return 0;
				}
		}
	}
	if (mid != -1)	// 对于奇数字符串，加上最后移动中间字符的步数
		steps += len / 2 - mid;
	return steps;
}
