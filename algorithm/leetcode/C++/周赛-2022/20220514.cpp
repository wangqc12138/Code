#include "head.h"
class Solution {
public:
    int maximumWhiteTiles(vector<vector<int>>& tiles, int carpetLen) {
        sort(tiles.begin(),tiles.end());
        int n=tiles.size();
        vector<int> temp;
        for(int i=0;i<n;i++){
            if(i!=0){
                temp.emplace_back(tiles[i][0]-tiles[i-1][1]-1);
            }
            temp.emplace_back(tiles[i][1]-tiles[i][0]+1);
        }
        vector<int> presum=temp;
        int m=temp.size();
        for(int i=1;i<m;i++){
            presum[i]+=presum[i-1];
        }
        set<int> st;
        st.emplace(0);
        int ans=0;
        for(int i=0;i<m;i++){
            auto itr=st.lower_bound(presum[i]-carpetLen);
            if(presum[i]-*itr<=carpetLen){
                ans=max(ans,presum[i]-*itr);
            }
            if(ans==carpetLen){
                return carpetLen;
            }
            st.emplace(presum[i]);
        }
        return ans;
    }
    int minimumWhiteTiles(string &floor, int n, int carpetLen) { // 默认代码没加引用，这里补上
        int m = floor.length();
        if (n * carpetLen >= m) return 0; // 剪枝
        vector<vector<int>> f(n + 1, vector<int>(m));
        f[0][0] = (floor[0] == '1');
        for (int i = 1; i < m; ++i)
            f[0][i] = f[0][i - 1] + (floor[i] == '1');
        for (int i = 1; i <= n; ++i)
            // j < carpetLen * i 的 f[i][j] 均为 0
            for (int j = carpetLen * i; j < m; ++j)
                f[i][j] = min(f[i][j - 1] + (floor[j] == '1'), f[i - 1][j - carpetLen]);
        return f[n][m - 1];
    }
};