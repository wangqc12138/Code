#include "head.h"
class Solution {
public:
    vector<int> findKDistantIndices(vector<int>& nums, int key, int k) {
        vector<int> res;
        int n=nums.size();
        for(int i=0;i<n;i++){
            for(int j=max(0,i-k);j<min(n,i+k+1);j++){
                if(nums[j]==key){
                    res.emplace_back(i);
                    break;
                }
            }
        }
        return res;
    }
};
class Solution {
public:
    int digArtifacts(int n, vector<vector<int>>& artifacts, vector<vector<int>>& dig) {
        set<pair<int,int>> st;
        int res=0;
        for(auto vec:dig){
            st.emplace(vec[0],vec[1]);
        }
        for(auto vec:artifacts){
            bool flag=true;
            for(int i=vec[0];i<vec[1];i++){
                for(int j=vec[2];j<vec[3];j++){
                    if(!st.count(pair<int,int>(i,j))){
                        flag=false;
                        break;
                    }
                }
                if(!flag){
                    break;
                }
            }
            if(flag){
                res++;
            }
        }
        return res;
    }
};
/* class Solution {
public:
    int maximumTop(vector<int>& nums, int k) {
        int n=nums.size();
        if(n==1&&k%2==1){
            return -1;
        }
        int maxn=-1,maxi=-1;
        for(int i=0;i<min(n,k);i++){
            if(nums[i]>maxn){
                maxi=i;
                maxn=nums[i];
            }
        }  
        if((k-maxi)%2==0||maxi!=n-1){
            return maxi;
        } 
        return *max_element(nums.begin(),nums.end()-1);     
    }
}; */
class node{
public:
    int k;
    long long w;
    vector<int> d;
    node(int k,long long w,vector<int> dir):k(k),w(w){
        d==dir;
        d.emplace_back(k);
    }
    bool operator>(const node &n)const{
		return w>n.w;
	}
};
class Solution {
public:
    long long minimumWeight(int n, vector<vector<int>>& edges, int src1, int src2, int dest) {
        map<long long,map<long long,long long>> next;
        for(auto vec:edges){
            next[vec[1]][vec[0]]=vec[2];
        }       
        priority_queue<node> mpq;
        vector<int> visit(n,0);
        mpq.emplace(node(dest,0,vector<int>{}));
        long long index=0,res=0;
        vector<vector<int>> temp;
        while(!mpq.empty()){
            int k=mpq.top().k;
            int w=mpq.top().w;
            auto d=mpq.top().d;
            mpq.pop();
            if(visit[k]==1){
                continue;
            }
            visit[k]=1;
            if(src1==k||src2==k){
                res+=w;
                temp.emplace_back(d);
                index++;
            }
            if(index==2){
                break;
            }
            for(auto nxt:next[k]){
                if(visit[nxt.first]){
                    continue;
                }
                mpq.emplace(node(nxt.first,w+nxt.second,d));
            }
        }
        if(index!=2){
            return -1;
        }
        int k=dest;
        for(int i=0;i<min(temp[0].size(),temp[1].size());i++){
            if(temp[0][i]==temp[1][i]){
                res-=next[k][temp[0][i]];
                k=temp[0][i];
            }
        }
    }
};