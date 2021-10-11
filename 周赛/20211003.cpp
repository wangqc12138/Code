#include "head.h"
/* 
给你一个字符串 s ，由 n 个字符组成，每个字符不是 'X' 就是 'O' 。

一次 操作 定义为从 s 中选出 三个连续字符 并将选中的每个字符都转换为 'O' 。注意，如果字符已经是 'O' ，只需要保持 不变 。

返回将 s 中所有字符均转换为 'O' 需要执行的 最少 操作次数。
 */
class Solution {
public:
    int minimumMoves(string s) {
		int res=0;
		for(int i=0;i<s.size();i++){
			if(s[i]=='X'){
				res++;
				i+=2;
			}
		}
		return res;
	}
};
/* 
现有一份 n + m 次投掷单个 六面 骰子的观测数据，骰子的每个面从 1 到 6 编号。观测数据中缺失了 n 份，你手上只拿到剩余 m 次投掷的数据。
幸好你有之前计算过的这 n + m 次投掷数据的 平均值 。

给你一个长度为 m 的整数数组 rolls ，其中 rolls[i] 是第 i 次观测的值。同时给你两个整数 mean 和 n 。

返回一个长度为 n 的数组，包含所有缺失的观测数据，且满足这 n + m 次投掷的 平均值 是 mean 。
如果存在多组符合要求的答案，只需要返回其中任意一组即可。如果不存在答案，返回一个空数组。

k 个数字的 平均值 为这些数字求和后再除以 k 。

注意 mean 是一个整数，所以 n + m 次投掷的总和需要被 n + m 整除。
 */
class Solution {
public:
    vector<int> missingRolls(vector<int>& rolls, int mean, int n) {
		int sum=accumulate(rolls.begin(),rolls.end(),0);
		int k=mean*(n+rolls.size());
		int m=(k-sum)/n;
		int j=(k-sum)%n;
		vector<int> res(n,m);
        if(m<=0||m>6){
            return {};
        }
		for(int i=0;i<j;i++){
			res[i]++;
			if(res[i]<=0||res[i]>6){
				return {};
			}
		}
		return res;
    }
};
/* 
Alice 和 Bob 再次设计了一款新的石子游戏。现有一行 n 个石子，每个石子都有一个关联的数字表示它的价值。给你一个整数数组 stones ，
其中 stones[i] 是第 i 个石子的价值。

Alice 和 Bob 轮流进行自己的回合，Alice 先手。每一回合，玩家需要从 stones 中移除任一石子。

    如果玩家移除石子后，导致 所有已移除石子 的价值 总和 可以被 3 整除，那么该玩家就 输掉游戏 。
    如果不满足上一条，且移除后没有任何剩余的石子，那么 Bob 将会直接获胜（即便是在 Alice 的回合）。

假设两位玩家均采用 最佳 决策。如果 Alice 获胜，返回 true ；如果 Bob 获胜，返回 false 。
1、不拿最后一个
2、拿了以后让对面拿任何一个都被3整除

1、让对面拿最后一个
2、同上
 */
class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        if(stones.size()==1){
            return false;
        }
        int i=0,j=0,k=0;
		for(int s:stones){
			if(s%3==0){
				i++;
			}else if(s%3==1){
				j++;
			}else{
				k++;
			}
		}
		if(j==0&&k==0){
			return false;
		}
        //cout<<i<<" "<<j<<" "<<k<<endl;
		int l=max(j,k)-min(j,k);
		i=i%2;
        if(i==0){
            if(min(j,k)==0){
                return false;
            }
        }else{
            if(l<=2){
			    return false;
		    }
        }
		
		return true;
    }
};
