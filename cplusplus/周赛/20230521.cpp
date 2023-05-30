#include "head.h"
class Solution {
public:
    int minLength(string s) {
        stack<char> sk;
        for (char c : s) {
            if (c == 'B' && !sk.empty() && sk.top() == 'A') {
                sk.pop();
                continue;
            }
            if (c == 'D' && !sk.empty() && sk.top() == 'C') {
                sk.pop();
                continue;
            }
            sk.emplace(c);
        }
        return sk.size();
    }
};
class Solution {
public:
    string makeSmallestPalindrome(string s) {
        int n = s.size();
        for (int i = 0; i < n / 2; i++) {
            if (s[i] != s[n - i - 1]) {
                s[i] = min(s[i], s[n - 1 - i]);
                s[n - 1 - i] = min(s[i], s[n - 1 - i]);
            }
        }
        return s;
    }
};
class Solution {
public:
    int punishmentNumber(int n) {
        vector<int> temp = {1, 9, 10, 36, 45, 55, 82, 91, 99, 100, 235, 297, 369, 370, 379, 414, 657, 675, 703, 756, 792, 909, 918, 945, 964, 990, 991, 999, 1000};
        int res = 0;
        for (auto i : temp) {
            if (i <= n) {
                res += i * i;
            }
        }
        return res;
    }
    // bool dfs(int n, int index, int now) {
    //     if (index >= to_string(n * n).size()) {
    //         return now == n;
    //     }
    //     if (now > n) {
    //         return false;
    //     }
    //     string str = to_string(n * n);
    //     for (int i = 1; i <= str.size() - index; i++) {
    //         if (dfs(n, index + i, now + stoi(str.substr(index, i)))) {
    //             return true;
    //         }
    //     }
    //     return false;
    // }
};
class node {
public:
    node(int x, int y) : x(x), y(y) {}
    node(int x, int y, int z, vector<int> dir) : x(x), y(y), z(z) {
        this->dir = dir;
        this->dir.emplace_back(x);
    }
    int x, y, z;
    bool operator<(const node& n) const {
        return y >= n.y;
    }
    vector<int> dir;
};
class Solution {
public:
    vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>>& edges, int source, int destination, int target) {
        map<int, map<int, int>> next;
        for (auto vec : edges) {
            next[vec[0]][vec[1]] = max(vec[2], 0);
            next[vec[1]][vec[0]] = max(vec[2], 0);
        }
        vector<int> visit(n, 0);
        priority_queue<node> mpq, mpq1;
        mpq.emplace(node(source, 0, 0, vector<int>()));
        mpq1.emplace(node(source, 0));
        while (!mpq1.empty()) {
            auto nd = mpq.top();
            mpq.pop();
            if (visit[nd.x]) {
                continue;
            }
            if (nd.x == destination && nd.y < target) {
                return vector<vector<int>>();
            }
            visit[nd.x] = 1;
            for (auto [a, b] : next[nd.x]) {
                if (!visit[a] && b) {
                    mpq.emplace(node(a, nd.y + b));
                }
            }
        }
        visit = vector<int>(n, 0);
        while (!mpq.empty()) {
            auto nd = mpq.top();
            mpq.pop();
            if (visit[nd.x]) {
                continue;
            }
            if (nd.x == destination) {
                if (nd.z == 0 && nd.y < target || nd.y + nd.z > target) {
                    return vector<vector<int>>();
                } else {
                    for (int i = 1; i < nd.dir.size(); i++) {
                        for (auto& vec : edges) {
                            if (vec[2] == -1 && (vec[0] == nd.dir[i] && vec[1] == nd.dir[i - 1] || vec[1] == nd.dir[i] && vec[0] == nd.dir[i - 1])) {
                                if (nd.z-- > 1) {
                                    vec[2] = 1;
                                    nd.y++;
                                } else {
                                    vec[2] = target - nd.y;
                                }
                            }
                        }
                    }
                    for (auto& vec : edges) {
                        if (vec[2] == -1) {
                            vec[2] = target;
                        }
                    }
                    return edges;
                }
            }
            visit[nd.x] = 1;
            for (auto [a, b] : next[nd.x]) {
                if (!visit[a]) {
                    mpq.emplace(node(a, nd.y + b, nd.z + (b == 0), nd.dir));
                }
            }
        }
        return vector<vector<int>>();
    }
};