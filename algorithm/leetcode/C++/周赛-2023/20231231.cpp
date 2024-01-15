#include "head.h"
class Solution {
public:
    bool hasTrailingZeros(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int k = nums[i] | nums[j];
                if (int(k & 1) == 0) {
                    return true;
                }
            }
        }
        return false;
    }
};
class Solution {
public:
    int maximumLength(string s) {
        map<string, int> mp;
        int res = -1;
        for (int i = 0; i < s.size(); i++) {
            for (int j = i; j < s.size(); j++) {
                if (s[j] == s[i]) {
                    auto str = s.substr(i, j - i + 1);
                    mp[str]++;
                    if (mp[str] >= 3) {
                        res = max(res, j - i + 1);
                    }
                } else {
                    break;
                }
            }
        }
        return res;
    }
};
class Solution {
public:
    int maximumLength(string s) {
        int len = 1, res = -1, n = s.size();
        map<int, map<int, int>> mp;
        for (int i = 0; i < n;) {
            int le = 1;
            for (int j = i + 1; j < n; j++) {
                if (s[i] != s[j]) {
                    break;
                } else {
                    le++;
                }
            }
            mp[s[i]][le]++;
            if (mp[s[i]].count(le + 1)) {
                res = max(res, le);
            } else if (mp[s[i]].count(le) && mp[s[i]][le] >= 2) {
                if (mp[s[i]][le] >= 3) {
                    res = max(res, le);
                } else if (mp[s[i]][le] == 2 && le != 1) {
                    res = max(res, le - 1);
                }
            } else if (mp[s[i]].count(le - 1)) {
                res = max(res, le - 1);
            } else if (le > 2) {
                res = max(res, le - 2);
            }
            i = le + i;
        }

        return res;
    }
};
