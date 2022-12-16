#include "head.h"
/* 
街上有 n 栋房子整齐地排成一列，每栋房子都粉刷上了漂亮的颜色。
给你一个下标从 0 开始且长度为 n 的整数数组 colors ，其中 colors[i] 表示第  i 栋房子的颜色。

返回 两栋 颜色 不同 房子之间的 最大 距离。

第 i 栋房子和第 j 栋房子之间的距离是 abs(i - j) ，其中 abs(x) 是 x 的绝对值。
 */
class Solution {
public:
    int maxDistance(vector<int>& colors) {
        return dfs(colors,0,colors.size()-1);
    }
	int dfs(vector<int>& colors,int i,int j){
		if(i==j){
			return 0;
		}
		if(colors[i]!=colors[j]){
			return abs(j-i);
		}
		return max(dfs(colors,i+1,j),dfs(colors,i,j-1));
	}
};
/* 
你打算用一个水罐给花园里的 n 株植物浇水。植物排成一行，从左到右进行标记，编号从 0 到 n - 1 。其中，第 i 株植物的位置是 x = i 。x = -1 处有一条河，你可以在那里重新灌满你的水罐。

每一株植物都需要浇特定量的水。你将会按下面描述的方式完成浇水：

    按从左到右的顺序给植物浇水。
    在给当前植物浇完水之后，如果你没有足够的水 完全 浇灌下一株植物，那么你就需要返回河边重新装满水罐。
    你 不能 提前重新灌满水罐。

最初，你在河边（也就是，x = -1），在 x 轴上每移动 一个单位 都需要 一步 。

给你一个下标从 0 开始的整数数组 plants ，数组由 n 个整数组成。其中，plants[i] 为第 i 株植物需要的水量。另有一个整数 capacity 表示水罐的容量，返回浇灌所有植物需要的 步数 。
 */
class Solution {
public:
    int wateringPlants(vector<int>& plants, int capacity) {
		int res=1,c=capacity;
		for(int i=0;i<plants.size();i++){
			c-=plants[i];
			if(i!=plants.size()-1){
				if(c<plants[i+1]){
                    c=capacity;
					res+=2*(i+1)+1;
				}else{
					res++;
				}
			}
		}
		return res;
    }
};
/* 
请你设计一个数据结构，它能求出给定子数组内一个给定值的 频率 。

子数组中一个值的 频率 指的是这个子数组中这个值的出现次数。

请你实现 RangeFreqQuery 类：

    RangeFreqQuery(int[] arr) 用下标从 0 开始的整数数组 arr 构造一个类的实例。
    int query(int left, int right, int value) 返回子数组 arr[left...right] 中 value 的 频率 。

一个 子数组 指的是数组中一段连续的元素。arr[left...right] 指的是 nums 中包含下标 left 和 right 在内 的中间一段连续元素。
 */
class RangeFreqQuery {
public:
    RangeFreqQuery(vector<int>& arr) {
		for(int i=0;i<arr.size();i++){
			mp[arr[i]].emplace_back(i);
		}
    }
    
    int query(int left, int right, int value) {
		if(!mp.count(value)){
			return 0;
        }
		auto l=lower_bound(mp[value].begin(),mp[value].end(),left);
		auto r=upper_bound(mp[value].begin(),mp[value].end(),right);
		return r-l;
    }
	map<int,vector<int>> mp;
};
