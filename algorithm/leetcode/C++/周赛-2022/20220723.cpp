#include "head.h"
class NumberContainers {
public:
    NumberContainers() {
        mp.clear();
        mp1.clear();
    }
    
    void change(int index, int number) {
        mp[number].emplace(index);
        if(mp1.count(index)&&mp1[index]!=number){
            int y=mp1[index];
            mp[y].erase(index);
            if(mp[y].empty()){
                mp.erase(y);
            }
        }
        mp1[index]=number;
    }
    
    int find(int number) {
        if(!mp.count(number)){
            return -1;
        }
        return *mp[number].begin();
    }
    map<int,set<int>> mp;
    map<int,int> mp1;
};
class Solution {
public:
    int shortestSequence(vector<int>& rolls, int k) {
        int n=rolls.size();
        if(k>n){
            return 1;
        }
        set<int> s(rolls.begin(),rolls.end());
        if(s.size()<k){
            return 1;
        }
        
    }
};