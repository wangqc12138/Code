#include "head.h"
class Solution {
public:
    int fillCups(vector<int>& amount) {
        sort(amount.begin(),amount.end());
        int res=0;
        while(amount[2]!=0){
            res++;
            if(amount[1]>0){
                amount[1]--;
            }
            amount[2]--;
            sort(amount.begin(),amount.end());
        }
        return res;
    }
};
class SmallestInfiniteSet {
public:
    SmallestInfiniteSet() {
        for(int i=1;i<=1000;i++){
            st.emplace(i);
        }
    }
    
    int popSmallest() {
        if(st.empty()){
            return 1;
        }
        int res=*st.begin();
        st.erase(res);
        return res;
    }
    
    void addBack(int num) {
        st.emplace(num);
    }
private:
    set<int> st;
};
class Solution {
public:
    bool canChange(string start, string target) {
        int n=start.size();
        int index=0;
        for(int i=0;i<n;i++){
            if(target[i]=='L'){
                index++;
            }
            if(start[i]=='L'){
                if(--index<0){
                    return false;
                }
            }else if(start[i]=='R'){
                if(index>0){
                    return false;
                }
            }
        }
        if(index!=0){
            return false;
        }
        for(int i=n-1;i>=0;i--){
            if(target[i]=='R'){
                index++;
            }
            if(start[i]=='R'){
                if(--index<0){
                    return false;
                }
            }else if(start[i]=='L'){
                if(index>0){
                    return false;
                }
            }
        }
        return index==0;
    }
};
class Solution {
public:
    int idealArrays(int n, int maxValue) {
        int res=0,sum=maxValue;
        int MOD=1000000007;
        for(int i=0;i<n;i++){
            for(int j=1;j<maxValue;j++){
                res+=maxValue/j;
                res%=MOD;
            }
        }
        return res;
    }
};