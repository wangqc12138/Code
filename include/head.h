#ifndef HEAD_H
#define HEAD_H
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <limits.h>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <unordered_map>
#include <queue>
#include <stack>
using namespace std;
typedef unsigned long long ull;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
class ArrayReader {
public:
    int get(int index);
};
#endif