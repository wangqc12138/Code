#include "head.h"
class Solution {
public:
    vector<int> findColumnWidth(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<int> ans(n, 0);
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < m; i++) {
                string s = to_string(grid[i][j]);
                ans[j] = max(ans[j], (int)s.size());
            }
        }
        return ans;
    }
};
class Solution {
public:
    TreeNode* replaceValueInTree(TreeNode* root) {
        queue<TreeNode*> mq;
        mq.emplace(root);
        while (!mq.empty()) {
            int len = mq.size();
            auto tq = mq;
            vector<int> temp;
            int sum = 0;
            for (int i = 0; i < len; i++) {
                auto node = mq.front();
                mq.pop();
                if (node != nullptr) {
                    temp.emplace_back(node->val);
                    sum += node->val;
                } else {
                    temp.emplace_back(0);
                }
            }
            int index = 0;
            for (int i = 0; i < len; i++) {
                auto node = tq.front();
                tq.pop();
                if (node == nullptr) {
                    continue;
                }
                int now = sum - temp[index];
                if (index > 0 && temp[index - 1] != 0) {
                    now -= temp[index - 1];
                }
                if (index < temp.size() - 1 && temp[index + 1] != 0) {
                    now -= temp[index + 1];
                }
                index++;
                node->val = now;
                if (node->left) {
                    mq.emplace(node->left);
                }
                if (node->right) {
                    mq.emplace(node->right);
                }
                mq.emplace(nullptr);
            }
        }
        return root;
    }
};
class Solution {
public:
    vector<long long> findPrefixScore(vector<int>& nums) {
        int n = nums.size();
        vector<long long> res(n);
        vector<int> temp = nums;
        for (int i = 1; i < n; i++) {
            temp[i] = max(temp[i], temp[i - 1]);
        }
        vector<long long> vec(n);
        for (int i = 0; i < n; i++) {
            vec[i] = (long long)(temp[i] + nums[i]);
        }
        res[0] = vec[0];
        for (int i = 1; i < n; i++) {
            res[i] = (long long)(res[i - 1] + vec[i]);
        }
        return res;
    }
};
using pii = pair<int, int>;
class Graph {
public:
    Graph(int n, vector<vector<int>>& edges) {
        N = n;
        for (auto vec : edges) {
            next[vec[0]][vec[1]] = vec[2];
        }
    }

    void addEdge(vector<int> edge) {
        next[edge[0]][edge[1]] = edge[2];
    }

    int shortestPath(int node1, int node2) {
        auto cmp = [&](pii& a, pii& b) {
            return a.second > b.second;
        };
        priority_queue<pii, vector<pii>, decltype(cmp)> mpq(cmp);
        mpq.emplace(node1, 0);
        vector<int> visit(N + 1, 0);
        while (!mpq.empty()) {
            auto [node, p] = mpq.top();
            mpq.pop();
            if (node == node2) {
                return p;
            }
            if (visit[node]) {
                continue;
            }
            visit[node] = 1;
            for (auto [x, y] : next[node]) {
                if (visit[x]) {
                    continue;
                }
                mpq.emplace(x, y + p);
            }
        }
        return -1;
    }

private:
    unordered_map<int, unordered_map<int, int>> next;
    int N;
};