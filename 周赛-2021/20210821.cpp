#include "head.h"
/* 

 */
class Node{
public:
    int num,time;
    Node(int num,int time):num(num),time(time){};
    // bool operator <(const Node& node)const{
    //     return time<node.time;
    // }
    bool operator>(const Node &n)const{
		return time>n.time;
	}
};
class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        unordered_map<int,unordered_map<int,int>> ump;
        priority_queue<Node,vector<Node>,greater<Node>> mpq;
        vector<int> price(n,INT_MAX);
        for(auto road:roads){
			ump[road[0]].emplace(road[1],road[2]);
		}
        mpq.emplace(Node(0,0));
        int res=0,mintime=INT_MAX;
        while(!mpq.empty()){
            Node node=mpq.top();
            mpq.pop();
            if(node.num==n-1){
                if(node.time==mintime){
                    res++;
                }else if(node.time<mintime){
                    res=1;
                    mintime=node.time;
                }
            }
            for(auto [next,time]:ump[node.num]){
                if(price[next]>=node.time+time){
                    price[next]=node.time+time;
				    mpq.emplace(Node(next,node.time+time));
                }
            }
        }
        return res;
    }
};