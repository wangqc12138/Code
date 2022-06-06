#include "head.h"
class Solution {
public:
    string largestGoodInteger(string num) {
        string res="";
        for(int i=0;i<num.size()-2;i++){
            bool flag=true;
            for(int j=0;j<3;j++){
                if(num[i]!=num[i+j]){
                    flag=false;
                }
            }
            if(flag&&num.substr(i,3)>res){
                res=num.substr(i,3);
            }
        }
        return res;
    }
};
class Solution {
public:
    int res=0;
    int averageOfSubtree(TreeNode* root) {
        dfs(root);
        return res;
    }
    pair<int,int> dfs(TreeNode* root){
        if(root==0){
            return {0,0};
        }
        auto l=dfs(root->left);
        auto r=dfs(root->right);
        int sum=root->val+l.second+r.second;
        if(sum/(l.first+r.first+1)==root->val){
            res++;
        }
        return {l.first+r.first+1,sum};
    }
};
//pressedKeys = "222222222222222222222222222222222222"
class Solution {
public:
    int countTexts(string str) {
        int n=str.size();
        vector<int> dp(n);
        dp[0]=1;
        for(int i=1;i<n;i++){
            if(i==1){
                if(str[i]!=str[i-1]){
                    dp[i]=dp[i-1];
                }else{
                    dp[i]=dp[i-1]+1;
                }
                continue;
            }
            if(i==2){
                if(str[i]!=str[i-1]){
                    dp[i]=dp[i-1];
                }else if(str[i]!=str[i-2]){
                    dp[i]=dp[i-1]+dp[i-2];
                }else{
                    dp[i]=4;
                }
                continue;
            }
            if(i==3&&(str[i]=='7'||str[i]=='9')){
                if(str[i]!=str[i-1]){
                    dp[i]=dp[i-1];
                }else if(str[i]!=str[i-2]){
                    dp[i]=dp[i-1]+dp[i-2];
                }else if(str[i]!=str[i-3]){
                    dp[i]=dp[i-1]+dp[i-2]+dp[i-3];
                }else{
                    dp[i]=8;
                }
                continue;
            }
            if(str[i]!='7'&&str[i]!='9'){
                if(str[i]!=str[i-1]){
                    dp[i]=dp[i-1];
                }else if(str[i]!=str[i-2]){
                    dp[i]=dp[i-1]+dp[i-2];
                }else{
                    dp[i]=dp[i-1]+dp[i-2]+dp[i-3];
                }
            }else{
                if(str[i]!=str[i-1]){
                    dp[i]=dp[i-1];
                }else if(str[i]!=str[i-2]){
                    dp[i]=dp[i-1]+dp[i-2];
                }else if(str[i]!=str[i-3]){
                    dp[i]=dp[i-1]+dp[i-2]+dp[i-3];
                }else{
                    dp[i]=dp[i-1]+dp[i-2]+dp[i-3]+dp[i-4];
                }
            }
            dp[i]%=1000000007;
        }
        return dp[n-1];
    }
};
class Solution {
public:
    stack<char> sk;
    bool hasValidPath(vector<vector<char>>& grid) {
        int m=grid.size(),n=grid[0].size();
        return dfs(grid,0,0,m,n);
    }
    bool dfs(vector<vector<char>>& grid,int i,int j,int m,int n){
        if(i>=m||j>=n){
            return false;
        }
        if(i==m-1&&j==n-1){
            return sk.empty();
        }
        if(grid[i][j]=='('){
            sk.emplace('(');
        }else if(sk.empty()){
            return false;
        }else{
            sk.pop();
        }
        if(dfs(grid,i+1,j,m,n)){
            return true;
        }
        if(dfs(grid,i,j+1,m,n)){
            return true;
        }
        if(grid[i][j]=='('){
            sk.pop();
        }
        return false;
    }
};