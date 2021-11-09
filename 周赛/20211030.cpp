#include "head.h"
/* 
 */
class Solution {
public:
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
        int m = queries.size(),n = s.size();
        vector<int> res(m);
        int prefixSum[n+1];prefixSum[0] = 0;
        int positionRight[n+1];positionRight[0] = 0;
        int positionLeft[n+1];
        for(int i = 1; i <= n;++i){
            if(s[i-1] == '*'){
                prefixSum[i] = prefixSum[i-1] + 1;
                positionRight[i] = positionRight[i-1];
            }
            else{
                prefixSum[i] = prefixSum[i-1];
                positionRight[i] = i-1;
            }
        }
        if(s[n-1] == '|')positionLeft[n] = n-1;
        else positionLeft[n] = n;
        for(int i = n-1; i >= 1;--i){
            if(s[i-1] == '|'){
                positionLeft[i] = i-1;
            }else{
                positionLeft[i] = positionLeft[i+1];
            }
        }
        for(int i = 0; i < m;++i){
            int start = queries[i][0],end = queries[i][1];
            int left = positionLeft[start+1],right = positionRight[end+1];
            if(left >= right)res[i] = 0;
            else{
                res[i] = prefixSum[right+1] - prefixSum[left];
            }
        }
        return res;
    }
};
