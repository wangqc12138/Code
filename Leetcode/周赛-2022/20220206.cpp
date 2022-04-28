#include "head.h"
/* 
给你一个下标从 0 开始的整数数组 nums 。根据下述规则重排 nums 中的值：

    按 非递增 顺序排列 nums 奇数下标 上的所有值。
        举个例子，如果排序前 nums = [4,1,2,3] ，对奇数下标的值排序后变为 [4,3,2,1] 。奇数下标 1 和 3 的值按照非递增顺序重排。
    按 非递减 顺序排列 nums 偶数下标 上的所有值。
        举个例子，如果排序前 nums = [4,1,2,3] ，对偶数下标的值排序后变为 [2,1,4,3] 。偶数下标 0 和 2 的值按照非递减顺序重排。

返回重排 nums 的值之后形成的数组。
 */
 class Solution {
public:
    vector<int> sortEvenOdd(vector<int>& nums) {
		vector<int> odd,even;
		for(int i=0;i<nums.size();i++){
			if(i%2==0){
				even.emplace_back(nums[i]);
			}else{
				odd.emplace_back(nums[i]);
			}
		}
		sort(odd.begin(),odd.end(),greater());
		sort(even.begin(),even.end());
		int j=0,k=0;
		for(int i=0;i<nums.size();i++){
			if(i%2==0){
				nums[i]=even[j++];
			}else{
				nums[i]=odd[k++];
			}
		}
		return nums;
    }
};
/* 
给你一个整数 num 。重排 num 中的各位数字，使其值 最小化 且不含 任何 前导零。

返回不含前导零且值最小的重排数字。

注意，重排各位数字后，num 的符号不会改变。
 */
class Solution {
public:
    long long smallestNumber(long long num) {
		vector<int> temp;
		long long k=abs(num);
		while(k){
			temp.emplace_back(k%10);
			k/=10;
		}	
		sort(temp.begin(),temp.end());
		long long res=0;
		if(num<0){
			for(int i=temp.size()-1;i>=0;i--){
				res+=temp[i];
				res*=10;
			}
			res*=-1;
		}else{
			if(temp[0]==0){
				for(int i=0;i<temp.size();i++){
					if(temp[i]!=0){
						temp[0]=temp[i];
						temp[i]=0;
						break;
					}
				}
			}
			for(int i=0;i<temp.size();i++){
				res+=temp[i];
				res*=10;
			}
		}
		return res;
    }
};
/* 
位集 Bitset 是一种能以紧凑形式存储位的数据结构。

请你实现 Bitset 类。

    Bitset(int size) 用 size 个位初始化 Bitset ，所有位都是 0 。
    void fix(int idx) 将下标为 idx 的位上的值更新为 1 。如果值已经是 1 ，则不会发生任何改变。
    void unfix(int idx) 将下标为 idx 的位上的值更新为 0 。如果值已经是 0 ，则不会发生任何改变。
    void flip() 翻转 Bitset 中每一位上的值。换句话说，所有值为 0 的位将会变成 1 ，反之亦然。
    boolean all() 检查 Bitset 中 每一位 的值是否都是 1 。如果满足此条件，返回 true ；否则，返回 false 。
    boolean one() 检查 Bitset 中 是否 至少一位 的值是 1 。如果满足此条件，返回 true ；否则，返回 false 。
    int count() 返回 Bitset 中值为 1 的位的 总数 。
    String toString() 返回 Bitset 的当前组成情况。注意，在结果字符串中，第 i 个下标处的字符应该与 Bitset 中的第 i 位一致。
 */
class Bitset {
public:
    Bitset(int size) {
		for(int i=0;i<size;i++){
			Zero.emplace(i);
		}
    }
    
    void fix(int idx) {
		One.emplace(idx);
		Zero.erase(idx);
    }
    
    void unfix(int idx) {
		
    }
    
    void flip() {

    }
    
    bool all() {

    }
    
    bool one() {

    }
    
    int count() {

    }
    
    string toString() {

    }
    unordered_set<int> Zero,One;
};

/**
 * Your Bitset object will be instantiated and called as such:
 * Bitset* obj = new Bitset(size);
 * obj->fix(idx);
 * obj->unfix(idx);
 * obj->flip();
 * bool param_4 = obj->all();
 * bool param_5 = obj->one();
 * int param_6 = obj->count();
 * string param_7 = obj->toString();
 */