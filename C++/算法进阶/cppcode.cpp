#include "head.h"
// DAY1
/*
现有一个按 升序 排列的整数数组 nums ，其中每个数字都 互不相同 。

给你一个整数 k ，请你找出并返回从数组最左边开始的第 k 个缺失数字。
1060
 */
class Solution {
public:
    int missingElement(vector<int>& nums, int k) {
        int i = nums[0], index = 0;
        while (k) {
            if (index < nums.size() && nums[index] == i) {
                index++;
            } else {
                k--;
            }
            if (k) {
                i++;
            }
        }
        return i;
    }
};
class Solution {
public:
    int missingElement(vector<int>& nums, int k) {
        int i = 1;
        for (; i < nums.size(); i++) {
            if (nums[i] - nums[i - 1] - 1 >= k) {
                break;
            } else {
                k -= nums[i] - nums[i - 1] - 1;
            }
        }
        return nums[i - 1] + k;
    }
};
class Solution {
public:
    int missingElement(vector<int>& nums, int k) {
        int n = nums.size();
        int left = 0, right = n - 1;
        while (left < right) {
            // 排除右半部分，使用向上取整
            int mid = left + (right - left + 1) / 2;
            // cout<<left<<" "<<mid<<" "<<right<<endl;
            if (nums[mid] - nums[0] - mid < k) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }
        return k + left + nums[0];
    }
};
/*
一个 2D 网格中的 顶峰元素 是指那些 严格大于 其相邻格子(上、下、左、右)的元素。

给你一个 从 0 开始编号 的 m x n 矩阵 mat ，其中任意两个相邻格子的值都 不相同 。
找出 任意一个 顶峰元素 mat[i][j] 并 返回其位置 [i,j] 。

你可以假设整个矩阵周边环绕着一圈值为 -1 的格子。

要求必须写出时间复杂度为 O(m log(n)) 或 O(n log(m)) 的算法
1901
 */
// 不合法
class Solution {
public:
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (check(mat, i, j, m, n)) {
                    return {i, j};
                }
            }
        }
        return {};
    }
    bool check(vector<vector<int>>& mat, int i, int j, int m, int n) {
        if (i - 1 >= 0 && mat[i][j] < mat[i - 1][j]) {
            return false;
        }
        if (i + 1 < m && mat[i][j] < mat[i + 1][j]) {
            return false;
        }
        if (j - 1 >= 0 && mat[i][j] < mat[i][j - 1]) {
            return false;
        }
        if (j + 1 < n && mat[i][j] < mat[i][j + 1]) {
            return false;
        }
        return true;
    }
};

class Solution {
public:
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        int m = mat.size();
        int left = 0, right = m - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            // cout<<left<<" "<<mid<<" "<<right<<endl;
            if (mid > 0 && mid < m - 1) {
                int m1 = *max_element(mat[mid - 1].begin(), mat[mid - 1].end());
                int m2 = *max_element(mat[mid].begin(), mat[mid].end());
                int m3 = *max_element(mat[mid + 1].begin(), mat[mid + 1].end());
                // cout<<m1<<" "<<m2<<" "<<m3<<endl;
                if (m1 <= m2 && m3 <= m2) {
                    for (int i = 0; i < mat[mid].size(); i++) {
                        if (m2 == mat[mid][i]) {
                            return {mid, i};
                        }
                    }
                } else if (m1 <= m2) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            } else if (mid == 0) {
                int m2 = *max_element(mat[mid].begin(), mat[mid].end());
                int m3 = *max_element(mat[mid + 1].begin(), mat[mid + 1].end());
                if (m3 <= m2) {
                    for (int i = 0; i < mat[mid].size(); i++) {
                        if (m2 == mat[mid][i]) {
                            return {mid, i};
                        }
                    }
                } else {
                    left = mid + 1;
                }
            } else {
                int m1 = *max_element(mat[mid - 1].begin(), mat[mid - 1].end());
                int m2 = *max_element(mat[mid].begin(), mat[mid].end());
                if (m1 <= m2) {
                    for (int i = 0; i < mat[mid].size(); i++) {
                        if (m2 == mat[mid][i]) {
                            return {mid, i};
                        }
                    }
                } else {
                    right = mid - 1;
                }
            }
        }
        return {};
    }
};
// DAY2
/*
你有一大块巧克力，它由一些甜度不完全相同的小块组成。我们用数组 sweetness 来表示每一小块的甜度。

你打算和 K 名朋友一起分享这块巧克力，所以你需要将切割 K 次才能得到 K+1 块，每一块都由一些 连续 的小块组成。

为了表现出你的慷慨，你将会吃掉 总甜度最小 的一块，并将其余几块分给你的朋友们。

请找出一个最佳的切割策略，使得你所分得的巧克力 总甜度最大，并返回这个 最大总甜度。
1231
 */
class Solution {
public:
    int maximizeSweetness(vector<int>& sweetness, int k) {
        int left = 0, right = accumulate(sweetness.begin(), sweetness.end(), 0);
        auto check = [&](int mid) {
            int m = 0, n = 0;
            for (auto i : sweetness) {
                m += i;
                if (m >= mid) {
                    n++;
                    m = 0;
                }
            }
            // k+1块
            return n > k;
        };
        while (left < right) {
            int mid = left + (right - left + 1) / 2;
            if (check(mid)) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }
        return left;
    }
};
/*
给你一个数组 colors，里面有  1、2、 3 三种颜色。

我们需要在 colors 上进行一些查询操作 queries，其中每个待查项都由两个整数 i 和 c 组成。

现在请你帮忙设计一个算法，查找从索引 i 到具有目标颜色 c 的元素之间的最短距离。

如果不存在解决方案，请返回 -1。
1182
 */
class Solution {
public:
    vector<int> shortestDistanceColor(vector<int>& colors, vector<vector<int>>& queries) {
        vector<vector<int>> vec(4);
        for (int i = 0; i < colors.size(); i++) {
            vec[colors[i]].emplace_back(i);
        }
        vector<int> res;
        for (auto v : queries) {
            int m = v[1];
            if (vec[m].empty()) {
                res.emplace_back(-1);
                continue;
            }
            auto i = lower_bound(vec[m].begin(), vec[m].end(), v[0]) - vec[m].begin();
            if (i == 0) {
                res.emplace_back(vec[m][0] - v[0]);
            } else if (i == vec[m].size()) {
                res.emplace_back(v[0] - vec[m][i - 1]);
            } else {
                res.emplace_back(min(vec[m][i] - v[0], v[0] - vec[m][i - 1]));
            }
        }
        return res;
    }
};
// DAY3
/*
你是一名行政助理，手里有两位客户的空闲时间表：slots1 和 slots2，以及会议的预计持续时间 duration，请你为他们安排合适的会议时间。

「会议时间」是两位客户都有空参加，并且持续时间能够满足预计时间 duration 的 最早的时间间隔。

如果没有满足要求的会议时间，就请返回一个 空数组。

「空闲时间」的格式是 [start, end]，由开始时间 start 和结束时间 end 组成，表示从 start 开始，到 end 结束。

题目保证数据有效：同一个人的空闲时间不会出现交叠的情况，
也就是说，对于同一个人的两个空闲时间 [start1, end1] 和 [start2, end2]，要么 start1 > end2，要么 start2 > end1。
1229
 */
class Solution {
public:
    vector<int> minAvailableDuration(vector<vector<int>>& slots1, vector<vector<int>>& slots2, int duration) {
        sort(slots1.begin(), slots1.end());
        sort(slots2.begin(), slots2.end());
        for (auto i : slots1) {
            if (i[1] - i[0] < duration) {
                continue;
            }
            for (auto j : slots2) {
                if (j[1] - j[0] < duration) {
                    continue;
                }
                if (j[0] >= i[1]) {
                    break;
                }
                if (min(j[1], i[1]) - max(i[0], j[0]) >= duration) {
                    return {max(i[0], j[0]), max(i[0], j[0]) + duration};
                }
            }
        }
        return {};
    }
};
/*
给定一个包含 n + 1 个整数的数组 nums ，其数字都在 1 到 n 之间（包括 1 和 n），可知至少存在一个重复的整数。

假设 nums 只有 一个重复的整数 ，找出 这个重复的数 。

你设计的解决方案必须不修改数组 nums 且只用常量级 O(1) 的额外空间。
287
 */
// 不符合题意
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            int j = abs(nums[i]);
            if (nums[j] < 0) {
                return j;
            } else {
                nums[j] *= -1;
            }
        }
        return -1;
    }
};
// 超时
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] == nums[j]) {
                    return nums[i];
                }
            }
        }
        return -1;
    }
};
// 看成数组化的链表，使用快慢指针类似于142题
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = 0, quick = 0;
        do {
            slow = nums[slow];
            quick = nums[nums[quick]];
        } while (slow != quick);
        slow = 0;
        while (slow != quick) {
            slow = nums[slow];
            quick = nums[quick];
        }
        return slow;
    }
};
// 二分也可以，在1-n里面查找，根据小于mid数是否合理来排除,
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size(), left = 0, right = n;
        while (left < right) {
            int mid = left + (right - left) / 2, cnt = 0;
            for (int i : nums) {
                cnt += i <= mid;
            }
            //==是有问题的，因为并不是都是1-n所有数字，有可能缺！！！
            if (cnt == mid) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }
};
// DAY4
/*
给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
42
 */
/*
单调栈及其他方法……
 */
class Solution {
public:
    int trap(vector<int>& height) {
        stack<int> sk;
        int res = 0;
        for (int i = 0; i < height.size(); i++) {
            while (!sk.empty() && height[sk.top()] < height[i]) {
                int j = sk.top();
                sk.pop();
                if (sk.empty()) {
                    break;
                }
                int k = sk.top();
                int h = min(height[i], height[k]) - height[j];
                res += (i - k - 1) * h;
            }
            sk.emplace(i);
        }
        return res;
    }
};
/*
行程编码（Run-length encoding）是一种压缩算法，
能让一个含有许多段连续重复数字的整数类型数组 nums 以一个（通常更小的）二维数组 encoded 表示。
每个 encoded[i] = [vali, freqi] 表示 nums 中第 i 段重复数字，其中 vali 是该段重复数字，重复了 freqi 次。

    例如， nums = [1,1,1,2,2,2,2,2] 可表示称行程编码数组 encoded = [[1,3],[2,5]] 。对此数组的另一种读法是“三个 1 ，后面有五个 2 ”。

两个行程编码数组 encoded1 和 encoded2 的积可以按下列步骤计算：

    将 encoded1 和 encoded2 分别扩展成完整数组 nums1 和 nums2 。
    创建一个新的数组 prodNums ，长度为 nums1.length 并设 prodNums[i] = nums1[i] * nums2[i] 。
    将 prodNums 压缩成一个行程编码数组并返回之。

给定两个行程编码数组 encoded1 和 encoded2 ，分别表示完整数组 nums1 和 nums2 。nums1 和 nums2 的长度相同。
每一个 encoded1[i] = [vali, freqi] 表示 nums1 中的第 i 段，每一个 encoded2[j] = [valj, freqj] 表示 nums2 中的第 j 段。

返回 encoded1 和 encoded2 的乘积。

注：行程编码数组需压缩成可能的最小长度。

 */
class Solution {
public:
    vector<vector<int>> findRLEArray(vector<vector<int>>& encoded1, vector<vector<int>>& encoded2) {
        int m = encoded1.size(), n = encoded2.size(), i = 0, j = 0;
        vector<vector<int>> temp;
        while (i < m && j < n) {
            if (encoded1[i][1] == encoded2[j][1]) {
                temp.push_back({encoded1[i][0] * encoded2[j][0], encoded1[i][1]});
                i++;
                j++;
            } else if (encoded1[i][1] < encoded2[j][1]) {
                temp.push_back({encoded1[i][0] * encoded2[j][0], encoded1[i][1]});
                encoded2[j][1] -= encoded1[i][1];
                i++;
            } else {
                temp.push_back({encoded1[i][0] * encoded2[j][0], encoded2[j][1]});
                encoded1[i][1] -= encoded2[j][1];
                j++;
            }
        }
        vector<vector<int>> res;
        for (auto vec : temp) {
            if (res.empty()) {
                res.emplace_back(vec);
            } else if (vec[0] == res.back()[0]) {
                res.back()[1] += vec[1];
            } else {
                res.emplace_back(vec);
            }
        }
        return res;
    }
};
// DAY5
/*
给定一个字符串 s ，找出 至多 包含两个不同字符的最长子串 t ，并返回该子串的长度。
159
 */
class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        map<char, int> wind;
        int left = 0, right = 0, n = s.size(), res = 0;
        while (right < n) {
            while (right < n && wind.size() <= 2) {
                if (wind.count(s[right])) {
                    wind[s[right]]++;
                } else if (wind.size() == 2) {
                    break;
                } else {
                    wind[s[right]]++;
                }
                right++;
            }
            res = max(right - left, res);
            // cout<<left<<" "<<right<<endl;
            while (left < right) {
                if (--wind[s[left]] == 0) {
                    wind.erase(s[left++]);
                    break;
                }
                left++;
            }
        }
        res = max(right - left - 1, res);
        return res;
    }
};
/*
给定一个字符串 s ，找出 至多 包含 k 个不同字符的最长子串 T。
340
 */
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        if (k == 0) {
            return 0;
        }
        map<char, int> wind;
        int left = 0, right = 0, n = s.size(), res = 0;
        while (right < n) {
            while (right < n && wind.size() <= k) {
                if (wind.count(s[right])) {
                    wind[s[right]]++;
                } else if (wind.size() == k) {
                    break;
                } else {
                    wind[s[right]]++;
                }
                right++;
            }
            res = max(right - left, res);
            // cout<<left<<" "<<right<<endl;
            while (left < right) {
                if (--wind[s[left]] == 0) {
                    wind.erase(s[left++]);
                    break;
                }
                left++;
            }
        }
        res = max(right - left - 1, res);
        return res;
    }
};
// DAY6
/*
给定一个由若干 0 和 1 组成的数组 A，我们最多可以将 K 个值从 0 变成 1 。

返回仅包含 1 的最长（连续）子数组的长度。
1004
 */
class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int z = 0, n = nums.size(), left = 0, right = 0, res = 0;
        while (right < n) {
            if (nums[right++] == 0) {
                z++;
            }
            while (z > k && left < right) {
                if (nums[left++] == 0) {
                    z--;
                }
            }
            res = max(right - left, res);
        }
        return res;
    }
};
/*
给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。
你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。

返回滑动窗口中的最大值。
239
 */
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> mdq;
        vector<int> res;
        for (int i = 0; i < nums.size(); i++) {
            while (!mdq.empty() && i - k >= mdq.front()) {
                mdq.pop_front();
            }
            while (!mdq.empty() && nums[i] > nums[mdq.back()]) {
                mdq.pop_back();
            }
            mdq.emplace_back(i);
            if (i < k - 1) {
                continue;
            } else {
                res.emplace_back(nums[mdq.front()]);
            }
        }
        return res;
    }
};
/*
给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。
76
 */
class Solution {
public:
    string minWindow(string s, string t) {
        map<char, int> need, wind;
        for (auto i : t) {
            need[i]++;
        }
        int n = s.size(), left = 0, right = 0, index = 0;
        int k = -1, len = n + 1;
        while (right < n) {
            while (right < n) {
                char c = s[right++];
                if (need.count(c) && ++wind[c] == need[c]) {
                    index++;
                }
                if (index == need.size()) {
                    break;
                }
            }
            while (left < right && index == need.size()) {
                if (right - left < len) {
                    len = right - left;
                    k = left;
                }
                char c = s[left++];
                if (need.count(c) && wind[c]-- == need[c]) {
                    index--;
                }
                if (index < need.size()) {
                    break;
                }
            }
        }
        return k == -1 ? "" : s.substr(k, len);
    }
};
/*
你被给定一个 m × n 的二维网格 rooms ，网格中有以下三种可能的初始化值：

    -1 表示墙或是障碍物
    0 表示一扇门
    INF 无限表示一个空的房间。然后，我们用 231 - 1 = 2147483647 代表 INF。你可以认为通往门的距离总是小于 2147483647 的。

你要给每个空房间位上填上该房间到 最近门的距离 ，如果无法到达门，则填 INF 即可。
286
 */
class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        int m = rooms.size(), n = rooms[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (rooms[i][j] == 0) {
                    dfs(i, j, m, n, 0, rooms);
                }
            }
        }
    }
    vector<vector<int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    void dfs(int i, int j, int m, int n, int len, vector<vector<int>>& rooms) {
        if (i < 0 || j < 0 || i >= m || j >= n || rooms[i][j] == -1) {
            return;
        }
        if (rooms[i][j] != 0 && rooms[i][j] <= len || rooms[i][j] == 0 && len != 0) {
            return;
        }
        rooms[i][j] = len;
        for (auto vec : dir) {
            dfs(i + vec[0], j + vec[1], m, n, len + 1, rooms);
        }
    }
};
// 多点BFS！！！！！
class Solution {
public:
    vector<vector<int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    void wallsAndGates(vector<vector<int>>& rooms) {
        int m = rooms.size(), n = rooms[0].size();
        queue<pair<int, int>> mq;
        int l = 0;
        vector<vector<int>> visit(m, vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (rooms[i][j] == 0) {
                    mq.emplace(i, j);
                }
            }
        }
        while (!mq.empty()) {
            int len = mq.size();
            for (int i = 0; i < len; i++) {
                auto k = mq.front();
                mq.pop();
                rooms[k.first][k.second] = l;
                for (auto vec : dir) {
                    int x = k.first + vec[0], y = k.second + vec[1];
                    if (x < 0 || y < 0 || x >= m || y >= n || visit[x][y] == 1 || rooms[x][y] == -1 || rooms[x][y] == 0) {
                        continue;
                    }
                    visit[x][y] = 1;
                    mq.emplace(x, y);
                }
            }
            l++;
        }
    }
};
/*
给定一个 m x n 的非负整数矩阵来表示一片大陆上各个单元格的高度。“太平洋”处于大陆的左边界和上边界，而“大西洋”处于大陆的右边界和下边界。

规定水流只能按照上、下、左、右四个方向流动，且只能从高到低或者在同等高度上流动。

请找出那些水流既可以流动到“太平洋”，又能流动到“大西洋”的陆地单元的坐标。
417
 */
class Solution {
public:
    vector<vector<int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    vector<vector<int>> res;
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        queue<pair<int, int>> mq;
        int m = heights.size(), n = heights[0].size();
        vector<vector<int>> copy = heights;
        for (int i = 0; i < m; i++) {
            dfs(i, 0, m, n, heights, -1, copy);
        }
        for (int j = 0; j < n; j++) {
            dfs(0, j, m, n, heights, -1, copy);
        }
        for (int i = 0; i < m; i++) {
            dfs(i, n - 1, m, n, heights, -2, copy);
        }
        for (int j = 0; j < n; j++) {
            dfs(m - 1, j, m, n, heights, -2, copy);
        }
        return res;
    }
    void dfs(int i, int j, int m, int n, vector<vector<int>>& heights, int index, vector<vector<int>>& copy) {
        if (heights[i][j] < 0 && heights[i][j] != index) {
            res.emplace_back(vector<int>{i, j});
        }
        heights[i][j] = index;
        for (auto vec : dir) {
            int x = i + vec[0], y = j + vec[1];
            if (x < 0 || y < 0 || x >= m || y >= n || heights[x][y] == index || copy[x][y] < copy[i][j]) {
                continue;
            }
            dfs(x, y, m, n, heights, index, copy);
        }
    }
};
// DAY8
/*
二叉树中，如果一个节点是其父节点的唯一子节点，则称这样的节点为 “独生节点” 。二叉树的根节点不会是独生节点，因为它没有父节点。

给定一棵二叉树的根节点 root ，返回树中 所有的独生节点的值所构成的数组 。数组的顺序 不限 。
1469
 */
class Solution {
public:
    vector<int> getLonelyNodes(TreeNode* root) {
        queue<TreeNode*> mq;
        mq.emplace(root);
        vector<int> res;
        while (!mq.empty()) {
            auto k = mq.front();
            mq.pop();
            if (k == nullptr) {
                continue;
            }
            if (k->left == nullptr && k->right) {
                res.emplace_back(k->right->val);
            }
            if (k->right == nullptr && k->left) {
                res.emplace_back(k->left->val);
            }
            mq.emplace(k->left);
            mq.emplace(k->right);
        }
        return res;
    }
};
/*
系统中存在 n 个进程，形成一个有根树结构。给你两个整数数组 pid 和 ppid ，
其中 pid[i] 是第 i 个进程的 ID ，
ppid[i] 是第 i 个进程的父进程 ID 。

每一个进程只有 一个父进程 ，但是可能会有 一个或者多个子进程 。只有一个进程的 ppid[i] = 0 ，意味着这个进程 没有父进程 。

当一个进程 被杀掉 的时候，它所有的子进程和后代进程都要被杀掉。

给你一个整数 kill 表示要杀掉​​进程的 ID ，返回杀掉该进程后的所有进程 ID 的列表。可以按 任意顺序 返回答案。
582
 */
class Solution {
public:
    vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill) {
        map<int, vector<int>> mp;
        for (int i = 0; i < ppid.size(); i++) {
            mp[ppid[i]].emplace_back(pid[i]);
        }
        queue<int> mq;
        mq.emplace(kill);
        vector<int> res;
        while (!mq.empty()) {
            auto k = mq.front();
            mq.pop();
            res.emplace_back(k);
            for (auto i : mp[k]) {
                mq.emplace(i);
            }
        }
        return res;
    }
};
// DAY9
/*
给定一个二叉树（具有根结点 root）， 一个目标结点 target ，和一个整数值 K 。

返回到目标结点 target 距离为 K 的所有结点的值的列表。 答案可以以任何顺序返回。
863
 */
class Solution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        map<TreeNode*, TreeNode*> parent;
        queue<TreeNode*> mq;
        mq.emplace(root);
        while (!mq.empty()) {
            auto node = mq.front();
            mq.pop();
            if (node->left) {
                parent[node->left] = node;
                mq.emplace(node->left);
            }
            if (node->right) {
                parent[node->right] = node;
                mq.emplace(node->right);
            }
        }
        vector<int> res;
        set<TreeNode*> visit;
        mq.emplace(target);
        visit.emplace(target);
        while (!mq.empty()) {
            int len = mq.size();
            for (int i = 0; i < len; i++) {
                auto node = mq.front();
                if (k == 0) {
                    res.emplace_back(node->val);
                }
                mq.pop();
                if (node->left && !visit.count(node->left)) {
                    mq.emplace(node->left);
                }
                if (node->right && !visit.count(node->right)) {
                    mq.emplace(node->right);
                }
                if (parent.count(node) && !visit.count(parent[node])) {
                    mq.emplace(parent[node]);
                }
            }
            k--;
        }
        return res;
    }
};
/*
你有一个带有四个圆形拨轮的转盘锁。每个拨轮都有10个数字： '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' 。
每个拨轮可以自由旋转：例如把 '9' 变为 '0'，'0' 变为 '9' 。每次旋转都只能旋转一个拨轮的一位数字。

锁的初始数字为 '0000' ，一个代表四个拨轮的数字的字符串。

列表 deadends 包含了一组死亡数字，一旦拨轮的数字和列表里的任何一个元素相同，这个锁将会被永久锁定，无法再被旋转。

字符串 target 代表可以解锁的数字，你需要给出解锁需要的最小旋转次数，如果无论如何不能解锁，返回 -1 。
752
 */
class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        queue<string> mq;
        set<string> visit;
        int res = 0;
        for (auto s : deadends) {
            visit.emplace(s);
        }
        if (!visit.count("0000")) {
            mq.push("0000");
            visit.emplace("0000");
        }
        while (!mq.empty()) {
            int len = mq.size();
            for (int i = 0; i < len; i++) {
                auto str = mq.front();
                if (str == target) {
                    return res;
                }
                mq.pop();
                for (int i = 0; i < 4; i++) {
                    string temp = str;
                    temp[i] = (str[i] - '0' + 1) % 10 + '0';
                    if (!visit.count(temp)) {
                        mq.emplace(temp);
                        visit.emplace(temp);
                    }
                    temp[i] = (str[i] - '0' + 9) % 10 + '0';
                    if (!visit.count(temp)) {
                        mq.emplace(temp);
                        visit.emplace(temp);
                    }
                }
            }
            res++;
        }
        return -1;
    }
};
// DAY10
/*
用以太网线缆将 n 台计算机连接成一个网络，计算机的编号从 0 到 n-1。
线缆用 connections 表示，其中 connections[i] = [a, b] 连接了计算机 a 和 b。

网络中的任何一台计算机都可以通过网络直接或者间接访问同一个网络中其他任意一台计算机。

给你这个计算机网络的初始布线 connections，你可以拔开任意两台直连计算机之间的线缆，并用它连接一对未直连的计算机。
请你计算并返回使所有计算机都连通所需的最少操作次数。如果不可能，则返回 -1 。
1319
 */
// 以前是用并查集做的，这次用dfs
class Solution {
public:
    unordered_map<int, vector<int>> ump;
    int makeConnected(int n, vector<vector<int>>& connections) {
        if (n > connections.size() + 1) {
            return -1;
        }
        for (auto vec : connections) {
            ump[vec[0]].emplace_back(vec[1]);
            ump[vec[1]].emplace_back(vec[0]);
        }
        int res = 0;
        vector<int> visit(n, 0);
        for (int i = 0; i < n; i++) {
            if (visit[i] == 1) {
                continue;
            } else {
                dfs(i, visit);
                res++;
            }
        }
        return res - 1;
    }
    void dfs(int i, vector<int>& visit) {
        if (visit[i] == 1) {
            return;
        }
        visit[i] = 1;
        for (auto j : ump[i]) {
            dfs(j, visit);
        }
    }
};
/*
给你一个 m x n 的网格图 grid 。 grid 中每个格子都有一个数字，对应着从该格子出发下一步走的方向。 grid[i][j] 中的数字可能为以下几种情况：

    1 ，下一步往右走，也就是你会从 grid[i][j] 走到 grid[i][j + 1]
    2 ，下一步往左走，也就是你会从 grid[i][j] 走到 grid[i][j - 1]
    3 ，下一步往下走，也就是你会从 grid[i][j] 走到 grid[i + 1][j]
    4 ，下一步往上走，也就是你会从 grid[i][j] 走到 grid[i - 1][j]

注意网格图中可能会有 无效数字 ，因为它们可能指向 grid 以外的区域。

一开始，你会从最左上角的格子 (0,0) 出发。
我们定义一条 有效路径 为从格子 (0,0) 出发，每一步都顺着数字对应方向走，最终在最右下角的格子 (m - 1, n - 1) 结束的路径。
有效路径 不需要是最短路径 。

你可以花费 cost = 1 的代价修改一个格子中的数字，但每个格子中的数字 只能修改一次 。

请你返回让网格图至少有一条有效路径的最小代价。
1368
 */
using pii = pair<int, int>;
using ppi = pair<pii, int>;
vector<vector<int>> dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        auto cmp = [](ppi a, ppi b) {
            return a.second > b.second;
        };
        auto hash = [](pii a) {
            return a.first ^ a.second;
        };
        priority_queue<ppi, vector<ppi>, decltype(cmp)> mpq(cmp);
        mpq.push({{0, 0}, 0});
        vector<vector<int>> visit(m, vector<int>(n, 0));
        while (!mpq.empty()) {
            auto node = mpq.top();
            mpq.pop();
            if (visit[node.first.first][node.first.second] == 1) {
                continue;
            }
            visit[node.first.first][node.first.second] = 1;
            if (node.first == pii{m - 1, n - 1}) {
                return node.second;
            }
            // cout<<node.first.first<<" "<<node.first.second<<" "<<node.second<<endl;
            for (int i = 0; i < 4; i++) {
                int j = dir[i][0] + node.first.first;
                int k = dir[i][1] + node.first.second;
                if (j < 0 || k < 0 || j >= m || k >= n || visit[j][k] == 1) {
                    continue;
                }
                int w = node.second;
                if (grid[node.first.first][node.first.second] != i + 1) {
                    w++;
                }
                mpq.push({{j, k}, w});
            }
        }
        return -1;
    }
};
/*
力扣数据中心有 n 台服务器，分别按从 0 到 n-1 的方式进行了编号。

它们之间以「服务器到服务器」点对点的形式相互连接组成了一个内部集群，其中连接 connections 是无向的。

从形式上讲，connections[i] = [a, b] 表示服务器 a 和 b 之间形成连接。任何服务器都可以直接或者间接地通过网络到达任何其他服务器。

「关键连接」是在该集群中的重要连接，也就是说，假如我们将它移除，便会导致某些服务器无法访问其他服务器。

请你以任意顺序返回该集群内的所有 「关键连接」。
1192
 */
// 最小生成树？----不是
// 这里用k算法
using pii = pair<int, int>;
class Solution {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        auto cmp = [](pii a, pii b) {
            return a.second > b.second;
        };
        priority_queue<pii, vector<pii>, decltype(cmp)> mpq(cmp);
        mpq.emplace(0, 0);
    }
};
/*
整数可以被看作是其因子的乘积。
254
 */
class Solution {
public:
    vector<vector<int>> res;
    vector<int> temp;
    vector<vector<int>> getFactors(int n) {
    }
    void dfs(vector<int> temp) {
        if (temp.size() > 1) {
            res.emplace_back(temp);
        }
        for (int i = 0; i < temp.size(); i++) {
            if (i >= 1 && temp[i] == temp[i - 1]) {
                continue;
            }
            for (int j = 2; j < temp[i] / 2; j++) {
                if (temp[i] % j == 0) {
                    temp.emplace_back(temp[i]);
                    temp.emplace_back(j);
                }
            }
        }
    }
};