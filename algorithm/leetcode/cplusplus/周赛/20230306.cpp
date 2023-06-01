#include "head.h"
class Solution {
public:
    int kItemsWithMaximumSum(int numOnes, int numZeros, int numNegOnes, int k) {
        int res = 0;
        if (numOnes < k) {
            res += numOnes;
            k -= numOnes;
        } else {
            return k;
        }
        if (numZeros < k) {
            k -= numZeros;
        } else {
            return res;
        }
        return res - k;
    }
};

class Solution {
public:
    bool primeSubOperation(vector<int>& nums) {
        vector<int> prim(1001, 1);
        vector<int> temp;
        for (int i = 2; i <= 1000; i++) {
            if (prim[i]) {
                temp.emplace_back(i);
                for (int j = 2; i * j <= 1000; j++) {
                    prim[i * j] = 0;
                }
            }
        }
        int k = lower_bound(temp.begin(), temp.end(), nums[0]) - temp.begin();
        if (k > 0) {
            nums[0] -= temp[k - 1];
        }
        for (int i = 1; i < nums.size(); i++) {
            int d = nums[i] - nums[i - 1];
            if (d <= 0) {
                return false;
            }
            int k = lower_bound(temp.begin(), temp.end(), d) - temp.begin();
            if (k > 0) {
                nums[i] -= temp[k - 1];
            }
        }
        return true;
    }
};
/*
[47,50,97,58,87,72,41,63,41,51,17,21,7,100,69,66,79,92,84,9,57,26,26,28,83,38]
[50,84,76,41,64,82,20,22,64,7,38,92,39,28,22,3,41,46,47,50,88,51,9,49,38,67,26,65,89,27,71,25,77,72,65,41,84,68,51,26,84,24,79,41,96,83,92,9,93,84,35,70,74,79,37,38,26,26,41,26]
 */
/*
[607,855,747,655,633,825,943,905,633,1227,685,1009,675,805,905,1330,655,625,619,607,929,605,1179,611,685,653,833,639,949,819,689,851,759,699,639,655,855,661,605,833,855,869,783,655,1097,839,1009,1179,1031,855,721,679,723,783,697,685,833,833,655,833]
[607,855,747,655,633,825,943,905,633,1227,685,1009,675,805,905,1331,655,625,619,607,929,605,1179,611,685,653,833,639,949,819,689,851,759,699,639,655,855,661,605,833,855,869,783,655,1097,839,1009,1179,1031,855,721,679,723,783,697,685,833,833,655,833]
 */
class Solution {
public:
    vector<long long> minOperations(vector<int>& nums, vector<int>& queries) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<long long> pre(n), res;
        pre[0] = nums[0];
        for (int i = 1; i < n; i++) {
            pre[i] += nums[i - 1];
        }
        for (auto i : queries) {
            int h = lower_bound(nums.begin(), nums.end(), i) - nums.begin();
            int t = upper_bound(nums.begin(), nums.end(), i) - nums.begin();
            res.emplace_back((h * i - h == 0 ? 0 : pre[h - 1]) + (pre[n - 1] - t == 0 ?: pre[t - 1] - (n - t) * h));
        }
        return res;
    }
};