#include "head.h"
/* 
给你两个字符串数组 words1 和 words2 ，请你返回在两个字符串数组中 都恰好出现一次 的字符串的数目。
 */
class Solution {
public:
    int countWords(vector<string>& words1, vector<string>& words2) {
		map<string,int> m1,m2;
		for(auto str:words1){
			m1[str]++;
		}
		for(auto str:words2){
			m2[str]++;
		}
		int res=0;
		for(auto [x,y]:m1){
			if(m2[x]==1&&y==1){
				res++;
			}
		}
		return res;
    }
};
/* 
给你一个下标从 0 开始的字符串 street 。street 中每个字符要么是表示房屋的 'H' ，要么是表示空位的 '.' 。

你可以在 空位 放置水桶，从相邻的房屋收集雨水。位置在 i - 1 或者 i + 1 的水桶可以收集位置为 i 处房屋的雨水。
一个水桶如果相邻两个位置都有房屋，那么它可以收集 两个 房屋的雨水。

在确保 每个 房屋旁边都 至少 有一个水桶的前提下，请你返回需要的 最少 水桶数。如果无解请返回 -1 。
*/
class Solution {
public:
    int minimumBuckets(string street) {
		int n=street.size(),res=0;
        for(int i=1;i<n-1;i++){
			if(street[i]=='.'){
				if(street[i-1]=='H'&&street[i+1]=='H'){
					res++;
					street[i-1]='#';
					street[i+1]='#';
				}
			}
		}
		for(int i=0;i<n;i++){
			if(street[i]=='H'){
				if(i>0&&street[i-1]=='.'||i<n-1&&street[i+1]=='.'){
					res++;
				}else{
					return -1;
				}
				
			}
		}
		return res;
    }
};
/* 
给你一个 m x n 的网格图，其中 (0, 0) 是最左上角的格子，(m - 1, n - 1) 是最右下角的格子。
给你一个整数数组 startPos ，startPos = [startrow, startcol] 表示 初始 有一个 机器人 在格子 (startrow, startcol) 处。
同时给你一个整数数组 homePos ，homePos = [homerow, homecol] 表示机器人的 家 在格子 (homerow, homecol) 处。

机器人需要回家。每一步它可以往四个方向移动：上，下，左，右，同时机器人不能移出边界。每一步移动都有一定代价。
再给你两个下标从 0 开始的额整数数组：长度为 m 的数组 rowCosts  和长度为 n 的数组 colCosts 。

    如果机器人往 上 或者往 下 移动到第 r 行 的格子，那么代价为 rowCosts[r] 。
    如果机器人往 左 或者往 右 移动到第 c 列 的格子，那么代价为 colCosts[c] 。

请你返回机器人回家需要的 最小总代价 。

 */
using pii=pair<int,int>;
using ppi=pair<pii,int>;
class Solution {
public:
	vector<pii> dir={{0,-1},{0,1},{1,0},{-1,0}};
    int minCost(vector<int>& startPos, vector<int>& homePos, vector<int>& rowCosts, vector<int>& colCosts) {
		int m=rowCosts.size(),n=colCosts.size();
		auto cmp=[&](ppi a,ppi b){
			return a.second>b.second;
		};
		priority_queue<ppi,vector<ppi>,decltype(cmp)> mpq(cmp);
		set<pii> visit;
		mpq.emplace(pii(startPos[0],startPos[1]),0);
		while(!mpq.empty()){
			ppi t=mpq.top();
			pii d=t.first;
			visit.emplace(d);
			mpq.pop();
			if(d.first==homePos[0]&&d.second==homePos[1]){
				return t.second;
			}
			for(auto k:dir){
				int x=k.first+d.first,y=k.second+d.second;
				if(x<0||x>=m||y<0||y>=n||visit.count(pii(x,y))){
					continue;
				}
				int w=k.first==0?colCosts[y]:rowCosts[x];
				mpq.emplace(pii(x,y),t.second+w);
			}
		}
		return -1;
    }
};