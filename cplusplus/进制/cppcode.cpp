#include "head.h"
/*
给你一个整数 n ，以二进制字符串的形式返回该整数的 负二进制（base -2）表示。

注意，除非字符串就是 "0"，否则返回的字符串中不能含有前导零。
T1017
 */
class Solution {
public:
    string baseNeg2(int n) {
        if (!n) {
            return "0";
        }
        return help(n, -2);
    }
    string help(int n, int x) {
        string res = "";
        while (n) {
            int remain = n % x;
            n = n / x;
            // 如果余数是负数，则说明商需要+1，使得余数非负
            if (remain < 0) {
                n++;
                remain -= x;
            }
            res += to_string(remain);
        }
        reverse(res.begin(), res.end());
        return res;
    }
};