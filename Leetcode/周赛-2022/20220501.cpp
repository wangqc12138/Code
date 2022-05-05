#include "head.h"
class Solution {
public:
    string removeDigit(string number, char digit) {
        string res="";
        for(int i=0;i<number.size();i++){
            if(number[i]==digit){
                string str=number.substr(0,i)+number.substr(i+1);
                if(res==""||res<str){
                    res=str;
                }
            }
        }
        return res;
    }
};
class Solution {
public:
    int minimumCardPickup(vector<int>& cards) {
        map<int,int> win;
        int n=cards.size(),L=0,R=0,res=-1;
        while(R<n){
            while(R<n){
                if(++win[cards[R++]]==2){
                    break;
                }
            }
            while(L<R){
                if(win[cards[L++]]--==2){
                    res=R-L;
                }
            }
        }      
        return res;
    }
};
class Solution {
public:
    int countDistinct(vector<int>& nums, int k, int p) {
        int n=nums.size(),res=0;
        vector<int> sum(n+1,0);
        set<vector<int>> visit;
        for(int i=0;i<n;i++){
            sum[i+1]=nums[i]%p==0+sum[i];
        }
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(sum[j+1]-sum[i]>k){
                    break;
                }
                vector<int> temp(nums.begin()+i,nums.begin()+j);
                if(!visit.count(temp)){
                    res++;
                    visit.emplace(temp);
                }
            }
        }
        return res;
    }
};
class Solution {
public:
    long long appealSum(string s) {
        int n=s.size();
        string str;
        vector<int> num;
        int index=1;
        for(int i=0;i<n;i++){
            if(i==0){
                str+=s[0];
                continue;
            }
            if(s[i]==s[i-1]){
                index++;
            }else{
                str+=s[i];
                num.emplace_back(index);
                index=1;
            }
        }
        num.emplace_back(index);
        n=str.size();
        long long res;
        for(int i=0;i<n;i++){
            set<char> st;
            int sum=0;
            for(int j=i;j<n;j++){
                st.emplace(str[i]);
                sum+=num[j];
                res+=st.size()*sum;
            }
        }
        return res;
    }
};