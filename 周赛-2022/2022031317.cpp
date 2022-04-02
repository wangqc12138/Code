#include "head.h"
/* 
给定一个链表的头结点 head，判断链表删除一个节点后是否可以成为「回文链表」。
若可以，则返回 true；否则返回 false
 */
class Solution {
public:
    bool isPalindrome(ListNode* head) {
		vector<int> temp;
		ListNode* ptr=head;
		while(ptr){
			temp.emplace_back(ptr->val);
			ptr=ptr->next;
		}
		int n=temp.size();
		int index=0;
		for(int i=0,j=n-1;i<j;i++,j--){
			if(temp[i]!=temp[j]){
                if(index==1){
                    return false;
                }
				if(temp[i]==temp[j-1]){
					j--;
				}else if(temp[i+1]==temp[j]){
					i++;
				}else{
					return false;
				}
				index=1;
			}
		}
        return true;
    }
};
/* 
「云闪付」作为各方联手打造的全新移动端统一入口，致力成为消费者省钱省心的移动支付管家。
请你设计一个「云闪付」优惠活动管理系统 DiscountSystem，具体功能如下：

    AddActivity(int actId, int priceLimit, int discount, int number, int userLimit) -- 表示创建编号为 actId 的优惠减免活动：
        单笔消费的原价不小于 priceLimit 时，可享受 discount 的减免
        每个用户最多参与该优惠活动 userLimit 次
        该优惠活动共有 number 数量的参加名额

    RemoveActivity(actId) -- 表示结束编号为 actId 的优惠活动

    Consume(int userId, int cost) -- 表示用户 userId 产生了一笔原价为 cost 的消费。请返回用户的实际支付金额。
        单次消费最多可参加一份优惠活动
        若可享受优惠减免，则 「支付金额 = 原价 - 优惠减免」
        若同时满足多个优惠活动时，则优先参加优惠减免最大的活动

        注：若有多个优惠减免最大的活动，优先参加 actId 最小的活动

注意：

    actId 全局唯一
 */
class DiscountSystem {
public:
    DiscountSystem() {
    }
    
    void addActivity(int actId, int priceLimit, int discount, int number, int userLimit) {
		mp[actId]=vector<int>{priceLimit,discount,number,userLimit};
    }
    
    void removeActivity(int actId) {
		if(mp.count(actId)){
			mp.erase(actId);
		}
    }
    
    int consume(int userId, int cost) {
		int a=1001,minn=cost;
		for(auto &&[x,vec]:mp){
			if(vec[2]==0){
				continue;
			}
			if(person[userId][x]==vec[3]){
				continue;
			}
			if(vec[0]>cost){
				continue;
			}
			if(minn>cost-vec[1]||(minn==cost-vec[1]&&x<a)){
				minn=cost-vec[1];
				a=x;
			}
		}
        if(a==1001){
            return cost;
        }
		mp[a][2]--;
		person[userId][a]++;
		return minn;
    }
private:
	map<int,vector<int>> mp;
	map<int,map<int,int>> person;
};
/* 
某公司计划推出一批投资项目。 product[i] = price 表示第 i 个理财项目的投资金额 price 。客户在按需投资时，需要遵循以下规则：

    客户在首次对项目 product[i] 投资时，需要投入金额 price
    对已完成首次投资的项目 product[i] 可继续追加投入，但追加投入的金额需小于上一次对该项目的投入(追加投入为大于 0 的整数)
    为控制市场稳定，每人交易次数不得大于 limit。(首次投资和追加投入均记作 1 次交易)

若对所有理财项目中最多进行 limit 次交易，使得投入金额总和最大，请返回这个最大值的总和。

注意：

    答案需要以 1e9 + 7 (1000000007) 为底取模，如：计算初始结果为：1000000008，请返回 1
	
    1 <= product.length <= 10^5
    1 <= product[i] <= 10^7
    1 <= limit <= 10^9

 */
class Solution {
public:
    int maxInvestment(vector<int>& product, int limit) {
		priority_queue<int,vector<int>,less<int>> mpq;
		for(auto i:product){
			mpq.emplace(i);
		}
		int pre=mpq.top();
        mpq.pop();
		long long res=0,num=1;
        mpq.emplace(0);
		while(!mpq.empty()&&limit){
			int k=mpq.top();
			mpq.pop();
			if(limit>=(pre-k)*num){
				limit-=(pre-k)*num;
				res+=(long long)(pre+k+1)*(pre-k)*num/2;
				res%=1000000007;
				num++;
			}else{
				int t=limit/num;
				int c=limit%num;
				res+=(long long)(2*pre-t+1)*t/2*num;
				res+=(long long)(pre-t)*c;
				res%=1000000007;
				limit=0;
			}
            //cout<<limit<<" ";
            //cout<<res<<endl;
			pre=k;
		}
		return res;
    }
};
//还有二分的方法，极小化极大，跟珂珂吃香蕉题目很像！
/* 
为了不断提高用户使用的体验，开发团队正在对产品进行全方位的开发和优化。
已知开发团队共有若干名成员，skills[i] 表示第 i 名开发人员掌握技能列表。
如果两名成员各自拥有至少一门对方未拥有的技能，则这两名成员可以「合作开发」。
请返回当前有多少对开发成员满足「合作开发」的条件。由于答案可能很大，请你返回答案对 10^9 + 7 取余的结果。
    2 <= skills.length <= 10^5
    1 <= skills[i].length <= 4
    1 <= skills[i][j] <= 1000
    skills[i] 中不包含重复元素
逆向思维，4个最大为1000可以用60位来表示
 */
using ll=long long;
class Solution {
public:
    int coopDevelop(vector<vector<int>>& skills) {
		int n=skills.size();
		map<ll,int> mp;
		for(auto vec:skills){
			long long t=0;
			for(auto i:vec){
				t=t<<10+i;
			}
			mp[t]++;
		}
		ll ch=0;
		for(auto vec:skills){
			int len=vec.size();
			for(int i=1;i<(1<<len)-1;i++){
				long long t=0;
				for(int j=0;j<len;j++){
					if(i&(1<<j)){
						t+=t<<10+vec[j];
					}
				}
				ch+=mp[t];
			}
		}
		ll cnt=0;
		for(auto [x,y]:mp){
			cnt+=(y-1)*y/2;
		}
		ll res=(ll)(n-1)*n/2-cnt-ch;
		res%=1000000007;
		return res;
    }
};