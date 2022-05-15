#include "head.h"
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
        int getnum(int n){
            Trie* root=this;
            if(!root->next[0]&&!root->next[1]){
                return -1;
            }
            int res=0;
            for(int i=31;i>=0;i--){
                int k=(n>>i)&1;
                if(root->next[k-1]==nullptr){
                    return -1;
                }else{
                    root=root->next[k-1];
                    res+=((k-1)<<i);
                }
            }
            return res;
        }
    private:
        vector<Trie*> next;
    };
class Solution {
public:
    map<int,int> mp;
    class Trie{
    public:
        Trie(){
            next.clear();
            next.resize(2);
        }
        void add(int n){
            Trie* root=this;
            for(int i=31;i>=0;i--){
                int k=(n>>i)&1;c                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
                if(root->next[k]==nullptr){
                    root->next[k]=new Trie();
                }
                root=root->next[k];
            }
        }
        int getnum(int n,map<int,int> &mp){
            Trie* root=this;
            if(!root->next[0]&&!root->next[1]){
                return -1;
            }
            int res=mp[n],t;
            int temp=0;
            for(int i=31;i>=0;i--){
                int k=(n>>i)&1;
                if(root->next[k-1]==nullptr){
                    return -1;
                }else{
                    root=root->next[k-1];
                    temp+=((k-1)<<i);
                    if(mp[temp]<res){
                        t=temp;
                        res=mp[temp];
                    }
                }
            }
            mp[t]=0;
            return res;
        }
    private:
        vector<Trie*> next;
    };
    int largestCombination(vector<int>& candidates) {
        for(int i:candidates){
            mp[i]++;
        }
        int res=candidates.size();
        set<int> st(candidates.begin(),candidates.end());
        candidates=vector<int>(st.begin(),st.end());
        Trie* t;
        for(int i:candidates){
            t->add(i);
        }
        for(int i:candidates){
            int n=t->getnum(i,mp);
            res-=n;
            mp[i]=0,mp[n]=0;
        }
        return res;
    }
};