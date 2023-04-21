#include <bits/stdc++.h>
#include <regex.h>
#include <sys/stat.h>

#include <regex>
using namespace std;
int minimumSize(vector<int>& nums, int maxOperations) {
    int left = 1, right = *max_element(nums.begin(), nums.end());
    while (left < right) {
        int mid = (right + left) / 2;
        cout << left << " " << right << "->" << mid << endl;
        long long k = 0;
        auto temp = nums;
        for (int i = 0; i < temp.size(); i++) {
            k += (temp[i] - 1) / mid;
        }
        if (k <= maxOperations) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    int16_t iRet;
    regex_t reTemp;
    string strPattern = "^XFER[1-2]_LIST";
    string strObject = "XFER1_LIST_75";
    iRet = regcomp(&reTemp, strPattern.c_str(), REG_EXTENDED | REG_NOSUB);
    cout << iRet << endl;

    iRet = regexec(&reTemp, strObject.c_str(), 0, NULL, 0);
    cout << iRet << endl;
    regfree(&reTemp);
    // cout << -5 % 2 << endl
    //      << 5 % -2 << endl
    //      << -5 % -2 << endl
    //      << -5 / 2 << endl
    //      << 5 / -2 << endl
    //      << -5 / -2 << endl;
    return 0;
    // vector<int> v1 = {1, 2, 3};
    // vector<int> v2 = {1, 2, 3, 0};
    // auto flag = v1 < v2;
    // cout << flag << endl;
    // return 0;
    // int d = 1024;
    // cout << bitset<32>(d) << endl;
    // return 0;
    // string src = "/leetcode/problems/";
    // int n = src.find('/');
    // vector<string> res;
    // while (n != string::npos) {
    //     int k = src.find('/', n + 1);
    //     res.emplace_back(src.substr(n + 1, k - n - 1));
    //     n = k;
    // }
    // for (auto i : res) {
    //     cout << i << endl;
    // }
    // return 0;
    // vector<int> temp = {4, 1, 1, 2, 5, 1, 5, 4};
    // for (int i = 0; i < temp.size(); i++) {
    //     int m = 0, n = 0, index = 0;
    //     for (int j = 0; j < temp.size(); j++) {
    //         if (j == i) {
    //             continue;
    //         }
    //         if (index % 2) {
    //             m += temp[j];
    //         } else {
    //             n += temp[j];
    //         }
    //         index++;
    //     }
    //     cout << m << " " << n << endl;
    // }
    // return 0;
    // regex re("^(?!E2596).*");
    // regex re("^[^E2596].*");
    // cout << regex_match("E2596241232434", re) << endl;
    int r;
    regex_t re;
    string str = "^[^E2596].*";
    str = "^(?!E2596).*";
    r = regcomp(&re, str.c_str(), REG_EXTENDED | REG_NOSUB);
    cout << r << endl;
    if (!r) {
        r = regexec(&re, "E2596241232434", 0, NULL, 0);
        cout << r << endl;
    }

    return 0;
    // string str = "data.*$@$son.*";
    // string::size_type begin = str.find("$@$");
    // cout << begin << endl;
    // if (begin != str.npos) {
    //     string strTemp1 = str.substr(begin + 3);
    //     cout << strTemp1 << endl;
    //     string strTemp2 = str.substr(0, begin);
    //     cout << strTemp2 << endl;
    // }

    // return 0;
    // char s1[256];
    // strcpy(s1, "/data01/gxcj/ob_run/var/stat/wqc_group.wqc_task.stat_10.19.14.34_20220509");
    // char s2[256];
    // strcpy(s2, "/data01/gxcj/ob_run/bak");
    // string strNewFile = s2, strTmp = s1;
    // strNewFile += strTmp.substr(strTmp.rfind('/'));
    // cout << strNewFile << endl;
}
