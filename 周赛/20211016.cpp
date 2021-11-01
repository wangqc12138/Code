#include "head.h"
/* 
一个房间里有 n 个座位和 n 名学生，房间用一个数轴表示。给你一个长度为 n 的数组 seats ，其中 seats[i] 是第 i 个座位的位置。
同时给你一个长度为 n 的数组 students ，其中 students[j] 是第 j 位学生的位置。

你可以执行以下操作任意次：

    增加或者减少第 i 位学生的位置，每次变化量为 1 （也就是将第 i 位学生从位置 x 移动到 x + 1 或者 x - 1）

请你返回使所有学生都有座位坐的 最少移动次数 ，并确保没有两位学生的座位相同。

请注意，初始时有可能有多个座位或者多位学生在 同一 位置。
 */
class Solution {
public:
    int minMovesToSeat(vector<int>& seats, vector<int>& students) {
        sort(seats.begin(),seats.end());
		sort(students.begin(),students.end());
		int res=0;
		for(int i=0;i<seats.size();i++){
			res+=abs(seats[i]-students[i]);
		}
		return res;
    }
};
/* 
总共有 n 个颜色片段排成一列，每个颜色片段要么是 'A' 要么是 'B' 。
给你一个长度为 n 的字符串 colors ，其中 colors[i] 表示第 i 个颜色片段的颜色。

Alice 和 Bob 在玩一个游戏，他们 轮流 从这个字符串中删除颜色。Alice 先手 。

    如果一个颜色片段为 'A' 且 相邻两个颜色 都是颜色 'A' ，那么 Alice 可以删除该颜色片段。Alice 不可以 删除任何颜色 'B' 片段。
    如果一个颜色片段为 'B' 且 相邻两个颜色 都是颜色 'B' ，那么 Bob 可以删除该颜色片段。Bob 不可以 删除任何颜色 'A' 片段。
    Alice 和 Bob 不能 从字符串两端删除颜色片段。
    如果其中一人无法继续操作，则该玩家 输 掉游戏且另一玩家 获胜 。

假设 Alice 和 Bob 都采用最优策略，如果 Alice 获胜，请返回 true，否则 Bob 获胜，返回 false。
 */
class Solution {
public:
    bool winnerOfGame(string colors) {
		int a=0,b=0;
		for(int i=1;i<colors.size();i++){
			if(colors[i]=='A'){
				if(colors[i-1]=='A'&&colors[i-1]==colors[i+1]){
					a++;
				}
			}else{
				if(colors[i-1]=='B'&&colors[i-1]==colors[i+1]){
					b++;
				}
			}
		}
		return a>b;
    }
};
/* 
给你一个有 n 个服务器的计算机网络，服务器编号为 0 到 n - 1 。
同时给你一个二维整数数组 edges ，其中 edges[i] = [ui, vi] 表示服务器 ui 和 vi 之间有一条信息线路，
在 一秒 内它们之间可以传输 任意 数目的信息。再给你一个长度为 n 且下标从 0 开始的整数数组 patience 。

题目保证所有服务器都是 相通 的，也就是说一个信息从任意服务器出发，都可以通过这些信息线路直接或间接地到达任何其他服务器。

编号为 0 的服务器是 主 服务器，其他服务器为 数据 服务器。每个数据服务器都要向主服务器发送信息，并等待回复。
信息在服务器之间按 最优 线路传输，也就是说每个信息都会以 最少时间 到达主服务器。
主服务器会处理 所有 新到达的信息并 立即 按照每条信息来时的路线 反方向 发送回复信息。

在 0 秒的开始，所有数据服务器都会发送各自需要处理的信息。从第 1 秒开始，每 一秒最 开始 时，
每个数据服务器都会检查它是否收到了主服务器的回复信息（包括新发出信息的回复信息）：

    如果还没收到任何回复信息，那么该服务器会周期性 重发 信息。
	数据服务器 i 每 patience[i] 秒都会重发一条信息，
	也就是说，数据服务器 i 在上一次发送信息给主服务器后的 patience[i] 秒 后 会重发一条信息给主服务器。
    否则，该数据服务器 不会重发 信息。

当没有任何信息在线路上传输或者到达某服务器时，该计算机网络变为 空闲 状态。

请返回计算机网络变为 空闲 状态的 最早秒数 。
 */
class Solution {
public:
    int networkBecomesIdle(vector<vector<int>>& edges, vector<int>& patience) {
		int n=patience.size();
		vector<int> visit(n,0);
		vector<vector<int>> next(n);
		for(auto vec:edges){
			next[vec[0]].emplace_back(vec[1]);
			next[vec[1]].emplace_back(vec[0]);
		}
		queue<int> mq;
		mq.emplace(0);
		while(!mq.empty()){
			int k=mq.front();
			mq.pop();
			if(visit[k]==1){
				continue;
			}
			visit[k]=1;
			for(auto i:)
		}
    }
};