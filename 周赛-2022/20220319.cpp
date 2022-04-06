#include "head.h"
class Solution {
public:
    bool divideArray(vector<int>& nums) {
        map<int,int> mp;
        for(auto num:nums){
            mp[num]++;
        }
        for(auto [x,y]:mp){
            if(y%2!=0){
                return false;
            }
        }
        return true;
    }
};
class Solution {
public:
    long long maximumSubsequenceCount(string text, string pattern) {
        long long a=0,b=0;
        long long res=0;
        for(auto i:text){
            if(i==pattern[0]){
                a++;
            }
            if(i==pattern[1]){
                res+=a;
            }
        }
        if(a>b){
            return res+a+1;
        }
        return res+b+1;
    }
};
class Solution {
public:
    int halveArray(vector<int>& nums) {
        priority_queue<double> mq;
        long long sum=0;
        for(auto i:nums){
            sum+=i;
            mq.emplace(i);
        }
        long long del=0;
        int res=0;
        while(del<sum/2&&!mq.empty()){
            double k=(double)mq.top()/2;
            mq.pop();
            mq.emplace(k);
            res++;
        }
        return res;
    }
};
using  pii=pair<int,int>;
class Solution {
public:
    int minimumWhiteTiles(string floor, int numCarpets, int carpetLen) {
        int n1=help(floor,numCarpets,carpetLen);
        reverse(floor.begin(),floor.end());
        int n2=help(floor,numCarpets,carpetLen);
        return min(n1,n2);
    }
    int help(string floor, int numCarpets, int carpetLen) {
        int len=0,n=floor.size();
        vector<int> vec(n,0),visit(n,0);
        auto cmp=[](pii a,pii b){
            if(a.second<b.second){
                return true;
            }else if(a.second==b.second){
                return a.first>b.first;
            }
            return false;
        };
        priority_queue<pii,vector<pii>,decltype(cmp)> mpq(cmp);
        int sum=0;
        for(int i=0;i<carpetLen;i++){
            if(floor[i]=='1'){
                vec[0]++;
            }
        }
        if(floor[0]=='1'){
            mpq.emplace(0,vec[0]);   
        }
        for(int i=carpetLen;i<n;i++){
            vec[i-carpetLen+1]=vec[i-carpetLen]+floor[i]-floor[i-carpetLen];
            if(floor[i-carpetLen+1]=='1'){
                mpq.emplace(i-carpetLen+1,vec[i-carpetLen+1]);
            }
        }
        for(int i=n-carpetLen+1;i<n;i++){
            vec[i]=vec[i-1]-floor[i-1]+'0';
            if(floor[i]=='1'){
                mpq.emplace(i,vec[i]);   
            }
        }
        for(auto i:floor){
            sum+=i-'0';
        }
//cout<<sum<<endl;
        while(numCarpets>0&&!mpq.empty()){
            pii t=mpq.top();
            mpq.pop();
            //cout<<" "<<t.first<<" "<<t.second<<endl;
            int k=t.second;
            for(int i=t.first;i<min(n,t.first+carpetLen);i++){
                if(visit[i]==1&&floor[i]=='1'){
                    t.second--;
                }
            }
            if(k!=t.second){
                mpq.emplace(t);
                continue;
            }
            cout<<t.first<<" "<<t.second<<endl;
            sum-=t.second;
            numCarpets--;
            for(int i=t.first;i<min(n,t.first+carpetLen);i++){
                visit[i]=1;
            }
        }
        return sum;
    }
};