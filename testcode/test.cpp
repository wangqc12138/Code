#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <queue>
#include <stack>
#include <sys/types.h>
#include <sys/stat.h> 
#include <unistd.h>
#include <map>
#include <bitset>
using namespace std;
vector<string> ans;
string temp;
//递归版本回溯
// void dfs1(vector<string>& vstr,int index){
// 	if(index==vstr.size()){
// 		ans.emplace_back(temp);
// 		return;
// 	}
// 	for(int i=0;i<vstr[index].size();i++){
// 		temp+=vstr[index][i];
// 		dfs1(vstr,index+1);
// 		temp.pop_back();
// 	}
// }
// //非递归版本 BFS
// void bfs(vector<string>& vstr){
// 	queue<string> mq;
// 	int index=0;
// 	//加入一个假定的头-空字符串
// 	mq.emplace("");
// 	while(index<vstr.size()){
// 		int len=mq.size();
// 		//将队列的字符串弹出加index层的元素
// 		for(int i=0;i<len;i++){
// 			auto f=mq.front();
// 			mq.pop();
// 			//再将拼装后的加入队列
// 			for(int j=0;j<vstr[index].size();j++){
// 				mq.emplace(f+vstr[index][j]);
// 			}
// 		}
// 		cout<<"第"<<index<<"层:"<<endl;
// 		queue<string> t=mq;
// 		int k=0;
// 		while(!t.empty()){
// 			cout<<t.front()<<" ";
// 			if(++k%10==0){
// 				cout<<endl;
// 			}
// 			t.pop();
// 		}
// 		cout<<endl;
// 		index++;
// 	}
// 	while(!mq.empty()){
// 		ans.emplace_back(mq.front());
// 		mq.pop();
// 	}
// } 
// //非递归-dfs
// void dfs2(vector<string>& vstr){
// 	stack<pair<string,int>> msk;
// 	msk.emplace("",0);
// 	while(!msk.empty()){
// 		auto psi=msk.top();
// 		int len=psi.first.size();
// 		int index=psi.second;
// 		if(len==vstr.size()){
// 			ans.emplace_back(psi.first);
// 			msk.pop();
// 			continue;
// 		}
// 		if(index==vstr[len].size()){
// 			msk.pop();
// 			continue;
// 		}
// 		psi.first+=vstr[len][index];
// 		psi.second=0;
// 		msk.top().second++;
// 		msk.emplace(psi);
// 	}
// }
using ll=long long;
ll get_soncnt(vector<vector<int>>& skills, map<ll, int> dict) {
        int n = skills.size();
        ll ans = 0;
        for(int i = 0; i < n; ++i){  
			for(auto k:skills[i]){
				cout<<k<<":";
			}
			cout<<endl;
            int l = skills[i].size();
            for(int t = 1; t < (1 << l) - 1; ++t){
                ll cj = 0;
				cout<<bitset<sizeof(int)>(t)<<":"<<endl;
                for(int j = 0; j < l; ++j){
                    if(t & (1 << j)){
                        cj = (cj << 10) + skills[i][j];
						cout<<j<<" ";
                    }
                }
				cout<<endl;
                ans += dict[cj];
            }
        }
        return ans;
    }
int main(){
	vector<vector<int>> skills={{1,2,3,4}};
	map<ll,int> cnt;
	get_soncnt(skills,cnt);
	int k=10&1;
	cout<<k<<endl;
	return 0;
}
