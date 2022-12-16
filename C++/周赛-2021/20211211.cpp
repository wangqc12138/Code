#include "head.h"
/* 
你和一群强盗准备打劫银行。给你一个下标从 0 开始的整数数组 security ，其中 security[i] 是第 i 天执勤警卫的数量。
日子从 0 开始编号。同时给你一个整数 time 。

如果第 i 天满足以下所有条件，我们称它为一个适合打劫银行的日子：

    第 i 天前和后都分别至少有 time 天。
    第 i 天前连续 time 天警卫数目都是非递增的。
    第 i 天后连续 time 天警卫数目都是非递减的。

更正式的，第 i 天是一个合适打劫银行的日子当且仅当：security[i - time] >= security[i - time + 1] >= ... >= security[i] <= ... <= security[i + time - 1] <= security[i + time].

请你返回一个数组，包含 所有 适合打劫银行的日子（下标从 0 开始）。返回的日子可以 任意 顺序排列。
 */
class Solution {
public:
    vector<int> goodDaysToRobBank(vector<int>& security, int time) {
        int n=security.size();
		vector<int> left(n,0),right(n,0),res;
		for(int i=1;i<n;i++){
			if(security[i]<=security[i-1]){
				left[i]=left[i-1]+1;
			}
		}
		for(int i=n-2;i>=0;i--){
			if(security[i]<=security[i+1]){
				right[i]=right[i+1]+1;
			}
		}
		for(int i=0;i<n;i++){
			if(left[i]>=time&&right[i]>=time){
				res.emplace_back(i);
			}
		}
		return res;
    }
};
/* 
给你一个炸弹列表。一个炸弹的 爆炸范围 定义为以炸弹为圆心的一个圆。

炸弹用一个下标从 0 开始的二维整数数组 bombs 表示，其中 bombs[i] = [xi, yi, ri] 。
xi 和 yi 表示第 i 个炸弹的 X 和 Y 坐标，ri 表示爆炸范围的 半径 。

你需要选择引爆 一个 炸弹。当这个炸弹被引爆时，所有 在它爆炸范围内的炸弹都会被引爆，这些炸弹会进一步将它们爆炸范围内的其他炸弹引爆。

给你数组 bombs ，请你返回在引爆 一个 炸弹的前提下，最多 能引爆的炸弹数目。
 */
class Solution {
public:
    int maximumDetonation(vector<vector<int>>& bombs) {
		
    }
};