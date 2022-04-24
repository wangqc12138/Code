#include "head.h"
class Solution {
public:
    vector<int> intersection(vector<vector<int>>& nums) {
        set<int> st(nums[0].begin(),nums[1].end());
        for(auto num:nums){
            set<int> temp;
            for(auto i:num){
                if(st.count(i)){
                    temp.emplace(i);
                }
            }
            st=temp;
        }
        vector<int> res;
        for(auto i:st){
            res.emplace_back(i);
        }
        return res;
    }
};
class Solution {
public:
    int countLatticePoints(vector<vector<int>>& circles) {
        int res=0;
        for(int i=0;i<=200;i++){
            for(int j=0;j<=200;j++){
                for(auto& vec:circles){
                    int x=vec[0],y=vec[1],r=vec[2];
                    if((i-x)*(i-x)+(j-y)*(j-y)<=r*r){
                        res++;
                        break;
                    }
                }
            }
        }
        return res;
    }
};
/* 
给你一个二维整数数组 rectangles ，其中 rectangles[i] = [li, hi] 表示第 i 个矩形长为 li 高为 hi 。
给你一个二维整数数组 points ，其中 points[j] = [xj, yj] 是坐标为 (xj, yj) 的一个点。

第 i 个矩形的 左下角 在 (0, 0) 处，右上角 在 (li, hi) 。

请你返回一个整数数组 count ，长度为 points.length，其中 count[j]是 包含 第 j 个点的矩形数目。

如果 0 <= xj <= li 且 0 <= yj <= hi ，那么我们说第 i 个矩形包含第 j 个点。如果一个点刚好在矩形的 边上 ，这个点也被视为被矩形包含。
 */
class Solution {
public:
    vector<int> countRectangles(vector<vector<int>>& rectangles, vector<vector<int>>& points) {
        sort(rectangles.begin(),rectangles.end(),greater());
        int maxh=rectangles[0][1];
        vector<vector<int>> help;
        help.emplace_back(rectangles[0]);
        for(int i=1;i<rectangles.size();i++){
            if(rectangles[i][1]>maxh){
                maxh=rectangles[i][1];
                help.emplace_back(rectangles[i]);
            }
        }
        vector<int> res(points.size(),0);
        int index=0;
        for(auto vec:points){
            int x=vec[0],y=vec[1];
            for(auto v:help){
                if(x<=v[0]&&y<=v[1]){
                    res[index++]++;
                }
                if(x>v[0]){
                    break;
                }
            }
        }
        return res;
    }
};