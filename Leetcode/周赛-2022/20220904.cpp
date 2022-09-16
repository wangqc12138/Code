#include "head.h"
class Solution {
public:
    bool checkDistances(string s, vector<int>& distance) {
        map<int,int> mp;
        for(int i=0;i<s.size();i++){
            mp[s[i]-'a']=i-mp[s[i]-'a'];
        }
        for(auto [x,y]:mp){
            if(distance[x]!=y){
                return false;
            }
        }
        return true;
    }
};
class Solution {
public:
    int longestNiceSubarray(vector<int>& nums) {
       int n=nums.size();
       int p=0,res=1;
       for(int i=1;i<n;i++){
            for(int j=i-1;j>=p;j--){
                if(nums[i]&nums[j]!=0){
                    p=j+1;
                    break;
                }
            }
            res=max(res,i-p+1);
       } 
       return res;
    }
};
class Solution {
public:
    using ll = long long;
    ll res=0;
    //map<int,map<int,ll>> temp;
    void help(int k,int n,int target){
        if(k==0){
            if(n==target){
                res++;
            }
            return ;
        }
        if(abs(n-target)>=k||(k-abs(n-target))%2){
            res+=abs(n-target)==k;
            return;
        }
        help(k-1,n-1,target);
        help(k-1,n+1,target);
    }
    int numberOfWays(int startPos, int endPos, int k) {
        help(k,startPos,endPos);
        return res%1000000007;
    }
};
class Solution {
public:
    using pii=pair<int,int>;
    int mostBooked(int n, vector<vector<int>>& meetings) {
        sort(meetings.begin(),meetings.end());
        vector<int> temp(n,0);
        auto cmp=[](pii a,pii b){
            return a.second>b.second||a.second==b.second&&a.first>b.first;
        };
        priority_queue<pii,vector<pii>,decltype(cmp)> mpq(cmp);
        for(int i=0;i<n;i++){
            mpq.emplace(i,0);
        }
        for(auto vec:meetings){
            int st=vec[0],ed=vec[1];
            vector<pii> vp;
            while(!mpq.empty()){
                if(mpq.top().second>st){
                    break;
                }
                vp.emplace_back(mpq.top());
                mpq.pop();
            }
            if(vp.empty()){
                auto p=mpq.top();
                mpq.pop();
                mpq.emplace(p.first,ed+p.second-st);
                temp[p.first]++;
            }else{
                sort(vp.begin(),vp.end());
                vp[0].second=ed;
                for(auto p:vp){
                    mpq.emplace(p);
                }
                temp[vp[0].first]++;
            }
        }
        int m=0,res=0;
        for(int i=0;i<n;i++){
            if(temp[i]>m){
                res=i;
                m=temp[i];
            }
        }
        return res;
    }
};