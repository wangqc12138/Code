#include "head.h"
class Solution {
public:
    int findDelayedArrivalTime(int arrivalTime, int delayedTime) {
        return (arrivalTime + delayedTime) % 24;
    }
};
class Solution {
public:
    int sumOfMultiples(int n) {
        int res = 0;
        for (int i = 1; i <= n; i++) {
            if (i % 3 == 0 || i % 5 == 0 || i % 7 == 0) {
                res += i;
            }
        }
        return res;
    }
};
class Solution {
public:
    vector<int> getSubarrayBeauty(vector<int>& nums, int k, int x) {
        multiset<int> mst;
        int n = nums.size();
        vector<int> res;
        for (int i = 0; i < n; i++) {
            mst.emplace(nums[i]);
            if (i >= k - 1) {
                vector<int> temp(mst.begin(), mst.end());
                res.emplace_back(min(0, temp[x - 1]));
                temp.erase(find(temp.begin(), temp.end(), nums[i - k + 1]));
                mst = multiset<int>(temp.begin(), temp.end());
            }
        }
        return res;
    }
};
class Solution {
public:
    vector<int> getSubarrayBeauty(vector<int>& nums, int k, int x) {
        map<int, int> mp;
        int n = nums.size(), index = 0;
        vector<int> res;
        for (int i = 0; i < n; i++) {
            if (nums[i] < 0) {
                mp[nums[i]]++;
                index++;
            }
            if (i >= k - 1) {
                if (index >= x) {
                    int t = x;
                    for (int j = -50; j < 0; j++) {
                        if (t <= mp[j]) {
                            res.emplace_back(j);
                            break;
                        }
                        t -= mp[j];
                    }
                } else {
                    res.emplace_back(0);
                }
                if (nums[i - k + 1] < 0) {
                    mp[nums[i - k + 1]]--;
                    index--;
                }
            }
        }
        return res;
    }
};
// [6,10,15]

class Solution {
public:
    int minOperations(vector<int>& nums) {
        int g = nums[0], n = nums.size(), flag = 0;
        for (int i = 0; i < n - 1; i++) {
            g = gcd(g, nums[i + 1]);
            if (nums[i] == 1) {
                flag++;
            }
        }
        if (nums[n - 1] == 1) {
            flag++;
        }
        if (g != 1) {
            return -1;
        }
        if (flag) {
            return n - flag;
        }
        int minn = 100;
        for (int i = 0; i < n - 1; i++) {
            int g = nums[i];
            for (int j = i + 1; j < n; j++) {
                g = gcd(g, nums[j]);
                if (g == 1) {
                    minn = min(minn, j - i);
                    break;
                }
            }
        }
        return minn + n - 1;
    }
};
