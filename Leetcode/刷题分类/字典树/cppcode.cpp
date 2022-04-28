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
#ifdef 421
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
//20220427
class trie{
public:
	trie():one(nullptr),zero(nullptr){};
	void add(int n){
		trie* root=this;
		for(int i=31;i>=0;i--){
			int k=(n>>i)&1;
			if(k){
				if(!root->one){
					root->one=new trie();
				}
				root=root->one;
			}else{
				if(!root->zero){
					root->zero=new trie();
				}
				root=root->zero;
			}
		}
	}
	int find(int n){
		trie* root=this;
		int res=0;
		for(int i=31;i>=0;i--){
			int k=(n>>i)&1;
			if(k){
				if(root->zero){
					res+=1<<i;
					root=root->zero;
				}else{
					res+=0<<i;
					root=root->one;
				}
			}else{
				if(root->one){
					res+=1<<i;
					root=root->one;
				}else{
					res+=0<<i;
					root=root->zero;
				}
			}
		}
		return res;
	}
private:
	trie *one,*zero;
};
class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
		trie* root=new trie();
		int res=0;
		for(auto i:nums){
			//root->add(i);
			//res=max(res,root->find(i));
		}
        return res;
    }	
};
#endif
/* 
给你一个由非负整数组成的数组 nums 。另有一个查询数组 queries ，其中 queries[i] = [xi, mi] 。

第 i 个查询的答案是 xi 和任何 nums 数组中不超过 mi 的元素按位异或（XOR）得到的最大值。
换句话说，答案是 max(nums[j] XOR xi) ，其中所有 j 均满足 nums[j] <= mi 。如果 nums 中的所有元素都大于 mi，最终答案就是 -1 。

返回一个整数数组 answer 作为查询的答案，其中 answer.length == queries.length 且 answer[i] 是第 i 个查询的答案。
1707
 */
#ifdef 1707
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
#endif
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
#ifdef 648
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
		for(auto str:dictionary){
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
#endif
/* 
请你设计一个数据结构，支持 添加新单词 和 查找字符串是否与任何先前添加的字符串匹配 。

实现词典类 WordDictionary ：

    WordDictionary() 初始化词典对象
    void addWord(word) 将 word 添加到数据结构中，之后可以对它进行匹配
    bool search(word) 如果数据结构中存在字符串与 word 匹配，则返回 true ；否则，返回  false 。
	word 中可能包含一些 '.' ，每个 . 都可以表示任何一个字母。

1 <= word.length <= 25
addWord 中的 word 由小写英文字母组成
search 中的 word 由 '.' 或小写英文字母组成
最多调用 104 次 addWord 和 search

211
 */
#ifdef 211
class trie{
public:
	trie(){
		next=vector<trie*>(26);
		isEnd=false;
	}
	void add(string str){
		trie* root=this;
		for(auto c:str){
			if(!root->next[c-'a']){
				root->next[c-'a']=new trie();
			}
			root=root->next[c-'a'];
		}
		root->isEnd=true;
	}
	bool search(string str,trie* root){
        //cout<<str<<endl;
		for(int i=0;i<str.size();i++){
			char c=str[i];
			if(c=='.'){
				for(char j='a';j<='z';j++){
                    if(!root->next[j-'a']){
                        continue;
                    }
					if(search(str.substr(i+1),root->next[j-'a'])){
						return true;
					}
				}
				return false;
			}else{
				if(!root->next[c-'a']){
					return false;
				}else{
					root=root->next[c-'a'];
				}
			}
		}
		return root->isEnd;
	}
private:
	vector<trie*> next;
	bool isEnd;
};
class WordDictionary {
public:
    WordDictionary() {
        root=new trie();
    }
    
    void addWord(string word) {
		root->add(word);
    }
    
    bool search(string word) {
		//return root->search(word,root);
    }
private:
	trie* root;
};
#endif
/* 
为搜索引擎设计一个搜索自动补全系统。用户会输入一条语句（最少包含一个字母，以特殊字符 '#' 结尾）。

给定一个字符串数组 sentences 和一个整数数组 times ，长度都为 n ，其中 sentences[i] 是之前输入的句子， times[i] 是该句子输入的相应次数。
对于除 ‘#’ 以外的每个输入字符，返回前 3 个历史热门句子，这些句子的前缀与已经输入的句子的部分相同。

下面是详细规则：

    一条句子的热度定义为历史上用户输入这个句子的总次数。
    返回前 3 的句子需要按照热度从高到低排序（第一个是最热门的）。如果有多条热度相同的句子，请按照 ASCII 码的顺序输出（ASCII 码越小排名越前）。
    如果满足条件的句子个数少于 3 ，将它们全部输出。
    如果输入了特殊字符，意味着句子结束了，请返回一个空集合。

实现 AutocompleteSystem 类：

    AutocompleteSystem(String[] sentences, int[] times): 使用数组sentences 和 times 对对象进行初始化。
    List<String> input(char c) 表示用户输入了字符 c 。
        如果 c == '#' ，则返回空数组 [] ，并将输入的语句存储在系统中。
        返回前 3 个历史热门句子，这些句子的前缀与已经输入的句子的部分相同。如果少于 3 个匹配项，则全部返回。
642
 */
class trie{
public:
	trie(){
		next.clear();
		isEnd=0;
	}
	void add(string s);
	void add(string s,int k){
		trie* root=this;
		for(auto c:s){
			if(!root->next.count(c)){
				root->next[c]=new trie();
			}
			root->nums[c][k]++;
			root=root->next[c];
		}
		root->isEnd=k;
	}
	string find(string s);
	trie* search(string s){
		trie* root=this;
		for(auto c:s){
			if(root->next.count(c)){
				root=root->next[c];
			}else{
				return nullptr;
			}
		}
		return root;
	}
	vector<string> getHotStr(string pre){
		trie* root=search(pre);
		if(root==nullptr){
			return {};
		}
		auto cmp=[](pair<char,int> a,pair<char,int> b){
			if(a.second>b.second){
				return true;
			}else if(a.second==b.second){
				return a.first<b.first;
			}
			return false;
		};
		vector<pair<char,int>> temp;
		for(auto [x,y]:root->nums){
			for(auto [a,b]:y){
				temp.emplace_back(x,y);
			}
			
		}
		sort(temp.begin(),temp.end(),cmp);

	}
private:
	map<char,trie*> next;
	map<char,map<int,int>> nums;
	int isEnd;
};
class AutocompleteSystem {
public:
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {

    }
    
    vector<string> input(char c) {

    }
};
/* 
给定一个 m x n 二维字符网格 board 和一个单词（字符串）列表 words， 返回所有二维网格上的单词 。

单词必须按照字母顺序，通过 相邻的单元格 内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母在一个单词中不允许被重复使用。
212
 */
//当然能用dfs来做
//这里使用字典树来完成-----word进树
class trie{
public:
	trie(){
		isEnd=false;
		next.resize(26);
	}
	void add(string str){
		trie* root=this;
		for(auto c:str){
			if(!root->next[c-'a']){
				root->next[c-'a']=new trie();
			}
			root=root->next[c-'a'];
		}
		root->isEnd=true;
	}
	bool isEnd;
	vector<trie*> next;
};
class Solution {
public:
	string temp;
	vector<string> res;
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
		int m=board.size(),n=board[0].size();
		trie* root=new trie();
		for(auto str:words){
			root->add(str);
		}
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				dfs(board,i,j,m,n,0,root);
			}
		}
		return res;
    }
	vector<pair<int,int>> dir={{0,1},{0,-1},{1,0},{-1,0}};
	void dfs(vector<vector<char>>& board,int i,int j,int &m,int &n,int len,trie* root){
        char c=board[i][j];
		if(!root->next[c-'a']){
			return;
		}
		root=root->next[c-'a'];
		if(root->isEnd){
			res.emplace_back(temp+c);
			root->isEnd=false;
		}
		board[i][j]='#';
		for(auto [x,y]:dir){
			if(i+x<0||i+x>=m||j+y<0||j+y>=n||board[i+x][j+y]=='#'||len==10){
				continue;
			}
			temp+=c;
			dfs(board,i+x,j+y,m,n,len+1,root);
			temp.pop_back();
		}
        board[i][j]=c;
	}
};
//425前置：422
/* 
给你一个单词序列，判断其是否形成了一个有效的单词方块。

有效的单词方块是指此由单词序列组成的文字方块的 第 k 行 和 第 k 列 (0 ≤ k < max(行数, 列数)) 所显示的字符串完全相同。

注意：

    给定的单词数大于等于 1 且不超过 500。
    单词长度大于等于 1 且不超过 500。
    每个单词只包含小写英文字母 a-z。
考虑不等长
422
*/
class Solution {
public:
    bool validWordSquare(vector<string>& words) {
        int m=words.size(),n=words[0].size();
		for(int i=0;i<words.size();i++){
			for(int j=0;j<words[i].size();j++){
				if(j>=words.size()||i>=words[j].size()||words[i][j]!=words[j][i]){
					return false;
				}
			}
		}
		return true;
    }
};
/* 
给定一个单词集合 words （没有重复），找出并返回其中所有的 单词方块 。 words 中的同一个单词可以被 多次 使用。你可以按 任意顺序 返回答案。

一个单词序列形成了一个有效的 单词方块 的意思是指从第 k 行和第 k 列  0 <= k < max(numRows, numColumns) 来看都是相同的字符串。

    例如，单词序列 ["ball","area","lead","lady"] 形成了一个单词方块，因为每个单词从水平方向看和从竖直方向看都是相同的。
425
 */
//尝试用全排列回溯去做------------TLE
class Solution {
public:
	vector<vector<string>> res;
	vector<string> temp;
    vector<vector<string>> wordSquares(vector<string>& words) {
		vector<int> visit(words.size(),0);
		dfs(words,visit);
		return res;
    }
	void dfs(vector<string>& words,vector<int>& visit){
        print(temp);
		if(temp.size()==words[0].size()){
			if(check(temp)){
				res.emplace_back(temp);
			}
			return;
		}
		for(int i=0;i<words.size();i++){
			if(words[i][0]!=words[i][temp.size()]&&visit[i]){
				continue;
			}
			visit[i]=1;
			temp.emplace_back(words[i]);
			dfs(words,visit);
			visit[i]=0;
			temp.pop_back();
		}
	}
	bool check(vector<string>& words) {
        int m=words.size(),n=words[0].size();
		for(int i=0;i<words.size();i++){
			for(int j=0;j<words[i].size();j++){
				if(j>=words.size()||i>=words[j].size()||words[i][j]!=words[j][i]){
					return false;
				}
			}
		}
		return true;
    }
    void print(vector<string>& words) {
        if(words.size()<=2){
            return;
        }
        for(auto str:words){
            cout<<str<<endl;
        }
        cout<<endl;
    }
};
//----------------------------------------------------------------
class Trie
{
public:
    unordered_map<char, Trie *> child;      //构造时就嵌套，只能用指针
    bool isWord = false;

    Trie() {} 

    void insert(string word)
    {
        Trie * root = this;
        for (char c : word)
        {
            if (root->child[c] == NULL)
                root->child[c] = new Trie();
            root = root->child[c];
        }
        root->isWord = true;
    }

    bool starts_with(string prefix)
    {
        Trie * root = this;
        for (char c : prefix)
        {
            if (root->child[c] == NULL)
                return false;
            root = root->child[c];
        }
        return true;
    }

    bool is_word(string word)
    {
        Trie * root = this;
        for (char c: word)
        {
            if (root->child[c] == NULL)
                return false;
            root = root->child[c];
        }
        return root->isWord == true;
    }

    vector<string> query(string prefix)
    {
        Trie * root = this;
        vector<string> res;
        for (char c: prefix)
        {
            if (root->child[c] == NULL)
                return res;
            root = root->child[c];
        }

        std::function<void(string ,Trie *)> dfs = [&] (string prefix, Trie * root)
        {
            if (root->isWord == true)
                res.push_back(prefix);
            for (auto [c, _] : root->child)
                if (root->child[c] != NULL)
                    dfs(prefix + c, root->child[c]);
        };

        dfs(prefix, root);
        return res;
    } 
};


class Solution 
{
public:
    vector<vector<string>> wordSquares(vector<string>& words) 
    {
        int wordLen = words[0].size();

        //--------------- 先建Trie树
        Trie * T = new Trie();
        for (string word : words)
            T->insert(word);

        vector<vector<string>> res;
        vector<string> path;

        //--------------- 回溯算法
        std::function<void(int)> backtrace = [&] (int idx)
        {
            if (idx == wordLen)
            {
                res.push_back(path);
                return ;
            }
            //----- 新一行的前缀
            string nxt_prefix = "";
            for (int i = 0; i < idx; i ++)
                nxt_prefix += path[i][idx];
            
            vector<string> nxt_words_with_prefix = T->query(nxt_prefix);
            for (string word : nxt_words_with_prefix)
            {
                path.push_back(word);
                backtrace(idx + 1);
                path.pop_back();
            }
        };

        //---------------- 尝试以每个单词为起点，执行回溯算法 
        for (string word: words)
        {
            path.push_back(word);
            backtrace(1);
            path.pop_back();
        }
        
        return res;
    }
};