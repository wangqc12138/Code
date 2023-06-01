#include "head.h"
using pii = pair<int, int>;
class Solution {
public:
    vector<int> supplyWagon(vector<int>& supplies) {
        auto cmp = [&](pii a, pii b) { return a.first > b.first || a.first == b.first && a.second > b.second; };
        priority_queue<pii, vector<pii>, decltype(cmp)> mpq(cmp);
        int n = supplies.size();
        int index = 0;
        for (auto i : supplies) {
            mpq.emplace(i, index++);
        }
        while (mpq.size() > n / 2) {
            auto a = mpq.top();
            mpq.pop();
            auto b = mpq.top();
            mpq.pop();
            mpq.emplace(a.first + b.first, min(a.second, b.second));
        }
        vector<pii> temp;
        while (!mpq.empty()) {
            temp.emplace_back(mpq.top());
            mpq.pop();
        }
        sort(temp.begin(), temp.end(), [](pii a, pii b) { return a.second < b.second; });
        vector<int> res;
        for (auto [f, s] : temp) {
            res.emplace_back(f);
        }
        return res;
    }
};
class Solution {
public:
    vector<int> supplyWagon(vector<int>& supplies) {
        int n = supplies.size();
        while (supplies.size() > n / 2) {
            int flag = 0, maxn = INT_MAX;
            for (int i = 1; i < supplies.size(); i++) {
                if (supplies[i] + supplies[i - 1] < maxn) {
                    flag = i - 1;
                    maxn = supplies[i] + supplies[i - 1];
                }
            }
            auto temp = supplies;
            supplies.clear();
            for (int i = 0; i < temp.size(); i++) {
                if (i != flag)
                    supplies.emplace_back(temp[i]);
                else {
                    supplies.emplace_back(temp[i] + temp[++i]);
                }
            }
        }
        return supplies;
    }
};
class Solution {
public:
    int splite(string str, string x, set<string>& vstr) {
        string temp = "";
        for (int i = 0; i < str.size(); i++) {
            if (str[i] == '-') {
                vstr.emplace(temp);
                temp = "";
                i++;
            } else {
                temp += str[i];
            }
        }
        if (!str.empty()) {
            vstr.emplace(temp);
        }
        return vstr.size();
    }
    int adventureCamp(vector<string>& expeditions) {
        set<string> visit;
        splite(expeditions[0], "->", visit);
        int maxn = 0, res = -1;
        for (int i = 1; i < expeditions.size(); i++) {
            set<string> temp;
            int len = splite(expeditions[i], "->", temp);
            if (len <= maxn) {
                continue;
            }
            int t = 0;
            for (auto str : temp) {
                if (!visit.count(str)) {
                    t++;
                }
            }
            if (t > maxn) {
                maxn = max(t, maxn);
                res = i;
            }
        }
        return res;
    }
};