#include "head.h"
class Solution {
public:
    int totalSteps(vector<int>& grid) {
        int n=nums.size();
        for(int i=n-1;i>=0;i--){
            if(nums[i]<nums[i-1]){

            }else{

            }
        }
    }
};
class Solution {
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int m=grid.size(), n=grid[0].size();
        vector<vector<int>> dp(m,vector<int>(n,10001));
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(i==0&&j==0){
                    dp[i][j]=0;
                }else if(i==0){
                    dp[i][j]=min(dp[i][j],dp[i][j-1]+grid[i][j]);
                }else if(j==0){
                    dp[i][j]=min(dp[i][j],dp[i-1][j]+grid[i][j]);
                }else{
                    dp[i][j]=min(dp[i][j],min(dp[i-1][j],dp[i][j-1])+grid[i][j]);
                }
            }
        }
        return dp[m-1][n-1];
    }
};
