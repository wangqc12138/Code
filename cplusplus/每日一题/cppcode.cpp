#include "head.h"
/*
给你两个字符串 a 和 b ，它们长度相同。请你选择一个下标，将两个字符串都在 相同的下标 分割开。
由 a 可以得到两个字符串： aprefix 和 asuffix ，满足 a = aprefix + asuffix ，同理，由 b 可以得到两个字符串 bprefix 和 bsuffix ，满足 b = bprefix + bsuffix 。
请你判断 aprefix + bsuffix 或者 bprefix + asuffix 能否构成回文串。

当你将一个字符串 s 分割成 sprefix 和 ssuffix 时， ssuffix 或者 sprefix 可以为空。比方说， s = "abc" 那么 "" + "abc" ， "a" + "bc" ， "ab" + "c" 和 "abc" + "" 都是合法分割。

如果 能构成回文字符串 ，那么请返回 true，否则返回 false 。

注意， x + y 表示连接字符串 x 和 y 。
T1616
思路：
双指针从两端开始遍历
 */
class Solution {
public:
    bool checkPalindromeFormation(string a, string b) {
        int n = a.size(), i = 0, j = n - 1;
        bool aa = false, bb = false, f1 = true, f2 = true;
        while (i < j) {
            if (f1) {
                if (aa == false) {
                    if (a[i] != b[j] && a[i] == a[j]) {
                        aa = true;
                    }
                    if (a[i] != b[j] && a[i] != a[j]) {
                        f1 = false;
                    }
                }
                if (aa == true && a[i] != a[j]) {
                    f1 = false;
                }
            }
            if (f2) {
                if (bb == false) {
                    if (b[i] != a[j] && b[i] == b[j]) {
                        bb = true;
                    }
                    if (b[i] != a[j] && b[i] != b[j]) {
                        f2 = false;
                    }
                }
                if (bb == true && b[i] != b[j]) {
                    f2 = false;
                }
            }
            if (!f1 && !f2) {
                return false;
            }
            i++;
            j--;
        }
        return true;
    }
};
/*
给定正整数 n，返回在 [1, n] 范围内具有 至少 1 位 重复数字的正整数的个数。
T1012
20230320
// 数位DP，学一下
 */
// 超时
class Solution {
public:
    int numDupDigitsAtMostN(int n) {
        int res = 0;
        for (int i = 1; i <= n; i++) {
            string str = to_string(i);
            if (set<char>(str.begin(), str.end()).size() != str.size()) {
                res++;
            }
        }
        return res;
    }
};
class Solution {
public:
    int numDupDigitsAtMostN(int n) {
        string num = to_string(n);
        int len = num.size(), dp[len + 1][1 << 10];
        memset(dp, -1, sizeof(dp));
        function<int(int, int, int, int)> f = [&](int pos, int mask, bool limit, bool isnum) -> int {
            if (pos >= len) {
                return isnum;
            }
            if (!limit && isnum && dp[pos][mask] != -1) {
                return dp[pos][mask];
            }
            int up = limit ? (num[pos] - '0') : 9;
            int res = 0;
            // 如果都是前导0，则跳过
            if (!isnum) {
                res = f(pos + 1, mask, false, false);
            }
            for (int i = !isnum; i <= up; i++) {
                if (((mask >> i) & 1) == 0) {
                    res += f(pos + 1, mask | (1 << i), limit && i == num[pos] - '0', true);
                }
            }
            if (!limit && isnum) {
                dp[pos][mask] = res;
            }
            return res;
        };
        return n - f(0, 0, true, false);
    }
};
/*
给你一个四舍五入到两位小数的非负浮点数 celsius 来表示温度，以 摄氏度（Celsius）为单位。

你需要将摄氏度转换为 开氏度（Kelvin）和 华氏度（Fahrenheit），并以数组 ans = [kelvin, fahrenheit] 的形式返回结果。

返回数组 ans 。与实际答案误差不超过 10-5 的会视为正确答案。
T2469
纯粹模拟，没什么好说的，垃圾！
 */
class Solution {
public:
    vector<double> convertTemperature(double celsius) {
        return {celsius + 273.15, celsius * 1.8 + 32};
    }
};
/*
假设你是球队的经理。对于即将到来的锦标赛，你想组合一支总体得分最高的球队。球队的得分是球队中所有球员的分数 总和 。

然而，球队中的矛盾会限制球员的发挥，所以必须选出一支 没有矛盾 的球队。如果一名年龄较小球员的分数 严格大于 一名年龄较大的球员，则存在矛盾。同龄球员之间不会发生矛盾。

给你两个列表 scores 和 ages，其中每组 scores[i] 和 ages[i] 表示第 i 名球员的分数和年龄。请你返回 所有可能的无矛盾球队中得分最高那支的分数 。
T1626
 */
class Solution {
public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int n = scores.size(), res = 0;
        vector<int> index(n);
        iota(index.begin(), index.end(), 0);
        sort(index.begin(), index.end(), [&](int i, int j) { return ages[i] < ages[j] || ages[i] == ages[j] && scores[i] <= scores[j]; });
        vector<int> dp(n, 0);
        for (int i = 0; i < n; i++) {
            for (int j = i; j >= 0; j--) {
                if (scores[index[i]] >= scores[index[j]] || ages[index[i]] == ages[index[j]]) {
                    dp[index[i]] = max(dp[index[i]], dp[index[j]] + scores[index[i]]);
                }
            }
            res = max(res, dp[index[i]]);
        }
        return res;
    }
};
/*
如果一个数列由至少两个元素组成，且每两个连续元素之间的差值都相同，那么这个序列就是 等差数列 。
更正式地，数列 s 是等差数列，只需要满足：对于每个有效的 i ， s[i+1] - s[i] == s[1] - s[0] 都成立。
给你一个由 n 个整数组成的数组 nums，和两个由 m 个整数组成的数组 l 和 r，后两个数组表示 m 组范围查询，其中第 i 个查询对应范围 [l[i], r[i]] 。
所有数组的下标都是 从 0 开始 的。

返回 boolean 元素构成的答案列表 answer 。
如果子数组 nums[l[i]], nums[l[i]+1], ... , nums[r[i]] 可以 重新排列 形成 等差数列 ，answer[i] 的值就是 true；否则answer[i] 的值就是 false 。
T1630
 */
// 错误，这个是判断不重新排列的！
class Solution {
public:
    vector<bool> checkArithmeticSubarrays(vector<int>& nums, vector<int>& l, vector<int>& r) {
        int pre = 0, n = nums.size();
        vector<int> L, R;
        for (int i = 1; i < n; i++) {
            if (nums[i] - nums[i - 1] != nums[pre + 1] - nums[pre]) {
                L.emplace_back(pre);
                R.emplace_back(i - 1);
                pre = i - 1;
            }
        }
        L.emplace_back(pre);
        R.emplace_back(n - 1);
        int len = l.size();
        vector<bool> res(len);
        for (int i = 0; i < len; i++) {
            int t1 = lower_bound(L.begin(), L.end(), l[i]) - L.begin();
            int t2 = upper_bound(R.begin(), R.end(), r[i]) - R.begin() - 1;
            res[i] = t1 == t2;
        }
        return res;
    }
};
/*
直接暴力
没啥说法
 */
class Solution {
public:
    vector<bool> checkArithmeticSubarrays(vector<int>& nums, vector<int>& l, vector<int>& r) {
        int len = l.size();
        vector<bool> res(len, true);
        for (int i = 0; i < len; i++) {
            vector<int> temp = vector<int>(nums.begin() + l[i], nums.begin() + r[i] + 1);
            sort(temp.begin(), temp.end());
            for (int j = 2; j < temp.size(); j++) {
                if (temp[j] - temp[j - 1] != temp[1] - temp[0]) {
                    res[i] = false;
                    break;
                }
            }
        }
        return res;
    }
};
/*
设计一个算法：接收一个字符流，并检查这些字符的后缀是否是字符串数组 words 中的一个字符串。

例如，words = ["abc", "xyz"] 且字符流中逐个依次加入 4 个字符 'a'、'x'、'y' 和 'z' ，你所设计的算法应当可以检测到 "axyz" 的后缀 "xyz" 与 words 中的字符串 "xyz" 匹配。

按下述要求实现 StreamChecker 类：

    StreamChecker(String[] words) ：构造函数，用字符串数组 words 初始化数据结构。
    boolean query(char letter)：从字符流中接收一个新字符，如果字符流中的任一非空后缀能匹配 words 中的某一字符串，返回 true ；否则，返回 false。
1032
 */
class trie {
public:
    trie() {
        fill(next, next + 26, nullptr);
        end = false;
    }
    void insert(const string& str) {
        trie* root = this;
        for (auto c : str) {
            if (root->next[c - 'a'] == nullptr) {
                root->next[c - 'a'] = new trie();
            }
            root = root->next[c - 'a'];
        }
        root->end = true;
    }
    trie* search(char c) {
        return this->next[c - 'a'];
    }
    bool isend() {
        return this->end;
    }

private:
    trie* next[26];
    bool end;
};
class StreamChecker {
public:
    StreamChecker(vector<string>& words) {
        root = new trie();
        for (auto str : words) {
            root->insert(str);
        }
        now.clear();
        now.emplace_back(root);
    }

    bool query(char letter) {
        vector<trie*> temp;
        bool res = false;
        for (auto t : now) {
            auto child = t->search(letter);
            if (child) {
                temp.emplace_back(child);
                res |= child->isend();
            }
        }
        auto child = root->search(letter);
        if (child) {
            temp.emplace_back(child);
            res |= child->isend();
        }
        now = temp;
        return res;
    }

private:
    trie* root;
    vector<trie*> now;
};

/*
给你一个整数数组 arr ，请你删除一个子数组（可以为空），使得 arr 中剩下的元素是 非递减 的。

一个子数组指的是原数组中连续的一个子序列。

请你返回满足题目要求的最短子数组的长度。
T1574
 */
class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr) {
        int n = arr.size(), res = n;
        vector<int> head, tail;
        for (int i = 0; i < n; i++) {
            if (head.empty() || arr[i] >= head.back()) {
                head.emplace_back(arr[i]);
            } else {
                break;
            }
        }
        if (head.size() == n) {
            return 0;
        }
        for (int i = n - 1; i >= 0; i--) {
            if (tail.empty() || arr[i] <= tail.back()) {
                tail.emplace_back(arr[i]);
            } else {
                break;
            }
        }
        res = n - min(head.size(), tail.size());
        for (int i = head.size() - 1; i >= 0; i--) {
            for (int j = tail.size() - 1; j >= 0; j--) {
                if (head[i] > tail[j]) {
                    continue;
                } else {
                    res = min(res, n - i - j - 2);
                    break;
                }
            }
        }
        return res;
    }
};
/*
给你两个字符串 s 和 t ，请你找出 s 中的非空子串的数目，这些子串满足替换 一个不同字符 以后，是 t 串的子串。
换言之，请你找到 s 和 t 串中 恰好 只有一个字符不同的子字符串对的数目。

比方说， "compute" and "computa" 只有一个字符不同： 'e'/'a' ，所以这一对子字符串会给答案加 1 。

请你返回满足上述条件的不同子字符串对数目。

一个 子字符串 是一个字符串中连续的字符。
T1638
 */
class Solution {
public:
    int countSubstrings(string s, string t) {
        int m = s.size(), n = t.size(), res = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int k = i, l = j;
                int flag = 0;
                while (l < n && k < m) {
                    if (s[k] != t[l] && flag == 0) {
                        res++;
                        flag = 1;
                    } else if (s[k] == t[l] && flag == 1) {
                        res++;
                    } else if (s[k] != t[l] && flag == 1) {
                        break;
                    }
                    k++;
                    l++;
                }
            }
        }
        return res;
    }
};
// dp
class Solution {
public:
    int countSubstrings(string s, string t) {
        int m = s.size(), n = t.size();
        int dp[m][n][2];
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (s[i] == t[j]) {
                    dp[i][j][0] = (i > 0 && j > 0 ? dp[i - 1][j - 1][0] : 0) + 1;
                    dp[i][j][1] = (i > 0 && j > 0 ? dp[i - 1][j - 1][1] : 0) + 1;
                } else {
                    dp[i][j][1] += (i > 0 && j > 0 ? dp[i - 1][j - 1][0] : 0) + 1;
                    dp[i][j][1] += (i > 0 && j > 0 ? dp[i - 1][j - 1][1] : 0);
                }
                cout << dp[i][j][0] << "+" << dp[i][j][1] << " ";
            }
            cout << endl;
        }
        return dp[m - 1][n - 1][1];
    }
};
/*
给你一个整数 n，请返回长度为 n 、仅由元音 (a, e, i, o, u) 组成且按 字典序排列 的字符串数量。

字符串 s 按 字典序排列 需要满足：对于所有有效的 i，s[i] 在字母表中的位置总是与 s[i+1] 相同或在 s[i+1] 之前。
T1641
 */
class Solution {
public:
    int countVowelStrings(int n) {
        vector<vector<int>> dp(n, vector<int>(5, -1));
        function<int(int, int)> f = [&](int pos, int now) -> int {
            if (pos >= n) {
                return 1;
            }
            if (dp[pos][now] != -1) {
                return dp[pos][now];
            }
            int res = 0;
            for (int i = now; i < 5; i++) {
                res += f(pos + 1, i);
            }
            dp[pos][now] = res;
            return res;
        };
        return f(0, 0);
    }
};
// dp
class Solution {
public:
    int countVowelStrings(int n) {
        vector<int> dp(5, 1);
        int s = 0;
        for (int i = 1; i < n; i++) {
            s = 0;
            for (int j = 0; j < 5; j++) {
                s += dp[j];
                dp[j] = s;
            }
        }
        return s;
    }
};
/*
有 N 堆石头排成一排，第 i 堆中有 stones[i] 块石头。

每次移动（move）需要将连续的 K 堆石头合并为一堆，而这个移动的成本为这 K 堆石头的总数。

找出把所有石头合并成一堆的最低成本。如果不可能，返回 -1 。
T1000
 */
class Solution {
public:
    int mergeStones(vector<int>& stones, int k) {
        int n = stones.size();
        vector<int> sum(n);
        partial_sum(stones.begin(), stones.end(), sum.begin());
    }
};
/*
给你一个整数 n ，以二进制字符串的形式返回该整数的 负二进制（base -2）表示。

注意，除非字符串就是 "0"，否则返回的字符串中不能含有前导零。
T1017
 */
// 超时
class Solution {
public:
    string baseNeg2(int n) {
        map<string, int> mp;
        mp["1"] = 1;
        mp["0"] = 0;
        while (!mp.empty()) {
            map<string, int> temp;
            for (auto& [x, y] : mp) {
                if (y == n) {
                    return x;
                }
                string s1 = "0" + x;
                int n1 = y;
                string s2 = "1" + x;
                int n2 = y + (s2.size() % 2 ? pow(2, s2.size() - 1) : pow(-2, s2.size() - 1));
                temp[s1] = n1;
                temp[s2] = n2;
            }
            mp = temp;
        }
        return "";
    }
};
class Solution {
public:
    string baseNeg2(int n) {
        if (!n) {
            return "0";
        }
        vector<int> bits(32);
        int index = 0;
        while (n) {
            bits[index++] = n % 2;
            n /= 2;
        }
        for (int i = 0; i < 32; i++) {
            if (bits[i] == 2) {
                bits[i] = 0;
                bits[i + 1]++;
            }
            if (bits[i] == 1 && i % 2) {
                bits[i + 1]++;
            }
        }
        string res = "";
        for (int i = 31; i >= 0; i--) {
            if (res == "" && bits[i] == 0) {
                continue;
            } else {
                res += to_string(bits[i]);
            }
        }
        return res;
    }
};
// 让余数为非负数！
class Solution {
public:
    string baseNeg2(int n) {
        if (!n) {
            return "0";
        }
        return help(n, -2);
    }
    string help(int n, int x) {
        string res = "";
        while (n) {
            int remain = n % x;
            int q = n / x;
            if (remain < 0) {
                n = q + 1;
                remain -= x;
            } else {
                n = q;
            }
            res += to_string(remain);
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

/*
在一个长度 无限 的数轴上，第 i 颗石子的位置为 stones[i]。如果一颗石子的位置最小/最大，那么该石子被称作 端点石子 。

每个回合，你可以将一颗端点石子拿起并移动到一个未占用的位置，使得该石子不再是一颗端点石子。

值得注意的是，如果石子像 stones = [1,2,5] 这样，你将 无法 移动位于位置 5 的端点石子，因为无论将它移动到任何位置（例如 0 或 3），该石子都仍然会是端点石子。

当你无法进行任何移动时，即，这些石子的位置连续时，游戏结束。

要使游戏结束，你可以执行的最小和最大移动次数分别是多少？ 以长度为 2 的数组形式返回答案：answer = [minimum_moves, maximum_moves] 。
T1040
 */
class Solution {
public:
    vector<int> numMovesStonesII(vector<int>& stones) {
    }
};
/*
给定一个长度为 n 的链表 head

对于列表中的每个节点，查找下一个 更大节点 的值。也就是说，对于每个节点，找到它旁边的第一个节点的值，这个节点的值 严格大于 它的值。

返回一个整数数组 answer ，其中 answer[i] 是第 i 个节点( 从1开始 )的下一个更大的节点的值。如果第 i 个节点没有下一个更大的节点，设置 answer[i] = 0 。
T1019
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<int> nextLargerNodes(ListNode* head) {
        unordered_map<int, int> ump;
        stack<int> sk;
        int index = 0;
        vector<int> res;
        while (head) {
            while (!sk.empty() && head->val > ump[sk.top()]) {
                res[sk.top()] = head->val;
                sk.pop();
            }
            sk.emplace(index);
            ump[index++] = head->val;
            res.emplace_back(0);
            head = head->next;
        }
        return res;
    }
};
/*
在无限的平面上，机器人最初位于 (0, 0) 处，面朝北方。注意:

    北方向 是y轴的正方向。
    南方向 是y轴的负方向。
    东方向 是x轴的正方向。
    西方向 是x轴的负方向。

机器人可以接受下列三条指令之一：

    "G"：直走 1 个单位
    "L"：左转 90 度
    "R"：右转 90 度

机器人按顺序执行指令 instructions，并一直重复它们。

只有在平面中存在环使得机器人永远无法离开时，返回 true。否则，返回 false。
T1041
 */
class Solution {
public:
    bool isRobotBounded(string instructions) {
        pair<int, int> now;
        int dir = 0;
        for (int i = 0; i < 4; i++) {
            for (auto c : instructions) {
                if (c == 'G') {
                    if (dir == 0) {
                        now.first++;
                    } else if (dir == 1) {
                        now.second++;
                    } else if (dir == 2) {
                        now.first--;
                    } else {
                        now.second--;
                    }
                } else if (c == 'L') {
                    if (++dir == 4) {
                        dir = 0;
                    }
                } else {
                    if (--dir == -1) {
                        dir = 3;
                    }
                }
            }
        }
        return now == pair<int, int>{0, 0} && dir == 0;
    }
};
/*
如果我们可以将小写字母插入模式串 pattern 得到待查询项 query，那么待查询项与给定模式串匹配。（我们可以在任何位置插入每个字符，也可以插入 0 个字符。）

给定待查询列表 queries，和模式串 pattern，返回由布尔值组成的答案列表 answer。
只有在待查项 queries[i] 与模式串 pattern 匹配时， answer[i] 才为 true，否则为 false。
1023
 */
class Solution {
public:
    vector<bool> camelMatch(vector<string>& queries, string pattern) {
        vector<bool> res;
        for (auto q : queries) {
            int i = 0, j = 0;
            bool flag = true;
            while (i < q.size() && j < pattern.size()) {
                if (pattern[j] == q[i]) {
                    i++;
                    j++;
                } else {
                    if (q[i] >= 'A' && q[i] <= 'Z') {
                        flag = false;
                        break;
                    }
                    i++;
                }
            }
            flag = j == pattern.size();
            if (j == pattern.size()) {
                for (; i < q.size(); i++) {
                    if (q[i] >= 'A' && q[i] <= 'Z') {
                        flag = false;
                        break;
                    }
                }
            }
            res.emplace_back(flag);
        }
        return res;
    }
};
// 正则
class Solution {
public:
    vector<bool> camelMatch(vector<string>& queries, string pattern) {
        string str = "[a-z]*";
        for (auto c : pattern) {
            str += c;
            str += "[a-z]*";
        }
        regex re(str);
        vector<bool> res;
        for (auto q : queries) {
            res.emplace_back(regex_match(q, re));
        }
        return res;
    }
};
/*
有 n 个花园，按从 1 到 n 标记。另有数组 paths ，其中 paths[i] = [xi, yi] 描述了花园 xi 到花园 yi 的双向路径。在每个花园中，你打算种下四种花之一。

另外，所有花园 最多 有 3 条路径可以进入或离开.

你需要为每个花园选择一种花，使得通过路径相连的任何两个花园中的花的种类互不相同。

以数组形式返回 任一 可行的方案作为答案 answer，其中 answer[i] 为在第 (i+1) 个花园中种植的花的种类。花的种类用  1、2、3、4 表示。保证存在答案。
T1042
 */
// 不需要dfs，暴力即可，这个dfs虽然过了，但是证明不了，感觉是有问题的！
class Solution {
public:
    vector<int> gardenNoAdj(int n, vector<vector<int>>& paths) {
        map<int, vector<int>> next;
        for (auto vec : paths) {
            next[vec[0]].emplace_back(vec[1]);
            next[vec[1]].emplace_back(vec[0]);
        }
        vector<int> clr(n + 1, 0);
        function<int(int, int)> dfs = [&](int pos, int color) -> int {
            if (clr[pos] != 0) {
                return clr[pos];
            }
            clr[pos] = color;
            vector<int> temp(5, 0);
            for (auto i : next[pos]) {
                temp[dfs(i, (color + 1) % 4 + 1)] = 1;
            }
            if (temp[color]) {
                for (int i = 1; i <= 4; i++) {
                    if (temp[i] == 0) {
                        clr[pos] = i;
                        break;
                    }
                }
            }

            return clr[pos];
        };
        for (int i = 1; i <= n; i++) {
            if (clr[i] == 0) {
                dfs(i, 1);
            }
        }
        return vector<int>(clr.begin() + 1, clr.end());
    }
};
// 暴力
class Solution {
public:
    vector<int> gardenNoAdj(int n, vector<vector<int>>& paths) {
        map<int, vector<int>> next;
        for (auto vec : paths) {
            next[vec[0]].emplace_back(vec[1]);
            next[vec[1]].emplace_back(vec[0]);
        }
        vector<int> color(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            vector<int> temp(5, 0);
            for (auto j : next[i]) {
                if (color[j]) {
                    temp[color[j]] = 1;
                }
            }
            for (int k = 1; k <= 4; k++) {
                if (temp[k] == 0) {
                    color[i] = k;
                    break;
                }
            }
        }
        return vector<int>(color.begin() + 1, color.end());
    }
};
/*
给定二叉树的根节点 root，找出存在于 不同 节点 A 和 B 之间的最大值 V，其中 V = |A.val - B.val|，且 A 是 B 的祖先。

（如果 A 的任何子节点之一为 B，或者 A 的任何子节点是 B 的祖先，那么我们认为 A 是 B 的祖先）
T1026
 */
// dfs
using pii = pair<int, int>;
class Solution {
public:
    int maxAncestorDiff(TreeNode* root) {
        int res = 0;
        function<pii(TreeNode*)> dfs = [&](TreeNode* node) -> pair<int, int> {
            if (node == nullptr) {
                return {-1, -1};
            }
            auto pl = dfs(node->left);
            auto pr = dfs(node->right);
            pii re = {node->val, node->val};
            if (pl.first != -1) {
                res = max(res, max(abs(pl.first - node->val), abs(pl.second - node->val)));
                re.first = min(re.first, pl.first);
                re.second = max(re.second, pl.second);
            }
            if (pr.first != -1) {
                res = max(res, max(abs(pr.first - node->val), abs(pr.second - node->val)));
                re.first = min(re.first, pr.first);
                re.second = max(re.second, pr.second);
            }
            return re;
        };
        dfs(root);
        return res;
    }
};
// bfs
using pii = pair<int, int>;
class Solution {
public:
    int maxAncestorDiff(TreeNode* root) {
        int res = 0;
        queue<TreeNode*> mq;
        queue<pii> mm;
        mq.emplace(root);
        mm.emplace(root->val, root->val);
        while (!mq.empty()) {
            auto node = mq.front();
            auto [minn, maxn] = mm.front();
            mq.pop();
            mm.pop();
            if (node->left) {
                mq.emplace(node->left);
                mm.emplace(min(node->left->val, minn), max(node->left->val, maxn));
                res = max(res, max(abs(node->left->val - minn), abs(node->left->val - maxn)));
            }
            if (node->right) {
                mq.emplace(node->right);
                mm.emplace(min(node->right->val, minn), max(node->right->val, maxn));
                res = max(res, max(abs(node->right->val - minn), abs(node->right->val - maxn)));
            }
        }
        return res;
    }
};
/*
给你一个整数数组 arr，请你将该数组分隔为长度 最多 为 k 的一些（连续）子数组。分隔完成后，每个子数组的中的所有值都会变为该子数组中的最大值。

返回将数组分隔变换后能够得到的元素最大和。本题所用到的测试用例会确保答案是一个 32 位整数。
T1043
 */
using pii = pair<int, int>;
class Solution {
public:
    int maxSumAfterPartitioning(vector<int>& arr, int K) {
        int n = arr.size();
        int dp[n + 1];
        memset(dp, 0, sizeof(dp));
        // auto cmp = [&](int a, int b) { return arr[a] < arr[b] || arr[a] == arr[b] && a > b; };
        // priority_queue<int, vector<int>, decltype(cmp)> mpq(cmp);
        for (int i = 1; i <= n; i++) {
            // while (!mpq.empty() && i - mpq.top() > K) {
            //     mpq.pop();
            // }
            // mpq.emplace(i - 1);
            int maxn = arr[i - 1];
            for (int j = i - 1; j >= i - K && j >= 0; j--) {
                dp[i] = max(dp[i], dp[j] + maxn * (i - j));
                if (j > 0) {
                    maxn = max(maxn, arr[j - 1]);
                }
            }
        }
        return dp[n];
    }
};
/*
给你两个整数数组 arr1 和 arr2，返回使 arr1 严格递增所需要的最小「操作」数（可能为 0）。

每一步「操作」中，你可以分别从 arr1 和 arr2 中各选出一个索引，分别为 i 和 j，0 <= i < arr1.length 和 0 <= j < arr2.length，然后进行赋值运算 arr1[i] = arr2[j]。

如果无法让 arr1 严格递增，请返回 -1。
1187
 */
class Solution {
public:
    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        sort(arr2.begin(), arr2.end());
        int n = arr1.size();
        vector<int> dp(n, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i < n; i++) {
            if (arr1[i] > arr1[i - 1]) {
                dp[i] = dp[i - 1];
            } else {
            }
        }
    }
};
/*
给你一个整数数组 nums，返回 nums 中最长等差子序列的长度。

回想一下，nums 的子序列是一个列表 nums[i1], nums[i2], ..., nums[ik] ，且 0 <= i1 < i2 < ... < ik <= nums.length - 1。并且如果 seq[i+1] - seq[i]( 0 <= i < seq.length - 1) 的值都相同，那么序列 seq 是等差的。
T1027
 */
class Solution {
public:
    int longestArithSeqLength(vector<int>& A) {
        int n = A.size(), res = 0;
        int dp[n][2000];
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < n; i++) {
            for (int j = i - 1; j >= 0; j--) {
                int sub = A[i] - A[j] + 1000;
                dp[i][sub] = max(dp[i][sub], dp[j][sub] + 1);
                res = max(res, dp[i][sub]);
            }
        }
        return res + 1;
    }
};

/*
给你一个字符串 s ，找出它的所有子串并按字典序排列，返回排在最后的那个子串。
T1163
20230501
 */
class Solution {
public:
    string lastSubstring(string s) {
        int i = 0, j = 1, n = s.size();
        while (j < n) {
            int k = 0;
            while (j + k < n && s[i + k] == s[j + k]) {
                k++;
            }
            if (j + k < n && s[i + k] < s[j + k]) {
                int t = i;
                i = j;
                j = max(i + 1, t + k + 1);
            } else {
                j += k + 1;
            }
        }
        return s.substr(i);
    }
};
/*
给你一个整数数组 nums 和两个整数 firstLen 和 secondLen，请你找出并返回两个非重叠 子数组 中元素的最大和，长度分别为 firstLen 和 secondLen 。

长度为 firstLen 的子数组可以出现在长为 secondLen 的子数组之前或之后，但二者必须是不重叠的。

子数组是数组的一个 连续 部分。
T1031
 */
class Solution {
public:
    int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
        int n = nums.size();
        vector<int> v1(n - firstLen + 1), v2(n - secondLen + 1);
        for (int i = 0; i < n; i++) {
            if (i < firstLen) {
                v1[0] += nums[i];
            } else {
                v1[i - firstLen + 1] = v1[i - firstLen] + nums[i] - nums[i - firstLen];
            }
            if (i < secondLen) {
                v2[0] += nums[i];
            } else {
                v2[i - secondLen + 1] = v2[i - secondLen] + nums[i] - nums[i - secondLen];
            }
        }
        int res = 0;
        for (int i = 0; i <= n - firstLen; i++) {
            for (int j = 0; j <= n - secondLen; j++) {
                if (j <= i && i - j < secondLen) {
                    continue;
                }
                if (i <= j && j - i < firstLen) {
                    continue;
                }
                res = max(v1[i] + v2[j], res);
            }
        }
        return res;
    }
};
/*
给出一个单词数组 words ，其中每个单词都由小写英文字母组成。

如果我们可以 不改变其他字符的顺序 ，在 wordA 的任何地方添加 恰好一个 字母使其变成 wordB ，那么我们认为 wordA 是 wordB 的 前身 。

    例如，"abc" 是 "abac" 的 前身 ，而 "cba" 不是 "bcad" 的 前身

词链是单词 [word_1, word_2, ..., word_k] 组成的序列，k >= 1，其中 word1 是 word2 的前身，word2 是 word3 的前身，依此类推。一个单词通常是 k == 1 的 单词链 。

从给定单词列表 words 中选择单词组成词链，返回 词链的 最长可能长度 。
 T1048
 */
using psi = pair<string, int>;
class Solution {
public:
    int longestStrChain(vector<string>& words) {
        map<int, vector<psi>> mp;
        int msize = INT_MAX;
        for (auto word : words) {
            mp[word.size()].emplace_back(word, 1);
            msize = min(msize, (int)word.size());
        }
        vector<psi> temp = mp[msize];
        int res = 0;
        set<string> visit;
        while (!temp.empty()) {
            vector<psi> ttemp;
            for (auto [s1, l1] : temp) {
                res = max(res, l1);
                for (auto [s2, l2] : mp[s1.size() + 1]) {
                    if (!visit.count(s2) && help(s1, s2)) {
                        visit.emplace(s2);
                        ttemp.emplace_back(s2, l1 + 1);
                    }
                }
            }
            msize++;
            for (auto [s1, l] : mp[msize]) {
                if (!visit.count(s1)) {
                    visit.emplace(s1);
                    ttemp.emplace_back(s1, l);
                }
            }
            temp = ttemp;
        }
        return res;
    }
    bool help(string& s1, string& s2) {
        int i = 0, j = 0, n = s1.size(), flag = true;
        while (i < n && j < n + 1) {
            if (s1[i] != s2[j]) {
                if (flag) {
                    j++;
                    flag = false;
                } else {
                    return false;
                }
            } else {
                i++;
                j++;
            }
        }
        return true;
    }
};
/*
我们把无限数量 ∞ 的栈排成一行，按从左到右的次序从 0 开始编号。每个栈的的最大容量 capacity 都相同。

实现一个叫「餐盘」的类 DinnerPlates：

    DinnerPlates(int capacity) - 给出栈的最大容量 capacity。
    void push(int val) - 将给出的正整数 val 推入 从左往右第一个 没有满的栈。
    int pop() - 返回 从右往左第一个 非空栈顶部的值，并将其从栈中删除；如果所有的栈都是空的，请返回 -1。
    int popAtStack(int index) - 返回编号 index 的栈顶部的值，并将其从栈中删除；如果编号 index 的栈是空的，请返回 -1。
T1172
 */
class DinnerPlates {
public:
    DinnerPlates(int capacity) {
    }

    void push(int val) {
    }

    int pop() {
    }

    int popAtStack(int index) {
    }
};

/**
 * Your DinnerPlates object will be instantiated and called as such:
 * DinnerPlates* obj = new DinnerPlates(capacity);
 * obj->push(val);
 * int param_2 = obj->pop();
 * int param_3 = obj->popAtStack(index);
 */
/*
给你一个字符串 croakOfFrogs，它表示不同青蛙发出的蛙鸣声（字符串 "croak" ）的组合。由于同一时间可以有多只青蛙呱呱作响，所以 croakOfFrogs 中会混合多个 “croak” 。

请你返回模拟字符串中所有蛙鸣所需不同青蛙的最少数目。

要想发出蛙鸣 "croak"，青蛙必须 依序 输出 ‘c’, ’r’, ’o’, ’a’, ’k’ 这 5 个字母。如果没有输出全部五个字母，那么它就不会发出声音。如果字符串 croakOfFrogs 不是由若干有效的 "croak" 字符混合而成，请返回 -1 。
1419
 */
class Solution {
public:
    int minNumberOfFrogs(string croakOfFrogs) {
        if (croakOfFrogs.size() % 5) {
            return -1;
        }
        map<int, int> mp;
        int res = 0, t = 0;
        for (auto c : croakOfFrogs) {
            mp[c]++;
            if (c == 'r' && mp[c] > mp['c']) {
                return -1;
            } else if (c == 'o' && mp[c] > mp['r']) {
                return -1;
            } else if (c == 'a' && mp[c] > mp['o']) {
                return -1;
            } else if (c == 'k' && mp[c] > mp['a']) {
                return -1;
            }
            if (c == 'k') {
                t--;
            }
            if (c == 'c') {
                t++;
                res = max(t, res);
            }
        }
        for (auto [x, y] : mp) {
            if (y != croakOfFrogs.size() / 5) {
                return -1;
            }
        }
        return res;
    }
};
/*
「推箱子」是一款风靡全球的益智小游戏，玩家需要将箱子推到仓库中的目标位置。

游戏地图用大小为 m x n 的网格 grid 表示，其中每个元素可以是墙、地板或者是箱子。

现在你将作为玩家参与游戏，按规则将箱子 'B' 移动到目标位置 'T' ：

    玩家用字符 'S' 表示，只要他在地板上，就可以在网格中向上、下、左、右四个方向移动。
    地板用字符 '.' 表示，意味着可以自由行走。
    墙用字符 '#' 表示，意味着障碍物，不能通行。
    箱子仅有一个，用字符 'B' 表示。相应地，网格上有一个目标位置 'T'。
    玩家需要站在箱子旁边，然后沿着箱子的方向进行移动，此时箱子会被移动到相邻的地板单元格。记作一次「推动」。
    玩家无法越过箱子。

返回将箱子推到目标位置的最小 推动 次数，如果无法做到，请返回 -1。
T1263
 */
class Solution {
public:
    int minPushBox(vector<vector<char>>& grid) {
        int dir[4][2] = {0, 1, 0, -1, 1, 0, -1, 0};
        int m = grid.size(), n = grid[0].size(), bi, bj, si, sj, ti, tj;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 'S') {
                    si = i;
                    sj = j;
                } else if (grid[i][j] == 'B') {
                    bi = i;
                    bj = j;
                } else if (grid[i][j] == 'T') {
                    ti = i;
                    tj = j;
                }
            }
        }
        auto check = [&](int i, int j) {
            return i >= 0 && i < m && j >= 0 && j < n && grid[i][j] != '#';
        };
        deque<vector<int>> mdq;
        set<vector<int>> visit;
        mdq.emplace_back(vector<int>{si, sj, bi, bj, 0});
        while (!mdq.empty()) {
            auto nd = mdq.front();
            mdq.pop_front();
            auto tnd = nd;
            tnd.pop_back();
            if (visit.count(tnd)) {
                continue;
            }
            visit.emplace(tnd);
            if (nd[2] == ti && nd[3] == tj) {
                return nd[4];
            }
            for (auto [x, y] : dir) {
                if (nd[0] + x == nd[2] && nd[1] + y == nd[3] && check(nd[2] + x, nd[3] + y) && !visit.count(vector<int>{x + nd[0], y + nd[1], nd[2] + x, nd[3] + y})) {
                    mdq.emplace_back(vector<int>{x + nd[0], y + nd[1], nd[2] + x, nd[3] + y, nd[4] + 1});
                } else if ((nd[0] + x != nd[2] || nd[1] + y != nd[3]) && check(x + nd[0], y + nd[1]) && !visit.count(vector<int>{x + nd[0], y + nd[1], nd[2], nd[3]})) {
                    mdq.emplace_front(vector<int>{x + nd[0], y + nd[1], nd[2], nd[3], nd[4]});
                }
            }
        }
        return -1;
    }
};
/*
+++
有 n 个房间，房间按从 0 到 n - 1 编号。最初，除 0 号房间外的其余所有房间都被锁住。你的目标是进入所有的房间。然而，你不能在没有获得钥匙的时候进入锁住的房间。

当你进入一个房间，你可能会在里面找到一套不同的钥匙，每把钥匙上都有对应的房间号，即表示钥匙可以打开的房间。你可以拿上所有钥匙去解锁其他房间。

给你一个数组 rooms 其中 rooms[i] 是你进入 i 号房间可以获得的钥匙集合。如果能进入 所有 房间返回 true，否则返回 false。
T841
 */
class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        queue<int> mq;
        mq.emplace(0);
        set<int> visit;
        while (!mq.empty()) {
            int node = mq.front();
            mq.pop();
            if (visit.count(node)) {
                continue;
            }
            visit.emplace(node);
            for (int i : rooms[node]) {
                if (!visit.count(i)) {
                    mq.emplace(i);
                }
            }
        }
        return visit.size() == rooms.size();
    }
};
/*
给你一个长度为 5 的字符串 time ，表示一个电子时钟当前的时间，格式为 "hh:mm" 。最早 可能的时间是 "00:00" ，最晚 可能的时间是 "23:59" 。

在字符串 time 中，被字符 ? 替换掉的数位是 未知的 ，被替换的数字可能是 0 到 9 中的任何一个。

请你返回一个整数 answer ，将每一个 ? 都用 0 到 9 中一个数字替换后，可以得到的有效时间的数目。
T2347
 */
class Solution {
public:
    int countTime(string time) {
        int res = 0;
        function<void(int, string)> dfs = [&](int index, const string& s) {
            if (index > 5) {
                if (s.substr(0, 2) < "24" && s.substr(3, 2) < "60") {
                    res++;
                }
                return;
            }
            if (time[index] == '?') {
                for (int i = 0; i <= 9; i++) {
                    string temp = s;
                    temp[index] = '0' + i;
                    dfs(index + 1, temp);
                }
            } else {
                dfs(index + 1, s);
            }
        };
        dfs(0, time);
        return res;
    }
};
/*
给定正整数 k ，你需要找出可以被 k 整除的、仅包含数字 1 的最 小 正整数 n 的长度。

返回 n 的长度。如果不存在这样的 n ，就返回-1。

注意： n 不符合 64 位带符号整数。
T1015
 */
class Solution {
public:
    int smallestRepunitDivByK(int k) {
        if (k % 2 == 0 || k % 5 == 0) {
            return -1;
        }
        set<int> st;
        int r = 1 % k, len = 1;
        while (r) {
            // 同余推
            /*
            a = t % k
            n = t*10 + 1;
            b = n % k;
              = (t*10 + 1) % k
              = (t*10%k + 1%k) % k
              = (a*10 + 1) % k
             */
            r = (r * 10 + 1) % k;
            len++;
            if (st.count(r)) {
                return -1;
            }
            st.emplace(r);
        }
        return len;
    }
};
/*
给定两个整数，分别表示分数的分子 numerator 和分母 denominator，以 字符串形式返回小数 。

如果小数部分为循环小数，则将循环的部分括在括号内。

如果存在多个答案，只需返回 任意一个 。

对于所有给定的输入，保证 答案字符串的长度小于 104 。
T166
 */
class Solution {
public:
    string fractionToDecimal(int n, int d) {
        string res = "";
        long long a = n, b = d;
        if (a % b == 0) {
            return to_string(a / b);
        }
        if (n < 0 && d < 0) {
            a = -a;
            b = -b;
        } else if (n < 0) {
            a = -a;
        } else if (d < 0) {
            b = -b;
        }
        map<int, int> mp;
        long long r = a % b;
        mp[r] = 0;
        while (r) {
            res += to_string((r * 10) / b);
            r = (r * 10) % b;
            if (mp.count(r)) {
                res = res.substr(0, mp[r]) + '(' + res.substr(mp[r]) + ')';
                break;
            }
            mp[r] = res.size();
        }
        res = to_string(a / b) + '.' + res;
        if (n < 0 && d > 0 || n > 0 && d < 0) {
            res = "-" + res;
        }
        return res;
    }
};
/*
给定一个二进制字符串 s 和一个正整数 n，如果对于 [1, n] 范围内的每个整数，其二进制表示都是 s 的 子字符串 ，就返回 true，否则返回 false 。

子字符串 是字符串中连续的字符序列。
T1016
 */
class Solution {
public:
    bool queryString(string s, int n) {
        int len = s.size();
        set<int> st;
        for (int i = 0; i < len; i++) {
            int k = 0;
            for (int j = i; j < len; j++) {
                k = k * 2 + s[j] - '0';
                if (k <= n && k > 0) {
                    st.emplace(k);
                }
                if (k > n) {
                    break;
                }
            }
        }
        return st.size() == n;
    }
};
/*
给定 m x n 矩阵 matrix 。

你可以从中选出任意数量的列并翻转其上的 每个 单元格。（即翻转后，单元格的值从 0 变成 1，或者从 1 变为 0 。）

返回 经过一些翻转后，行与行之间所有值都相等的最大行数 。
T1072
 */
class Solution {
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        for (int i = 0; i < m; i++) {
        }
        map<vector<int>, int> mp;
        for (auto vec : matrix) {
            vector<int> t1, t2;
            int index = 0;
            for (auto i : vec) {
                if (i == 0) {
                    t1.emplace_back(index++);
                } else {
                    t2.emplace_back(index++);
                }
            }
            mp[t1]++;
            mp[t2]++;
        }
        int res = 0;
        for (auto [x, y] : mp) {
            res = max(res, y);
        }
        return res;
    }
};
/*
在一个仓库里，有一排条形码，其中第 i 个条形码为 barcodes[i]。

请你重新排列这些条形码，使其中任意两个相邻的条形码不能相等。 你可以返回任何满足该要求的答案，此题保证存在答案。
T1054
 */
using pii = pair<int, int>;
class Solution {
public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
        map<int, int> mp;
        auto cmp = [](pii a, pii b) { return a.second < b.second; };
        priority_queue<pii, vector<pii>, decltype(cmp)> mpq(cmp);
        for (auto i : barcodes) {
            mp[i]++;
        }
        for (auto [x, y] : mp) {
            mpq.emplace(pii(x, y));
        }
        vector<int> res;
        while (!mpq.empty()) {
            auto f = mpq.top();
            mpq.pop();
            res.emplace_back(f.first);
            if (mpq.empty()) {
                break;
            }
            auto s = mpq.top();
            mpq.pop();
            res.emplace_back(s.first);
            if (--f.second) {
                mpq.emplace(f);
            }
            if (--s.second) {
                mpq.emplace(s);
            }
        }
        return res;
    }
};
/*
给你两个字符串数组 event1 和 event2 ，表示发生在同一天的两个闭区间时间段事件，其中：

    event1 = [startTime1, endTime1] 且
    event2 = [startTime2, endTime2]

事件的时间为有效的 24 小时制且按 HH:MM 格式给出。

当两个事件存在某个非空的交集时（即，某些时刻是两个事件都包含的），则认为出现 冲突 。

如果两个事件之间存在冲突，返回 true ；否则，返回 false 。
T2446
 */
class Solution {
public:
    bool haveConflict(vector<string>& event1, vector<string>& event2) {
        if (event1[0] < event2[0]) {
            return event1[1] >= event2[0];
        } else {
            return event2[1] >= event1[0];
        }
    }
};
/*
给出基数为 -2 的两个数 arr1 和 arr2，返回两数相加的结果。

数字以 数组形式 给出：数组由若干 0 和 1 组成，按最高有效位到最低有效位的顺序排列。
例如，arr = [1,1,0,1] 表示数字 (-2)^3 + (-2)^2 + (-2)^0 = -3。数组形式 中的数字 arr 也同样不含前导零：即 arr == [0] 或 arr[0] == 1。

返回相同表示形式的 arr1 和 arr2 相加的结果。两数的表示形式为：不含前导零、由若干 0 和 1 组成的数组。
T1073
 */
class Solution {
public:
    vector<int> addNegabinary(vector<int>& arr1, vector<int>& arr2) {
        int m = arr1.size(), n = arr2.size(), i = m - 1, j = n - 1;
        int c = 0;
        vector<int> res;
        while (i >= 0 || j >= 0 || c) {
            int a = i >= 0 ? arr1[i--] : 0;
            int b = j >= 0 ? arr2[j--] : 0;
            int x = a + b + c;
            if (x >= 0) {
                res.emplace_back(x % 2);
                c = x >= 2 ? -1 : 0;
            } else {
                res.emplace_back(1);
                c = 1;
            }
        }
        while (res.size() > 1 && res.back() == 0) {
            res.pop_back();
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
/*
你有一套活字字模 tiles，其中每个字模上都刻有一个字母 tiles[i]。返回你可以印出的非空字母序列的数目。

注意：本题中，每个活字字模只能使用一次。
T1079
 */
class Solution {
public:
    int numTilePossibilities(string tiles) {
        sort(tiles.begin(), tiles.end());
        int res = 0, n = tiles.size();
        string s = "";
        vector<int> visit(n, 0);
        function<void()> dfs = [&]() {
            set<int> temp;
            for (int i = 0; i < n; i++) {
                if (visit[i] == 1 || temp.count(tiles[i])) {
                    continue;
                }
                res++;
                temp.count(tiles[i]);
                visit[i] = 1;
                dfs();
                visit[i] = 0;
            }
        };
        dfs();
        return res;
    }
};
/*
给你二叉树的根节点 root 和一个整数 limit ，请你同时删除树中所有 不足节点 ，并返回最终二叉树的根节点。

假如通过节点 node 的每种可能的 “根-叶” 路径上值的总和全都小于给定的 limit，则该节点被称之为 不足节点 ，需要被删除。

叶子节点，就是没有子节点的节点。
1080
 */
class Solution {
public:
    TreeNode* sufficientSubset(TreeNode* root, int limit) {
        function<bool(TreeNode*&, int)> dfs = [&](TreeNode*& node, int sum) -> bool {
            sum -= node->val;
            if (!node->left && !node->right) {
                return sum > 0;
            }
            bool l = dfs(node->left, sum);
            bool r = dfs(node->right, sum);
            if (l) {
                node->left = nullptr;
            }
            if (r) {
                node->right = nullptr;
            }
            return l && r;
        };
        TreeNode* dum = new TreeNode();
        dum->left = root;
        dfs(dum, 0);
        return dum->left;
    }
};
class Solution {
public:
    TreeNode* sufficientSubset(TreeNode* root, int limit) {
        limit -= root->val;
        if (root->left == root->right) {
            return limit > 0 ? nullptr : root;
        }
        if (root->left) {
            root->left = sufficientSubset(root->left, limit);
        }
        if (root->right) {
            root->right = sufficientSubset(root->right, limit);
        }
        return root->right || root->left ? root : nullptr;
    }
};
/*
我们有一个 n 项的集合。给出两个整数数组 values 和 labels ，第 i 个元素的值和标签分别是 values[i] 和 labels[i]。还会给出两个整数 numWanted 和 useLimit 。

从 n 个元素中选择一个子集 s :

    子集 s 的大小 小于或等于 numWanted 。
    s 中 最多 有相同标签的 useLimit 项。

一个子集的 分数 是该子集的值之和。

返回子集 s 的最大 分数 。
T1090
 */
class Solution {
public:
    int largestValsFromLabels(vector<int>& values, vector<int>& labels, int numWanted, int useLimit) {
        int n = values.size(), res = 0;
        vector<int> index(n);
        iota(index.begin(), index.end(), 0);
        auto cmp = [&](int i, int j) { return values[i] > values[j]; };
        sort(index.begin(), index.end(), cmp);
        map<int, int> mp;
        for (int i : index) {
            if (mp[labels[i]] < useLimit && numWanted) {
                mp[labels[i]]++;
                res += values[i];
                numWanted--;
            }
        }
        return res;
    }
};
/*
给你一棵由 n 个顶点组成的无向树，顶点编号从 1 到 n。青蛙从 顶点 1 开始起跳。规则如下：

    在一秒内，青蛙从它所在的当前顶点跳到另一个 未访问 过的顶点（如果它们直接相连）。
    青蛙无法跳回已经访问过的顶点。
    如果青蛙可以跳到多个不同顶点，那么它跳到其中任意一个顶点上的机率都相同。
    如果青蛙不能跳到任何未访问过的顶点上，那么它每次跳跃都会停留在原地。

无向树的边用数组 edges 描述，其中 edges[i] = [ai, bi] 意味着存在一条直接连通 ai 和 bi 两个顶点的边。

返回青蛙在 t 秒后位于目标顶点 target 上的概率。与实际答案相差不超过 10-5 的结果将被视为正确答案。
T1377
 */
class Solution {
public:
    double frogPosition(int n, vector<vector<int>>& edges, int t, int target) {
        map<int, set<int>> next;
        map<int, long long> mp;
        for (auto vec : edges) {
            next[vec[0]].emplace(vec[1]);
            next[vec[1]].emplace(vec[0]);
        }
        queue<int> mq;
        mq.emplace(1);
        mp[1] = 1;
        t++;
        while (!mq.empty() && t--) {
            int len = mq.size();
            while (len--) {
                int f = mq.front();
                mq.pop();
                if (target == f) {
                    if (t == 0 || next[target].empty()) {
                        return (double)1 / mp[target];
                    }
                    break;
                }
                for (auto nxt : next[f]) {
                    mq.emplace(nxt);
                    next[nxt].erase(f);
                    mp[nxt] = mp[f] * next[f].size();
                }
            }
        }
        return 0;
    }
};
/*
给你一个字符串数组 words ，每一个字符串长度都相同，令所有字符串的长度都为 n 。

每个字符串 words[i] 可以被转化为一个长度为 n - 1 的 差值整数数组 difference[i] ，其中对于 0 <= j <= n - 2 有 difference[i][j] = words[i][j+1] - words[i][j] 。
注意两个字母的差值定义为它们在字母表中 位置 之差，也就是说 'a' 的位置是 0 ，'b' 的位置是 1 ，'z' 的位置是 25 。

    比方说，字符串 "acb" 的差值整数数组是 [2 - 0, 1 - 2] = [2, -1] 。

words 中所有字符串 除了一个字符串以外 ，其他字符串的差值整数数组都相同。你需要找到那个不同的字符串。

请你返回 words中 差值整数数组 不同的字符串。
T2451
 */
class Solution {
public:
    string oddString(vector<string>& words) {
    }
};
/*
给你一个 n x n 的二进制矩阵 grid 中，返回矩阵中最短 畅通路径 的长度。如果不存在这样的路径，返回 -1 。

二进制矩阵中的 畅通路径 是一条从 左上角 单元格（即，(0, 0)）到 右下角 单元格（即，(n - 1, n - 1)）的路径，该路径同时满足下述要求：

    路径途经的所有单元格都的值都是 0 。
    路径中所有相邻的单元格应当在 8 个方向之一 上连通（即，相邻两单元之间彼此不同且共享一条边或者一个角）。

畅通路径的长度 是该路径途经的单元格总数。
T1091
 */
class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    }
};

/*
给出二叉树的根节点 root，树上每个节点都有一个不同的值。

如果节点值在 to_delete 中出现，我们就把该节点从树上删去，最后得到一个森林（一些不相交的树构成的集合）。

返回森林中的每棵树。你可以按任意顺序组织答案。
T1110
 */
class Solution {
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        set<int> st(to_delete.begin(), to_delete.end());
        vector<TreeNode*> res;
        if (!st.count(root->val)) {
            res.emplace_back(root);
        }
        function<void(TreeNode*&)> dfs = [&](TreeNode*& node) -> void {
            if (node == nullptr) {
                return;
            }
            dfs(node->left);
            dfs(node->right);
            if (st.count(node->val)) {
                if (node->left) {
                    res.emplace_back(node->left);
                }
                if (node->right) {
                    res.emplace_back(node->right);
                }
                node = nullptr;
            }
        };
        dfs(root);
        return res;
    }
};
/*
给你一个正整数数组 arr，考虑所有满足以下条件的二叉树：

    每个节点都有 0 个或是 2 个子节点。
    数组 arr 中的值与树的中序遍历中每个叶节点的值一一对应。
    每个非叶节点的值等于其左子树和右子树中叶节点的最大值的乘积。

在所有这样的二叉树中，返回每个非叶节点的值的最小可能总和。这个和的值是一个 32 位整数。

如果一个节点有 0 个子节点，那么该节点为叶节点。
T1130
 */
class Solution {
public:
    int mctFromLeafValues(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
        auto mx = dp;
        for (int i = 0; i < n; i++) {
            mx[i][i] = arr[i];
            dp[i][i] = 0;
        }
        /* 这样有问题子区间没计算就计算了大区间 */
        // for (int i = 0; i < n; i++) {
        //     for (int j = i + 1; j < n; j++) {
        //         mx[i][j] = max(mx[i][j - 1], arr[j]);
        //         for (int k = i; k < j; k++) {
        //             dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + mx[i][k] * mx[k + 1][j]);
        //         }
        //     }
        // }
        for (int len = 1; len < n; len++) {
            for (int i = 0; i + len < n; i++) {
                int j = i + len;
                mx[i][j] = max(mx[i][j - 1], arr[j]);
                for (int k = i; k < j; k++) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + mx[i][k] * mx[k + 1][j]);
                }
            }
        }
        return dp[0][n - 1];
    }
};
/*
给你一个正整数数组 price ，其中 price[i] 表示第 i 类糖果的价格，另给你一个正整数 k 。

商店组合 k 类 不同 糖果打包成礼盒出售。礼盒的 甜蜜度 是礼盒中任意两种糖果 价格 绝对差的最小值。

返回礼盒的 最大 甜蜜度。
T2517
 */
class Solution {
public:
    int maximumTastiness(vector<int>& price, int k) {
        sort(price.begin(), price.end());
        int n = price.size(), l = 0, r = price.back() - price[0];
        while (l < r) {
            int mid = (l + r) / 2;
            int x = 0;
            for (int i = 1; i < n; i++) {
                if (price[i] - price[i - 1] > mid) {
                    if (++x > k) {
                        break;
                    }
                }
            }
            if (x > k) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        return l;
    }
};
class Solution {
public:
    int maximumTastiness(vector<int>& price, int k) {
        sort(price.begin(), price.end());
        int l = 0, r = price.back() - price[0];
        while (l < r) {
            int mid = (l + r) / 2;
            int t = price[0], x = 1;
            for (auto i : price) {
                if (i - t >= mid) {
                    t = i;
                    x++;
                }
            }
            // 如果选出的糖果数小于k，表示间隔太大了，满足条件的太少了！
            if (x < k) {
                r = mid - 1;
            } else {
                l = mid;
            }
        }
        return l;
    }
};
// 比赛时写的！
class Solution {
public:
    int maximumTastiness(vector<int>& price, int k) {
        sort(price.begin(), price.end());
        int left = 0, right = price.back() - price[0];
        while (left < right) {
            int mid = (left + right + 1) / 2;
            // cout<<left<<" "<<mid<<" "<<right<<endl;
            int pre = price[0], t = 1;
            for (int i : price) {
                if (i - pre > mid) {
                    pre = i;
                    t++;
                }
            }
            if (t < k) {
                right = mid - 1;
            } else {
                left = mid;
            }
        }
        return left;
    }
};