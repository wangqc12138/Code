#include "../head.h"
/* 
给你一个下标从 0 开始的字符串 s ，它的 偶数 下标处为小写英文字母，奇数 下标处为数字。
定义一个函数 shift(c, x) ，其中 c 是一个字符且 x 是一个数字，函数返回字母表中 c 后面第 x 个字符。
    比方说，shift('a', 5) = 'f' 和 shift('x', 0) = 'x' 。
对于每个 奇数 下标 i ，你需要将数字 s[i] 用 shift(s[i-1], s[i]) 替换。
请你替换所有数字以后，将字符串 s 返回。题目 保证 shift(s[i-1], s[i]) 不会超过 'z' 。
 */
class Solution {
public:
    string replaceDigits(string s) {
        char pre;
        for(char &c:s){
            if(c>='0'&&c<='9'){
                c=pre+c-'0';
            }else{
                pre=c;
            }
        }
        return s;
    }
};
/* 
请你设计一个管理 n 个座位预约的系统，座位编号从 1 到 n 。

请你实现 SeatManager 类：

    SeatManager(int n) 初始化一个 SeatManager 对象，它管理从 1 到 n 编号的 n 个座位。所有座位初始都是可预约的。
    int reserve() 返回可以预约座位的 最小编号 ，此座位变为不可预约。
    void unreserve(int seatNumber) 将给定编号 seatNumber 对应的座位变成可以预约。
 */
 //直接遍历超时
class SeatManager {
public:
    SeatManager(int n) {
        for(int i=1;i<=n;i++){
            m_pq.push(i);
        }
    }
    
    int reserve() {
        int res=m_pq.top();
        m_pq.pop();
        return res;
    }
    
    void unreserve(int seatNumber) {
        m_pq.push(seatNumber);
    }
private:
    priority_queue<int,vector<int>,greater<int>> m_pq;
};

/**
 * Your SeatManager object will be instantiated and called as such:
 * SeatManager* obj = new SeatManager(n);
 * int param_1 = obj->reserve();
 * obj->unreserve(seatNumber);
 */

 /* 
 给你一个正整数数组 arr 。请你对 arr 执行一些操作（也可以不进行任何操作），使得数组满足以下条件：

    arr 中 第一个 元素必须为 1 。
    任意相邻两个元素的差的绝对值 小于等于 1 ，也就是说，对于任意的 1 <= i < arr.length （数组下标从 0 开始），都满足 abs(arr[i] - arr[i - 1]) <= 1 。abs(x) 为 x 的绝对值。

你可以执行以下 2 种操作任意次：

    减小 arr 中任意元素的值，使其变为一个 更小的正整数 。
    重新排列 arr 中的元素，你可以以任意顺序重新排列。

请你返回执行以上操作后，在满足前文所述的条件下，arr 中可能的 最大值 。
 */
class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        sort(arr.begin(),arr.end());
        arr[0]=1;
        for(int i=1;i<arr.size();i++){
            arr[i]=min(arr[i-1]+1,arr[i]);
        }
        return arr.back();
    }
};