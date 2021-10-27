#include "head.h"
/* 
句子仅由小写字母（'a' 到 'z'）、数字（'0' 到 '9'）、连字符（'-'）、标点符号（'!'、'.' 和 ','）以及空格（' '）组成。
每个句子可以根据空格分解成 一个或者多个 token ，这些 token 之间由一个或者多个空格 ' ' 分隔。

如果一个 token 同时满足下述条件，则认为这个 token 是一个有效单词：

    仅由小写字母、连字符和/或标点（不含数字）。
    至多一个 连字符 '-' 。如果存在，连字符两侧应当都存在小写字母（"a-b" 是一个有效单词，但 "-ab" 和 "ab-" 不是有效单词）。
    至多一个 标点符号。如果存在，标点符号应当位于 token 的 末尾 。

这里给出几个有效单词的例子："a-b."、"afad"、"ba-c"、"a!" 和 "!" 。

给你一个字符串 sentence ，请你找出并返回 sentence 中 有效单词的数目 。
sentence 由小写英文字母、数字（0-9）、以及字符（' '、'-'、'!'、'.' 和 ','）组成
 */
/* class Solution {
public:
    int countValidWords(string sentence) {
        int res=0,n=sentence.size();
		bool flag=true;
		for(int i=0;i<n;i++){
			char c=sentence[i];
			if(c==' '){
				if(flag){
					res++;
				}
				flag=true;
			}
			if(!flag){
				continue;
			}
			if(c>='0'||c<='9'){
				flag=false;
			}
			if(c=='-'){
				if(i==0||i==n-1){
					flag=false;
				}else if((sentence[i-1]<'a'&&sentence[i-1]>'z')||(sentence[i+1]<'a'&&sentence[i+1]>'z')){
					flag=false;
				}
			}
			if(c==','||c=='.'||c=='!'){
				if(i!=n-1&&sentence[i+1]!=' '){
					flag=false;
				}
			}
		}
		if(flag){
			res++;
		}
		return res;
    }
}; */
/* 
如果整数  x 满足：对于每个数位 d ，这个数位 恰好 在 x 中出现 d 次。那么整数 x 就是一个 数值平衡数 。

给你一个整数 n ，请你返回 严格大于 n 的 最小数值平衡数 。
 */
class Solution {
public:
    int nextBeautifulNumber(int n) {	
		while(++n){
			int k=n;
			bool flag=true;
			//需要数组，map会超时
			map<int,int> mmp;
			while(k){
				mmp[k%10]++;
				k/=10;
			}
			for(auto [i,j]:mmp){
				if(i!=j){
					flag=false;
					break;
				}
			}
			if(flag){
				return n;
			}
		}
		return 0;
    }
};
/* 
给你一棵根节点为 0 的 二叉树 ，它总共有 n 个节点，节点编号为 0 到 n - 1 。
同时给你一个下标从 0 开始的整数数组 parents 表示这棵树，其中 parents[i] 是节点 i 的父节点。由于节点 0 是根，所以 parents[0] == -1 。

一个子树的 大小 为这个子树内节点的数目。每个节点都有一个与之关联的 分数 。
求出某个节点分数的方法是，将这个节点和与它相连的边全部 删除 ，剩余部分是若干个 非空 子树，这个节点的 分数 为所有这些子树 大小的乘积 。

请你返回有 最高得分 节点的 数目 。
 */
class treenode{
public:
	int val;
	vector<treenode*> chi;
	treenode(int val):val(val){};
};
class Solution {
public:
	long long n,maxn,res=0;
    int countHighestScoreNodes(vector<int>& parents) {
		n=parents.size();
		vector<vector<int>> child(n);
		for(int i=1;i<n;i++){
			child[parents[i]].emplace_back(i);
		}
		treenode* root=buildtree(child,0);
		maxn=n-1;
		dfs(root);
		
		return res;
    }
	treenode* buildtree(vector<vector<int>> &child,int index){
		treenode* root=new treenode(index);
		for(auto i:child[index]){
			root->chi.emplace_back(buildtree(child,i));
		}
        return root;
	}
	int dfs(treenode* root){
		if(root==nullptr){
			return 0;
		}
		long long sum=1,cnt=1;
		for(auto i:root->chi){
			int k=dfs(i);
			cnt*=k;
			sum+=k;
		}
		if(n>sum){
			cnt*=(n-sum);
		}
		if(cnt>maxn){
			maxn=cnt;
			res=1;
		}else if(cnt==maxn){
			res++;
		}
		return sum;
	}
};
/* 
给你一个整数 n ，表示有 n 节课，课程编号从 1 到 n 。同时给你一个二维整数数组 relations ，其中 relations[j] = [prevCoursej, nextCoursej] ，表示课程 prevCoursej 必须在课程 nextCoursej 之前 完成（先修课的关系）。同时给你一个下标从 0 开始的整数数组 time ，其中 time[i] 表示完成第 (i+1) 门课程需要花费的 月份 数。

请你根据以下规则算出完成所有课程所需要的 最少 月份数：

    如果一门课的所有先修课都已经完成，你可以在 任意 时间开始这门课程。
    你可以 同时 上 任意门课程 。

请你返回完成所有课程所需要的 最少 月份数。

注意：测试数据保证一定可以完成所有课程（也就是先修课的关系构成一个有向无环图）
 */
class Solution {
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
		vector<int> in_d(n+1,0),maxn(n+1,0);
		vector<vector<int>> next(n+1); 
		for(auto vec:relations){
			next[vec[0]].emplace_back(vec[1]);
			in_d[vec[1]]++;
		}
		queue<int> mq;
		for(int i=1;i<=n;i++){
			if(in_d[i]==0){
				mq.emplace(i);
			}
		}
		int res=0;
		while(!mq.empty()){
			int len=mq.size();
			for(int i=0;i<len;i++){
				int f=mq.front();
				mq.pop();
                maxn[f]+=time[f-1];
				for(int i:next[f]){
					maxn[i]=max(maxn[i],maxn[f]);
					if(--in_d[i]==0){
						mq.emplace(i);
					}
				}
			}
		}
		return *max_element(maxn.begin(),maxn.end());
    }
};