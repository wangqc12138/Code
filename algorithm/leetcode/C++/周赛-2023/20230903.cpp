#include "head.h"
class Solution {
public:
    int countSymmetricIntegers(int low, int high) {
        int res = 0;
        for (int i = low; i <= high; i++) {
            string s = to_string(i);
            if (s.size() % 2 == 0) {
                int t = 0;
                for (int j = 0; j < s.size(); j++) {
                    if (j < s.size() / 2) {
                        t += s[j] - '0';
                    } else {
                        t -= s[j] - '0';
                    }
                }
                res += t == 0;
            }
        }
        return res;
    }
};
class Solution {
public:
    int minimumOperations(string num) {
        int n = num.size(), res = 0;
        auto help = [&](string s) -> string {
            string re = "";
            int k = 0;
            for (int i = 0; i < s.size(); i++) {
                int a = k * 10 + (s[i] - '0');
                re += to_string(a / 5);
                k = a % 5;
            }
            if (k == 0) {
                return re;
            } else {
                return "";
            }
        };
        auto check = [&](string s) {
            if (s.size() < 4) {
                return stoi(s) % 25 == 0;
            } else {
                return s.substr(s.size() - 2) == "75" || s.substr(s.size() - 2) == "25" || s.substr(s.size() - 2) == "00" || s.substr(s.size() - 2) == "50";
            }
            if (s.back() != '0' && s.back() != '5') {
                return false;
            }
            string t = help(s);
            if (t.empty() || (t.back() != '0' && t.back() != '5')) {
                return false;
            }
            return help(t) != "";
        };
        function<void(string, int)> dfs = [&](string s, int index) {
            if (s.size() && check(s)) {
                res = max((int)s.size(), res);
            }
            for (int i = index; i < n; i++) {
                dfs(s + num[i], i + 1);
            }
        };
        dfs("", 0);
        // cout<<help("25")<<endl;
        return n - res;
    }
};
class Solution {
public:
    int minimumOperations(string num) {
        int n = num.size(), k = 0;
        set<int> st;
        int re = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (num[i] == '0') {
                if (st.count(0)) {
                    if (st.count(5)) {
                        re++;
                    }
                    return re;
                } else {
                    st.emplace(0);
                    continue;
                }
            } else if (num[i] == '5') {
                if (st.count(0)) {
                    if (st.count(5)) {
                        re++;
                    }
                    return re;
                }
                if (!st.count(5)) {
                    st.emplace(5);
                    continue;
                }
            } else if (num[i] == '2' || num[i] == '7') {
                if (st.count(5)) {
                    if (st.count(0)) {
                        re++;
                    }
                    return re;
                }
            }
            re++;
        }
        return st.count(0) ? n - 1 : n;
    }
};
class Solution {
public:
    long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) {
        int n = nums.size();
        long long res = 0;
        set<int> st;
        map<int, int> mp;
        vector<int> pre(n, 0);
        for (auto& i : nums) {
            i = i % modulo == k;
        }
        pre[0] = nums[0];
        if (nums[0]) {
            mp[pre[0]] = 0;
        }
        for (int i = 1; i < n; i++) {
            pre[i] = pre[i - 1] + nums[i];
            if (nums[i]) {
                mp[pre[i]] = i;
            }
            if (pre[i] % modulo == k) {
                st.emplace(pre[i]);
            }
        }
        for (auto t : st) {
            for (auto [x, y] : mp) {
                if (mp.count(x + t)) {
                    res += (long long)((mp.count(x - 1) ? (mp[x] - mp[x - 1] - 1) : 1) * (mp.count(x + t + 1) ? (mp[x + t + 1] - mp[x + t] - 1) : 1));
                }
            }
        }
        return res;
    }
};