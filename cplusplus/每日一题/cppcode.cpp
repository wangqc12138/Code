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