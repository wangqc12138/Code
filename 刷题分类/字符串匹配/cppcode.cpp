#include <string>
#include <map>
#include <vector>
using namespace std;
/*
实现 strStr() 函数。
给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 needle 字符串出现的第一个位置（下标从 0 开始）。如果不存在，则返回  -1 。
*/
// KMP算法
class Solution {
public:
    int strStr(string haystack, string needle) {

    }
};
// BM算法
class Solution {
public:
    int strStr(string haystack, string needle) {
    	int m=haystack.size(),n=needle.size(),i=0,j;
        gs=vector<int>(n,-1);
        isHead=vector<bool>(n,false);
        goodsuffix(needle);
    	//坏字符表
    	for(;i<n;i++){
    		bc[needle[i]]=i;
    	}
    	i=0;
    	while(i<=m-n){
    		j=n-1;
    		while(j>=0&&haystack[i+j]==needle[j]){
    			j--;
    		}
    		if(j<0){
    			return i;
    		}
    		char badC=haystack[i+j];
            int b_m,g_m=0;
    		if(bc.count(badC)){
    			b_m=i+j-bc[badC];
    		}else{
    			b_m=i+j+1;
    		}
    		if(j<n-1){
    			g_m=i+move_gm(j,n);
    		}
    		i=max(b_m,g_m);
    	}
        return -1;
    }
    void goodsuffix(string needle){
    	int n=needle.size();
        for(int i=0;i<n-1;i++){
            int k=i,j=n-1;
            int len=0;
            //好后缀的子串必为尾部子串
            //匹配好后缀子串必为头部
            while(k>=0&&needle[k]==needle[j]){
                k--;
                j--;
                len++;
                gs[len]=k+1;
            }
            if(k==-1){
                isHead[len]=true;
            }
        }
    }
    int move_gm(int j,int n){
        int len=n-j-1;
        if(gs[len]!=-1){
            return j-gs[len]+1;
        }
        for(int i=len-1;i>0;i--){
            if(isHead[i]==true){
                return n-gs[i]+1;
            }
        }
        return n;
    }
private:
	map<char,int> bc;
	vector<int> gs;
    vector<bool> isHead;
};
// Sunday算法
class Solution {
public:
    int strStr(string haystack, string needle) {
        if(needle==""){
            return 0;
        }
        int m=haystack.size(),n=needle.size(),i,j,k,tmp;
        for(i=0;i<n;i++){
            shift[needle[i]]=i;
        }
        i=0;
        while(i<=m-n){
            j=0,k=i+n,tmp=i;
            while(j<n&&haystack[i]==needle[j]){
                i++;
                j++;
            }
            if(j==n){
                return tmp;
            }
            char c=haystack[k];
            if(shift.count(c)){
                i=tmp+n-shift[c];
            }else{
                i=tmp+n+1;
            }
        }
        return -1;
    }
private:
    map<char,int> shift;
};