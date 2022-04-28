#include "head.h"
/* 
给你一个整数 n 。如果 n 恰好有三个正除数 ，返回 true ；否则，返回 false 。

如果存在整数 k ，满足 n = k * m ，那么整数 m 就是 n 的一个 除数 。
 */
class Solution {
public:
    bool isThree(int n) {
        int res=0;
        for(int i=2;i<n;i++){
            if(n%i==0){
                res++;
            }
        }
        return res==1;
    }
};
/* 
给你 n 个项目，编号从 0 到 n - 1 。同时给你一个整数数组 milestones ，其中每个 milestones[i] 表示第 i 个项目中的阶段任务数量。

你可以按下面两个规则参与项目中的工作：

每周，你将会完成 某一个 项目中的 恰好一个 阶段任务。你每周都 必须 工作。
在 连续的 两周中，你 不能 参与并完成同一个项目中的两个阶段任务。
一旦所有项目中的全部阶段任务都完成，或者仅剩余一个阶段任务都会导致你违反上面的规则，那么你将 停止工作 。注意，由于这些条件的限制，你可能无法完成所有阶段任务。

返回在不违反上面规则的情况下你 最多 能工作多少周。
 */
class Solution {
public:
    long long numberOfWeeks(vector<int>& milestones) {
        long long res=0;
        long long sum=accumulate(milestones.begin(),milestones.end(),0);
        int maxn=*max_element(milestones.begin(),milestones.end());
        if(sum-maxn>maxn){
            return sum;
        }
        priority_queue<int> mpq;
        for(int i:milestones){
            mpq.emplace(i);
        }
        while(mpq.size()>1){
            int max=mpq.top();
            mpq.pop();
            int sec=mpq.top();
            mpq.pop();
            max-=sec;
            res+=sec*2;
            if(max==0){
                continue;
            }
            mpq.emplace(max);
        }
        return mpq.empty()?res:res+1;
    }
};
