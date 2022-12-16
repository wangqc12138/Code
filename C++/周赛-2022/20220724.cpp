#include "head.h"
class FoodRatings {
public:
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        int n=foods.size();
        for(int i=0;i<n;i++){
            m1[cuisines[i]].emplace(foods[i],ratings[i]);
            m2[foods[i]]=cuisines[i];
            m3[foods[i]]=ratings[i];
        }
    }
    
    void changeRating(string food, int newRating) {
        int r=m3[food];
        string c=m2[food];
        m1[c].erase(pair<string,int>(food,r));
        m1[c].emplace(food,newRating);
        m3[food]=newRating;
    }
    
    string highestRated(string cuisine) {
        auto p=*m1[cuisine].begin();
        return p.first;
    }
    struct comp{
        bool operator() (pair<string,int> a ,pair<string,int> b)const{
            return a.second>b.second||a.first<b.first&&a.second==b.second;
        }
    };
    map<string,set<pair<string,int>,comp>> m1;
    map<string,string> m2;
    map<string,int> m3;
};
class Solution {
public:
    long long countExcellentPairs(vector<int>& nums, int k) {
        vector<int> temp;
        long long res=0;
        map<int,int> mp,mp1;
        for(int i:nums){
            int t=0;
            for(int j=0;j<32;j++){
                t+=(i>>j)&1;
            }
            if(mp.count(i)){
                continue;
            }else{
                for(int j=k-t;j<=30;j++){
                    res+=(long long)2*mp1[j];
                }
                if(t*2>=k){res++;}
                mp1[t]++;
            }
            mp[i]++;
        }
        return res;
    }
};