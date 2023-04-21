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
        return help(n, -2);
    }
    string help(int n, int x) {
        string res = "";
        while (n) {
            int remain = (n - x) % x;
            int q = n / x;
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
