#include "head.h"
class Solution {
public:
    bool findSubarrays(vector<int>& nums) {
        if(nums.size()==2){
            return false;
        }
        map<int,int> mp;
       for(int i=0;i<nums.size()-1;i++){
            if(mp.count(nums[i]+nums[i+1])){
                return true;
            }
            mp[nums[i]+nums[i+1]]++;
       }
       return false;
    }
};
class Solution {
public:
    bool isStrictlyPalindromic(int n) {
        for(int i=2;i<=n-2;i++){
            string temp;
            int m=n;
            while(m){
                int t=m%i;
                m/=i;
                temp+=to_string(t);
            }
            string str=temp;
            string end=temp;
            reverse(str.begin(),str.end());
            if(str!=end){
                return false;
            }
        }
        return true;
    }
};
class Solution {
public:
    set<int> temp;
    int res=0;
    void help(vector<vector<int>>& mat,int m,int n,int k,int cols){
        if(cols==temp.size()){
            int t=0;
            for(int i=0;i<m;i++){
                int sum=accumulate(mat[i].begin(),mat[i].end(),0);
                for(int j=0;j<n;j++){
                    if(temp.count(j)){
                        sum-=mat[i][j];
                    }
                }
                t+=sum==0;
            }
            res=max(res,t);
            return;
        }
        for(int i=k;i<n;i++){
            temp.emplace(i);
            help(mat,m,n,i+1,cols);
            temp.erase(i);
        }
    } 
    int maximumRows(vector<vector<int>>& mat, int cols) {
        int m=mat.size(),n=mat[0].size();
        help(mat,m,n,0,cols);
        return res;
    }
};
class Solution {
public:
    int maximumRobots(vector<int>& chargeTimes, vector<int>& runningCosts, long long budget) {
        int L=0,R=0,n=chargeTimes.size(),sum,res;
        deque<int> mdq;
		while(R<n){
			while(!mdq.empty()&&L>=mdq.front()){
				mdq.pop_front();
			}
			while(!mdq.empty()&&chargeTimes[R]>chargeTimes[mdq.back()]){
				mdq.pop_back();
			}
			mdq.emplace_back(R);
			int maxn=mdq.front();
            sum+=runningCosts[R++];
            while(maxn+sum>budget){
                sum-=runningCosts[L++];
            }
            res=max(R-L,res);
		}
        return res;
    }
};
[11,12,74,67,37,87,42,34,18,90,36,28,34,20]
[18,98,2,84,7,57,54,65,59,91,7,23,94,20]
937
4