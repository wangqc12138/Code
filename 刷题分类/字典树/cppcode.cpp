#include "head.h"
/*
Trie（发音类似 "try"）或者说 前缀树 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。这一数据结构有相当多的应用情景，例如自动补完和拼写检查。
请你实现 Trie 类：
    Trie() 初始化前缀树对象。
    void insert(String word) 向前缀树中插入字符串 word 。
    boolean search(String word) 如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回 false 。
    boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true ；否则，返回 false 。
208
*/
/* -----------以前代码--------------- */
class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        next.clear();
        next.resize(26);
		isEnd=false;
    }
    /** Inserts a word into the trie. */
    void insert(string word) {
        Trie* node=this;
        for(char c:word){
            int i=c-'a';
            if(node->next[i]==nullptr){
                node->next[i]=new Trie(); 
            } 
            node=node->next[i];           
        }
        node->isEnd=true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Trie* node=this;
        for(char c:word){
            node=node->next[c-'a'];
            if(node==nullptr){
                return false;
            }
        }
        return node->isEnd;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Trie* node=this;
        for(char c:prefix){
            node=node->next[c-'a'];
            if(node==nullptr){
                return false;
            }
        }
        return true;
    }
private:
    vector<Trie*> next;
    bool isEnd; 
};
/* -----------20220311------------ */
//this指针
class Trie {
public:
    Trie() {
		next.clear();
		next.resize(26);
    }
    
    void insert(string word) {
		Trie* node=this;
		for(auto c:word){
			if(node->next[c-'a']==nullptr){
				node->next[c-'a']=new Trie();
			}
			node=node->next[c-'a'];
		}
		node->isEnd=true;
    }
    
    bool search(string word) {
		Trie* node=this;
		for(auto c:word){
			if(node->next[c-'a']==nullptr){
				return false;
			}
			node=node->next[c-'a'];
		}
		return node->isEnd;
    }
    
    bool startsWith(string prefix) {
		Trie* node=this;
		for(auto c:prefix){
			if(node->next[c-'a']==nullptr){
				return false;
			}
			node=node->next[c-'a'];
		}
		return true;
    }
private:
	vector<Trie*> next;
	bool isEnd=false;
};
/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
/* 
给你一个整数数组 nums ，返回 nums[i] XOR nums[j] 的最大运算结果，其中 0 ≤ i ≤ j < n 。
进阶：你可以在 O(n) 的时间解决这个问题吗？
421
字典树--0、1
*/
class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
		int res=0;
		Trie* root=new Trie();
		for(int i:nums){
			root->add(i);
			int m=root->getMaxXor(i);
			res=max(res,m);
		}
		return res;
    }

};
class Trie{
public:
	Trie(){
		next.clear();
		next.resize(2);
		isEnd=false;
	}
	void add(int n){
		Trie *root=this;
		for(int i=31;i>=0;i--){
			int k=(n>>i)&1;//获取最低位
			if(root->next[k]==nullptr){
				Trie* node=new Trie;
				root->next[k]=node;
			}
			root=root->next[k];
		}
		root->isEnd=true;
	}
	int getMaxXor(int n){
		Trie *root=this;
		int res=0;
		for(int i=31;i>=0;i--){
			int k=(n>>i)&1;
			if(k==0){
				if(root->next[1]!=nullptr){
					root=root->next[1];
					res+=(1<<i);
				}else{
					root=root->next[0];
				}
			}else{
				if(root->next[0]!=nullptr){
					root=root->next[0];
					res+=(1<<i);
				}else{
					root=root->next[1];
				}
			}
		}
		return res;
	}
private:
	vector<Trie*> next;
	bool isEnd;
};
/* 
给你一个由非负整数组成的数组 nums 。另有一个查询数组 queries ，其中 queries[i] = [xi, mi] 。

第 i 个查询的答案是 xi 和任何 nums 数组中不超过 mi 的元素按位异或（XOR）得到的最大值。
换句话说，答案是 max(nums[j] XOR xi) ，其中所有 j 均满足 nums[j] <= mi 。如果 nums 中的所有元素都大于 mi，最终答案就是 -1 。

返回一个整数数组 answer 作为查询的答案，其中 answer.length == queries.length 且 answer[i] 是第 i 个查询的答案。
1707
 */
class Trie{
public:
	Trie(){
		next.clear();
		next.resize(2);
	}
	void add(int n){
		Trie* root=this;
		for(int i=31;i>=0;i--){
			int k=(n>>i)&1;
			if(root->next[k]==nullptr){
				root->next[k]=new Trie();
			}
			root=root->next[k];
		}
	}
	int getMaxXor(int n){
		Trie* root=this;
		if(!root->next[0]&&!root->next[1]){
			return -1;
		}
		int res=0;
		for(int i=31;i>=0;i--){
			int k=(n>>i)&1;
			if(k==0){
				if(root->next[1]!=nullptr){
					root=root->next[1];
					res+=(1<<i);
				}else{
					root=root->next[0];
				}
			}else{
				if(root->next[0]!=nullptr){
					root=root->next[0];
					res+=(1<<i);
				}else{
					root=root->next[1];
				}
			}
		}
		return res;
	}
private:
	vector<Trie*> next;
};
class Solution {
public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
		int i=0;
		for(auto &q:queries){
			q.push_back(i++);
		}
		sort(nums.begin(),nums.end());
		sort(queries.begin(),queries.end(),[](auto &x,auto &y){return x[1]<y[1];});
		vector<int> res(queries.size());
		Trie* root=new Trie();
		i=0;
		for(auto vec:queries){
			int xi=vec[0],mi=vec[1],j=vec[2];
			for(;i<nums.size()&&nums[i]<=mi;i++){
				root->add(nums[i]);
			}
			res[j]=root->getMaxXor(xi);
		}
		return res;
    }
};
/* 
设计一个 map ，满足以下几点:

    字符串表示键，整数表示值
    返回具有前缀等于给定字符串的键的值的总和

实现一个 MapSum 类：

    MapSum() 初始化 MapSum 对象
    void insert(String key, int val) 插入 key-val 键值对，字符串表示键 key ，整数表示值 val 。
	如果键 key 已经存在，那么原来的键值对 key-value 将被替代成新的键值对。
    int sum(string prefix) 返回所有以该前缀 prefix 开头的键 key 的值的总和。
	key 和 prefix 仅由小写英文字母组成
677
 */
class MapSum {
public:
    MapSum():tree(26),v(0),s(0){}
    
    void insert(string key, int val) {
		MapSum* node=this;
		for(auto c:key){
			if(node->tree[c-'a']==nullptr){
				node->tree[c-'a']=new MapSum();
			}
			node=node->tree[c-'a'];
            node->s+=val;
        }
		if(node->v!=0){
			MapSum* temp=this;
			for(auto c:key){
				temp=temp->tree[c-'a'];
                temp->s-=node->v;
			}
		}
		node->v=val;
    }
    
    int sum(string prefix) {
		MapSum* node=this;
		for(auto c:prefix){
			if(node->tree[c-'a']==nullptr){
				return 0;
			}
			node=node->tree[c-'a'];
		}
		return node->s;
    }
private:
	vector<MapSum*> tree;
	int v,s;
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */
/* 
在英语中，我们有一个叫做 词根(root) 的概念，可以词根后面添加其他一些词组成另一个较长的单词——我们称这个词为 继承词(successor)。
例如，词根an，跟随着单词 other(其他)，可以形成新的单词 another(另一个)。

现在，给定一个由许多词根组成的词典 dictionary 和一个用空格分隔单词形成的句子 sentence。
你需要将句子中的所有继承词用词根替换掉。如果继承词有许多可以形成它的词根，则用最短的词根替换它。

你需要输出替换之后的句子。
648
1 <= dictionary.length <= 1000
1 <= dictionary[i].length <= 100
dictionary[i] 仅由小写字母组成。
1 <= sentence.length <= 10^6
sentence 仅由小写字母和空格组成。
sentence 中单词的总量在范围 [1, 1000] 内。
sentence 中每个单词的长度在范围 [1, 1000] 内。
sentence 中单词之间由一个空格隔开。
sentence 没有前导或尾随空格。
 */
class trie{
public:
	trie(){
		next.resize(26);
		isEnd=false;
	}
	void add(const string& str){
		trie* node=this;
		for(auto c:str){
			if(node->next[c-'a']==nullptr){
				node->next[c-'a']=new trie();
			}
			node=node->next[c-'a'];
		}
		node->isEnd=true;
	}
	string find(const string& str){
		trie* node=this;
		string res="";
		for(auto c:str){
			if(node->next[c-'a']==nullptr){
				break;
			}
			node=node->next[c-'a'];
			res+=c;
			if(node->isEnd==true){
				return res;
			}
		}
		return "";
	}
private:
	vector<trie*> next;
	bool isEnd;
};
class Solution {
public:
	int splite(string str,string x,vector<string> &vstr){
		int index=0,n=str.size();
		while(int k=str.find(x,index)!=string::npos){
			vstr.emplace_back(str.substr(index,k-index+x.size()));
			index=k+x.size();
		}
		return vstr.size();
	}
	void splite(string& data,vector<string>& vec){
		int i=0;
		while(i<data.size()){
			int n=data.find(' ',i);
			vec.emplace_back(data.substr(i,n-i));
			i=n+1;
		}
	}
    string replaceWords(vector<string>& dictionary, string sentence) {
		vector<string> vstr;
		splite(sentence,vstr);
		trie Trie;
		for(auto str:dictionary){s
			Trie.add(str);
		}
		string res="";
		for(auto str:vstr){
			string s=Trie.find(str);
			if(s!=""){
				res+=s+" ";
			}else{
				res+=str+" ";
			}
		}
		res.pop_back();
		return res;
    }
};