#include "head.h"
/* 
给你一个下标从 0 开始的整数数组 nums ，返回 nums 中满足 i mod 10 == nums[i] 的最小下标 i ；如果不存在这样的下标，返回 -1 。

x mod y 表示 x 除以 y 的 余数 。
 */
class Solution {
public:
    int smallestEqual(vector<int>& nums) {
        for(int i=0;i<nums.size();i++){
			if(i%10==nums[i]){
				return i;
			}
		}
		return -1;
    }
};
/* 
链表中的 临界点 定义为一个 局部极大值点 或 局部极小值点 。

如果当前节点的值 严格大于 前一个节点和后一个节点，那么这个节点就是一个  局部极大值点 。

如果当前节点的值 严格小于 前一个节点和后一个节点，那么这个节点就是一个  局部极小值点 。

注意：节点只有在同时存在前一个节点和后一个节点的情况下，才能成为一个 局部极大值点 / 极小值点 。

给你一个链表 head ，返回一个长度为 2 的数组 [minDistance, maxDistance] ，
其中 minDistance 是任意两个不同临界点之间的最小距离，maxDistance 是任意两个不同临界点之间的最大距离。
如果临界点少于两个，则返回 [-1，-1] 。
 */
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
		ListNode* ptr=head;
		int pre=-1,index=0,k=0,i=0;
		int minn=100001,maxn=-1;
		while(ptr){
			if(ptr!=head&&ptr->next){
				if(ptr->val>ptr->next->val&&ptr->val>pre||ptr->val<ptr->next->val&&ptr->val<pre){
					minn=min(index-k,minn);
					maxn=max(index-k,maxn);
					i++;
					k=index;
				}
			}
			pre=ptr->val;
			ptr=ptr->next;
			index++;
		}
		if(i<2){
			return {-1,-1};
		}
		return vector<int>{minn,maxn};
    }
};
/* 
给你一个下标从 0 开始的整数数组 nums ，该数组由 互不相同 的数字组成。另给你两个整数 start 和 goal 。

整数 x 的值最开始设为 start ，你打算执行一些运算使 x 转化为 goal 。你可以对数字 x 重复执行下述运算：

如果 0 <= x <= 1000 ，那么，对于数组中的任一下标 i（0 <= i < nums.length），可以将 x 设为下述任一值：

    x + nums[i]
    x - nums[i]
    x ^ nums[i]（按位异或 XOR）

注意，你可以按任意顺序使用每个 nums[i] 任意次。使 x 越过 0 <= x <= 1000 范围的运算同样可以生效，但该该运算执行后将不能执行其他运算。

返回将 x = start 转化为 goal 的最小操作数；如果无法完成转化，则返回 -1 。
 */
class Solution {
public:
    int minimumOperations(vector<int>& nums, int start, int goal) {
		int visit[1001]={0};
		visit[start]=1;
		queue<int> mq;
		int res=0;
		mq.emplace(start);
		while(!mq.empty()){
			int len=mq.size();
			for(int i=0;i<len;i++){
				int k=mq.front();
				mq.pop();
				for(int j=0;j<nums.size();j++){
					int t1=k+nums[j];
					int t2=k-nums[j];
					int t3=k^nums[j];
					if(t1==goal||t2==goal||t3==goal){
						return res;
					}
					if(t1>=0&&t1<=1000&&visit[t1]==0){
						mq.emplace(t1);
						visit[t1]=1;
					}
					if(t2>=0&&t2<=1000&&visit[t2]==0){
						mq.emplace(t2);
						visit[t2]=1;
					}
					if(t3>=0&&t3<=1000&&visit[t3]==0){
						mq.emplace(t3);
						visit[t3]=1;
					}
				}
			}
			res++;
		}
		return -1;
    }
};
/* 
原字符串由小写字母组成，可以按下述步骤编码：

    任意将其 分割 为由若干 非空 子字符串组成的一个 序列 。
    任意选择序列中的一些元素（也可能不选择），然后将这些元素替换为元素各自的长度（作为一个数字型的字符串）。
    重新 顺次连接 序列，得到编码后的字符串。

例如，编码 "abcdefghijklmnop" 的一种方法可以描述为：

    将原字符串分割得到一个序列：["ab", "cdefghijklmn", "o", "p"] 。
    选出其中第二个和第三个元素并分别替换为它们自身的长度。序列变为 ["ab", "12", "1", "p"] 。
    重新顺次连接序列中的元素，得到编码后的字符串："ab121p" 。

给你两个编码后的字符串 s1 和 s2 ，由小写英文字母和数字 1-9 组成。
如果存在能够同时编码得到 s1 和 s2 原字符串，返回 true ；否则，返回 false。

注意：生成的测试用例满足 s1 和 s2 中连续数字数不超过 3 。
dp
 */
class Solution {
public:
	vector<int> get3num(string &str){
		vector<int> res;
		int i=str[0]-'0';
		int j=str[1]-'0';
		int k=str[2]-'0';
		i+j+k;
		i*10+j+k;
		i+j*10+k;
		i*100+j*10+k;
	}
    bool possiblyEquals(string s1, string s2) {
		for(int )
    }
};