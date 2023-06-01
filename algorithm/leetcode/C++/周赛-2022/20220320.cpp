#include "head.h"
class Solution {
public:
    int countHillValley(vector<int>& nums) {
        int res=0,n=nums.size();
        vector<int> vec;
        for(int i=0;i<n-1;i++){
            if(nums[i]!=nums[i+1]){
                vec.emplace_back(nums[i]);
            }
        }
        for(int i=1;i<vec.size();i++){
            if((vec[i]-vec[i-1])*(vec[i]-vec[i+1])>0){
                res++;
            }
        }
        return res;
    }
};
//directions = "RLRSLL"
class Solution {
public:
    int countCollisions(string directions) {
        int n=directions.size(),res=0;
        int i=0;
        for(;i<n;i++){
            if(directions[i]!='L'){
                break;
            }
        }
        if(i>n){
            return 0;
        }
        directions=directions.substr(i);
        n=directions.size();
        for(int i=n-1;i>=0;i--){
            if(directions[i]!='R'){
                break;
            }
            directions.pop_back();
        }
        n=directions.size();
        bool flag=true;
        for(int i=0;i<n;i++){
            if(directions[i]=='R'){
                res++;
                flag=true;
            }
            if(directions[i]=='L'&&flag){
                if(flag){
                    res+=2;
                    flag=false;
                }else{
                    res++;
                }
            }
            if(directions[i]=='S'){
                flag=true;
            }
        }
        return res;
    }
};
class Solution {
public:
    vector<int> maximumBobPoints(int numArrows, vector<int>& aliceArrows) {
        vector<pair<int,int>> vpp;
        for(int i=1;i<=11;i++){
            vpp.emplace_back(aliceArrows[i]+11-i,i);
        }
        auto cmp=[](auto a,auto b){
            if(a.first<b.first){
                return true;
            }else if(a.first==b.first){
                return a.second>b.second;
            }
        };
        sort(vpp.begin(),vpp.end(),cmp);
        vector<int> res(12,0);
        int sum=0;
        for(auto [x,y]:vpp){
            if(numArrows>=aliceArrows[y]+1){
                numArrows-=aliceArrows[y]+1;
                res[x]=aliceArrows[y]+1;
                sum+=x;
            }
        }
        cout<<sum<<endl;
        return res;
    }
};