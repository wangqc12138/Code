#include "head.h"
/*
给你一个在 XY 平面上的 width x height 的网格图，左下角 的格子为 (0, 0) ，右上角 的格子为 (width - 1, height - 1) 。
网格图中相邻格子为四个基本方向之一（"North"，"East"，"South" 和 "West"）。一个机器人 初始 在格子 (0, 0) ，方向为 "East" 。

机器人可以根据指令移动指定的 步数 。每一步，它可以执行以下操作。

    沿着当前方向尝试 往前一步 。
    如果机器人下一步将到达的格子 超出了边界 ，机器人会 逆时针 转 90 度，然后再尝试往前一步。

如果机器人完成了指令要求的移动步数，它将停止移动并等待下一个指令。

请你实现 Robot 类：

    Robot(int width, int height) 初始化一个 width x height 的网格图，机器人初始在 (0, 0) ，方向朝 "East" 。
    void move(int num) 给机器人下达前进 num 步的指令。
    int[] getPos() 返回机器人当前所处的格子位置，用一个长度为 2 的数组 [x, y] 表示。
    String getDir() 返回当前机器人的朝向，为 "North" ，"East" ，"South" 或者 "West" 。

 */
class Robot {
public:
    Robot(int width, int height) {
		w=width;
		h=height;
    }
    
    void move(int num) {
		num=num%((w+h-2)*2);
		now+=num;
		now=now%((w+h-2)*2);
    }
    
    vector<int> getPos() {
		if(now<=w-1){
			return {now,0};
		}else if(now<=w+h-2){
			return {w-1,now-w+1};
		}else if(now<=2*w+h-3){
			return {now-(2*w+h-3),h-1};
		}else{
			return {0,(w+h-2)*2-now};
		}
    }
    
    string getDir() {
		if(now<=w-1){
			return "East";
		}else if(now<=w+h-2){
			return "South";
		}else if(now<=2*w+h-3){
			return "West";
		}else{
			return "North";
		}
    }
private:
	int now=0;
	int w,h;
};

/**
 * Your Robot object will be instantiated and called as such:
 * Robot* obj = new Robot(width, height);
 * obj->move(num);
 * vector<int> param_2 = obj->getPos();
 * string param_3 = obj->getDir();
 */
/* 
给你一个二维整数数组 items ，其中 items[i] = [pricei, beautyi] 分别表示每一个物品的 价格 和 美丽值 。

同时给你一个下标从 0 开始的整数数组 queries 。对于每个查询 queries[j] ，你想求出价格小于等于 queries[j] 的物品中，最大的美丽值 是多少。
如果不存在符合条件的物品，那么查询的结果为 0 。

请你返回一个长度与 queries 相同的数组 answer，其中 answer[j]是第 j 个查询的答案。

 */
class Solution {
public:
    vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries) {
		
    }
};