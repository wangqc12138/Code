#ifndef HEAD_H
#define HEAD_H
#include <stdlib.h>
#include <vector>
#include <map>
#include <limits.h>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


#endif