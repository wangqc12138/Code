#include "head.h"
class Solution {
public:
    int convertTime(string current, string correct) {
        int n1=0,n2=0;
        string h=current.substr(0,2);
        string m=current.substr(3,2);
        n1=stoi(h)*60+stoi(m);
        h=correct.substr(0,2);
        m=correct.substr(3,2);
        n2=stoi(h)*60+stoi(m);
        int n=n2-n1;
        int res=0;
        while(n){
            if(n>=60){
                n-=60;
            }else if(n>=15){
                n-=15;
            }else if(n>=5){
                n-=5;
            }else{
                n--;
            }
            res++;
        }
        return res;
    }
};
class Solution {
public:
    vector<vector<int>> findWinners(vector<vector<int>>& matches) {
        map<int,int> mp1,mp2;
        for(auto vec:matches){
            mp1[vec[0]]++;
            mp2[vec[1]]++;
        }   
        vector<vector<int>> res(2);   
        for(auto [x,y]:mp1){
            if(!mp2.count(x)){
                res[0].emplace_back(x);
            }
        }
        for(auto [x,y]:mp2){
            if(y==1){
                res[1].emplace_back(x);
            }
        }
        return res;
    }
};
class Solution {
public:
    int maximumCandies(vector<int>& candies, long long k) {
        long long right=accumulate(candies.begin(),candies.end(),0);
        long long left=*min_element(candies.begin(),candies.end());
        if(right<k){
            return 0;
        }
        while(left<right){
            long long mid=left+(right-left)/2;
            vector<int> help=candies;
            long long t;
            for(int i=0;i<help.size();i++){
                if(help[i]>=mid){
                    // help[i]-=mid;
                    // i--;
                    // t++;
                }
            }
            if(t<k){
                right=mid-1;
            }else{
                left=mid;
            }
        }
        return left;
    }
};
class Trie{
public:
	Trie(){
		next.clear();
		isEnd=false;
	}
	void add(string str){
		Trie *root=this;
		for(auto c:str){
            if(root->next[c]==nullptr){
                root->next[c]=new Trie;
            }
            root=root->next[c];
        }
		root->isEnd=true;
	}
	int find(const string& str,map<string,vector<char>> mp){
		Trie* root=this;
        queue<char> mq;
        queue<Trie*> q;
        for(auto c:mp[str.substr(0,2)]){
            mq.emplace(c);
            q.emplace(root);
        }
        int index=2;
		while(!mq.empty()){
            int len=mq.size();
            for(int i=0;i<len;i++){
                auto f=mq.front();
                auto rf=q.front();
                mq.pop();
                q.pop();
                if(rf->next[f]==nullptr){
                    continue;
                }
                q.emplace(rf->next[f]);
                for(auto c:mp[])
            }
            index+=2;
        }
		return root->isEnd;
	}
private:
	map<char,Trie*> next;
	bool isEnd;
};
class Encrypter {
public:
    Encrypter(vector<char>& keys, vector<string>& values, vector<string>& dictionary) {
        for(int i=0;i<keys.size();i++){
            mp1[keys[i]]=values[i];
            mp2[values[i]].emplace_back(keys[i]);
        }
        st=set<string>(dictionary.begin(),dictionary.end());
        for(auto str:dictionary){
            for(int i=0;i<str.size();i++){
                mst[i].emplace(str.substr(0,i+1));
            }
        }
    }
    
    string encrypt(string word1) {
        string res;
        for(auto i:word1){
            if(mp1.count(i)){
                res+=mp1[i];
            }else{
                res+=i;
            }
        }
        return res;
    }
    int res=0;
    string temp;
    int decrypt(string word2) {
        res=0;
        temp="";
        dfs(word2,0);
        return res;
    }
    void dfs(string word2,int index){
        if(index==word2.size()){
            if(st.count(temp)){
               res++; 
            }
            return;
        }
        for(auto c:mp2[word2.substr(index,2)]){
            if(!mst[index/2].count(temp)){
                continue;
            }
            temp+=c;
            dfs(word2,index+2);
            temp.pop_back();
        }
    }
private:
    map<char,string> mp1;
    map<string,vector<char>> mp2;
    set<string> st;
    map<int,set<char>> mst;
};