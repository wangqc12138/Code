#include"head.h"
/* 
字母的 字母值 取决于字母在字母表中的位置，从 0 开始 计数。即，'a' -> 0、'b' -> 1、'c' -> 2，以此类推。

对某个由小写字母组成的字符串 s 而言，其 数值 就等于将 s 中每个字母的 字母值 按顺序 连接 并 转换 成对应整数。

例如，s = "acb" ，依次连接每个字母的字母值可以得到 "021" ，转换为整数得到 21 。
给你三个字符串 firstWord、secondWord 和 targetWord ，每个字符串都由从 'a' 到 'j' （含 'a' 和 'j' ）的小写英文字母组成。

如果 firstWord 和 secondWord 的 数值之和 等于 targetWord 的数值，返回 true ；否则，返回 false 。
 */
class Solution {
public:
    bool isSumEqual(string firstWord, string secondWord, string targetWord) {
        int n1=0,n2=0,n3=0;
        for(auto c:firstWord){
            n1=10*n1+c-'a';
        }
        for(auto c:secondWord){
            n2=10*n2+c-'a';
        }
        for(auto c:targetWord){
            n3=10*n3+c-'a';
        }
        return n1+n2==n3;
    }
};
/* 
给你一个非常大的整数 n 和一个整数数字 x ，大整数 n 用一个字符串表示。n 中每一位数字和数字 x 都处于闭区间 [1, 9] 中，且 n 可能表示一个 负数 。

你打算通过在 n 的十进制表示的任意位置插入 x 来 最大化 n 的 数值 ​​​​​​。但 不能 在负号的左边插入 x 。

例如，如果 n = 73 且 x = 6 ，那么最佳方案是将 6 插入 7 和 3 之间，使 n = 763 。
如果 n = -55 且 x = 2 ，那么最佳方案是将 2 插在第一个 5 之前，使 n = -255 。
返回插入操作后，用字符串表示的 n 的最大值。
 */
class Solution {
public:
    string maxValue(string n, int x) {
        string res;
        if(n[0]=='-'){
            int i=1;
            for(;i<n.size();i++){
                if(n[i]>x-'0'){
                    break;
                }
            }
            for(int j=0;j<i;j++){
                res+=n[j];
            }
            res+=x+'0';
            for(int j=i;j<n.size();j++){
                res+=n[j];
            }
        }else{
            int i=0;
            for(;i<n.size();i++){
                if(n[i]<x-'0'){
                    break;
                }
            }
            for(int j=0;j<i;j++){
                res+=n[j];
            }
            res+=x+'0';
            for(int j=i;j<n.size();j++){
                res+=n[j];
            }
        }
        return res;
    }
};
/* 
给你两个 下标从 0 开始 的整数数组 servers 和 tasks ，长度分别为 n​​​​​​ 和 m​​​​​​ 。servers[i] 是第 i​​​​​​​​​​ 台服务器的 权重 ，而 tasks[j] 是处理第 j​​​​​​ 项任务 所需要的时间（单位：秒）。

你正在运行一个仿真系统，在处理完所有任务后，该系统将会关闭。每台服务器只能同时处理一项任务。第 0 项任务在第 0 秒可以开始处理，相应地，第 j 项任务在第 j 秒可以开始处理。

处理第 j 项任务时，你需要为它分配一台 权重最小 的空闲服务器。

如果存在多台相同权重的空闲服务器，请选择 下标最小 的服务器。如果一台空闲服务器在第 t 秒分配到第 j 项任务，那么在 t + tasks[j] 时它将恢复空闲状态。

如果没有空闲服务器，则必须等待，直到出现一台空闲服务器，并 尽可能早 地处理剩余任务。 如果有多项任务等待分配，则按照 下标递增 的顺序完成分配。

如果同一时刻存在多台空闲服务器，可以同时将多项任务分别分配给它们。

构建长度为 m 的答案数组 ans ，其中 ans[j] 是第 j 项任务分配的服务器的下标。

返回答案数组 ans​​​​ 。
 */
class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int time=0;
        map<int,int> map;
        vector<int> res;
        for(int i:servers){
            map[i]=0;
        }
        for(int i=0;i<tasks.size();i++){
            bool k=false;
            for(auto& [s,t]:map){
                if(t==0){
                    res.push_back(s);
                    t=time+tasks[i];
                    k=true;
                }
            }
            for(auto& [s,t]:map){
                if(t!=0){
                    t--;
                }
            }
            time++;
            if(k==false){
                i--;
                continue;
            }
        }
    }
};