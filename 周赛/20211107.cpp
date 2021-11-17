#include "head.h"
/* 
子字符串 是字符串中的一个连续（非空）的字符序列。

元音子字符串 是 仅 由元音（'a'、'e'、'i'、'o' 和 'u'）组成的一个子字符串，且必须包含 全部五种 元音。

给你一个字符串 word ，统计并返回 word 中 元音子字符串的数目 。
 */
class Solution {
public:
	int countVowelSubstrings(string word) {
		int left=0,right=0,n=word.size();
		set<char> st={'a','e','i','o','u'};
		set<char> win;
		int res=0;
		for(int i=0;i<n;i++){
			for(int j=i;j<n;j++){
				if(st.count(word[j])){
					win.emplace(word[j]);
					if(win.size()==5){
						res++;
					}
				}else{
					win.clear();
					break;
				}
			}
		}
		return res;
    }
};
/* 
给你一个字符串 word ，返回 word 的所有子字符串中 元音的总数 ，元音是指 'a'、'e'、'i'、'o' 和 'u' 。

子字符串 是字符串中一个连续（非空）的字符序列。

注意：由于对 word 长度的限制比较宽松，答案可能超过有符号 32 位整数的范围。计算时需当心。
 */
class Solution {
public:
    long long countVowels(string word) {
		long long res=0;
		int n=word.size();
		set<char> st={'a','e','i','o','u'};
		for(int i=0;i<n;i++){
			if(st.count(word[i])){
				res+=(long long)(i+1)*(n-i);
			}
		}
		return res;
    }
};
/*
给你一个整数 n ，表示有 n 间零售商店。总共有 m 种产品，每种产品的数目用一个下标从 0 开始的整数数组 quantities 表示，
其中 quantities[i] 表示第 i 种商品的数目。

你需要将 所有商品 分配到零售商店，并遵守这些规则：

    一间商店 至多 只能有 一种商品 ，但一间商店拥有的商品数目可以为 任意 件。
    分配后，每间商店都会被分配一定数目的商品（可能为 0 件）。
	用 x 表示所有商店中分配商品数目的最大值，你希望 x 越小越好。
	也就是说，你想 最小化 分配给任意商店商品数目的 最大值 。

请你返回最小的可能的 x 。
 */
class Solution {
public:
    int minimizedMaximum(int n, vector<int>& quantities) {
		int left=1,right=*max_element(quantities.begin(),quantities.end());
		while(left<right){
			int mid=(right-left)/2+left;
			int sum=0;
			for(int i:quantities){
				//向上取整的小技巧
				//也可以是
				sum+=ceil(i/mid);
				//sum+=(i-1)/mid+1;
			}
			if(sum>n){
				left=mid+1;
			}else{
				right=mid;
			}
		}
		return left;
    }
};
/* 
给你一张 无向 图，图中有 n 个节点，节点编号从 0 到 n - 1 （都包括）。
同时给你一个下标从 0 开始的整数数组 values ，其中 values[i] 是第 i 个节点的 价值 。
同时给你一个下标从 0 开始的二维整数数组 edges ，
其中 edges[j] = [uj, vj, timej] 表示节点 uj 和 vj 之间有一条需要 timej 秒才能通过的无向边。最后，给你一个整数 maxTime 。

合法路径 指的是图中任意一条从节点 0 开始，最终回到节点 0 ，且花费的总时间 不超过 maxTime 秒的一条路径。
你可以访问一个节点任意次。一条合法路径的 价值 定义为路径中 不同节点 的价值 之和 （每个节点的价值 至多 算入价值总和中一次）。

请你返回一条合法路径的 最大 价值。

注意：每个节点 至多 有 四条 边与之相连。
10 <= timej, maxTime <= 100
 */
class Solution {
public:
	int res=0,temp=0;
	unordered_map<int,vector<pair<int,int>>> next;
    int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {
		for(auto vec:edges){
			next[vec[0]].emplace_back(vec[1],vec[2]);
			next[vec[1]].emplace_back(vec[0],vec[2]);
		}
        temp=values[0];
		vector<int> visit(values.size(),0);
        visit[0]=1;
		dfs(values,maxTime,0,visit);
		return res;
    }
	void dfs(vector<int>& values, int t, int node, vector<int> &visit){
		if(node==0&&t>=0){
			res=max(temp,res);
		}
        if(t<10){
            return;
        }
		for(auto p:next[node]){
			if(visit[p.first]==0){
				temp+=values[p.first];
				visit[p.first]=1;
				dfs(values,t-p.second,p.first,visit);
				temp-=values[p.first];
				visit[p.first]=0;
			}else{
				dfs(values,t-p.second,p.first,visit);
			}
		}
	}
};
/* 
你正在参与祖玛游戏的一个变种。

在这个祖玛游戏变体中，桌面上有 一排 彩球，每个球的颜色可能是：红色 'R'、黄色 'Y'、蓝色 'B'、绿色 'G' 或白色 'W' 。
你的手中也有一些彩球。

你的目标是 清空 桌面上所有的球。每一回合：

    从你手上的彩球中选出 任意一颗 ，然后将其插入桌面上那一排球中：两球之间或这一排球的任一端。
    接着，如果有出现 三个或者三个以上 且 颜色相同 的球相连的话，就把它们移除掉。
        如果这种移除操作同样导致出现三个或者三个以上且颜色相同的球相连，则可以继续移除这些球，直到不再满足移除条件。
    如果桌面上所有球都被移除，则认为你赢得本场游戏。
    重复这个过程，直到你赢了游戏或者手中没有更多的球。

给你一个字符串 board ，表示桌面上最开始的那排球。另给你一个字符串 hand ，表示手里的彩球。
请你按上述操作步骤移除掉桌上所有球，计算并返回所需的 最少 球数。如果不能移除桌上所有的球，返回 -1 。
488
 */
class Solution {
public:
    int findMinStep(string board, string hand) {

    }
	void dfs(string board,string hand){
		int n=board.size();
		for(int i=0;i<=n;i++){
			for(int j=0;j<hand.size();j++){
				string ts1=board.substr(0,i)+hand[j]+board.substr(i,n-i);
				string ts2=hand;
				ts2.erase(ts2.begin()+j);
				help(ts1);
			}
		}
	}
	void help(string& str){
		char c=' ';
		int sum=0;
		for(int i=0;i<str.size();i++){
			if(c!=str[i]){
				if(sum>=3){

				}
				c=str[i];
				continue;
			}else{
				
			}
		}
	}
};
/* 
给你两个字符串 s 和 goal ，只要我们可以通过交换 s 中的两个字母得到与 goal 相等的结果，就返回 true ；否则返回 false 。

交换字母的定义是：取两个下标 i 和 j （下标从 0 开始）且满足 i != j ，接着交换 s[i] 和 s[j] 处的字符。

    例如，在 "abcd" 中交换下标 0 和下标 2 的元素可以生成 "cbad" 。
859
 */
class Solution {
public:
    bool buddyStrings(string s, string goal) {
		int k=0;
		vector<int> v1(26,0),v2(26,0);
		for(int i=0;i<s.size();i++){
			if(s[i]!=goal[i]){
				if(++k==3){
					return false;
				}
			}
			v1[s[i]-'a']++;
			v2[goal[i]-'a']++;
		}
		bool res=false;
		for(int i=0;i<26;i++){
			if(v1[i]!=v2[i]){
				return false;
			}else if(v1[i]>1){
				res=true;
			}
		}
		return false;
    }
};