#include "head.h"
class Solution {
public:
    int minMaxDifference(int num) {
        string str = to_string(num);
        int s1 = num, s2 = num;
        for (int i = 0; i <= 9; i++) {
            for (int j = 0; j <= 9; j++) {
                if (i == j) {
                    continue;
                }
                string t = str;
                for (auto& c : t) {
                    if (c == i + '0') {
                        c = j + '0';
                    }
                }
                s1 = max(s1, stoi(t));
                s1 = min(s1, stoi(t));
            }
        }
        return s1 - s2;
    }
};
// i j k l
class Solution {
public:
    int minimizeSum(vector<int>& nums) {
        set<int> st(nums.begin(), nums.end());
        bool zero = false;
        if (st.size() < nums.size()) {
            zero = true;
        }
        vector<int> temp(st.begin(), st.end());
        int n = temp.size(), res;
        if (temp.size() == 3) {
            return 0;
        }
        res = min(min(temp[n - 1] - temp[2], temp[n - 3] - temp[0]), temp[n - 2] - temp[1]);
        return res;
    }
};
class Solution {
public:
    int minImpossibleOR(vector<int>& nums) {
        int res = 0, i = 1, j = 0;
        set<int> st(nums.begin(), nums.end());
        if (!st.count(1)) {
            return 1;
        }
        for (; i < 32; i++) {
            vector<int> temp;
            for (auto t : nums) {
                int k = (t >> i) & 1;
                if (k == 0) {
                    temp.emplace_back(t);
                }
            }

            if (temp.empty()) {
                break;
            }
            nums = temp;
        }
        for (; j < i; j++) {
            if (!st.count(1 << j)) {
                break;
            }
        }
        return 1 << j;
    }
};

class Solution {
public:
    int minImpossibleOR(vector<int>& nums) {
        int res = 0;
        set<int> st(nums.begin(), nums.end());
        for (int i = 0; i < 32; i++) {
            int i0 = 0, i1 = 0;
            for (auto t : nums) {
                int k = (t >> i) & 1;
                // cout<<k<<" "<<t<<" "<<i<<endl;;
                if (k == 1) {
                    i1 = 1;
                } else {
                    i0++;
                }
                if (i1 == 1 && i0 > 1) {
                    break;
                }
            }
            // cout<<i<<"---\n";
            // cout<<i1<<" "<<i0<<endl;
            // cout<<"---\n";
            if (i1 == 0) {
                res += (1 << i);
                break;
            }
            if (i0 == 0) {
                if (i == 0) {
                    if (st.count(1)) {
                        return 2;
                    } else {
                        return 1;
                    }
                }
                res += (0 << i);
                break;
            }
            if (i0 == 1 && i > 0) {
                if (!st.count(1 << (i - 1))) {
                    res = 1 << (i - 1);
                    break;
                }
            }
        }
        return res;
    }
};
using pii = pair<int, int>;
class Solution {
public:
    vector<long long> handleQuery(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        vector<long long> res;
        for (auto i : nums2) {
            res.emplace_back(i);
        }
        long long temp;
        vector<pii> vp;
        for (auto vec : queries) {
            if (vec[0] == 3) {
                res.emplace_back(temp);
            }
            if (vec[0] == 1) {
            }
            if (vec[0] == 2) {
            }
        }
    }
};