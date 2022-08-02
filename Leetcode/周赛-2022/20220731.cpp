#include "head.h"
class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        set<int> st(nums.begin(),nums.end());
        return *st.begin()==0?st.size()-1:st.size();
    }
};
class Solution {
public:
    int maximumGroups(vector<int>& grades) {
        sort(grades.begin(),grades.end(),greater<int>());
        vector<int> sum=grades;
        int n=grades.size();
        for(int i=1;i<n;i++){
            sum[i]+=sum[i-1];
        }
        int p=0,s=sum[0],len=1,res=1;
        for(int i=1;i<n;i++){
            if(sum[i]-sum[p]>s&&i-p>len){
                len=i-p;
                s=sum[i]-sum[p];
                p=i;
                res++;
            }
        }
        return res;
    }
};
class Solution {
public:
    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        map<int,int> m1,m2;
        int i=node1,len=0,res=-1;
        while(i!=-1&&!m1.count(i)){
            m1[i]=len++;
            i=edges[i];
        }
        i=node2,len=0;
        while(i!=-1&&!m2.count(i)){
            m2[i]=len++;
            i=edges[i];
        }
        len=INT_MAX;
        for(auto [x,y]:m1){
            if(m2.count(x)){
                if(len>max(y,m2[x])){
                    res=x;
                    len=max(y,m2[x]);
                }
            }
        }
        return res;
    }
};
class Solution {
public:
    int longestCycle(vector<int>& edges) {
        set<int> visit;
        int i,res=-1,len;
        for(i=0;i<edges.size();i++){
            if(!visit.count(i)){
                int k=i;
                map<int,int> mp;
                int len=0;
                while(k!=-1&&!visit.count(k)){
                    mp[k]=len++;
                    visit.emplace(k);
                    k=edges[k];
                    if(mp.count(k)){
                        res=max(res,len-mp[k]);
                        break;
                    }
                }
            }
        }
        return res;
    }
};