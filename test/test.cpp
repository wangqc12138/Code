#include <bits/stdc++.h>
#include <sys/stat.h>
using namespace std;
int minimumSize(vector<int> &nums, int maxOperations)
{
    int left = 1, right = *max_element(nums.begin(), nums.end());
    while (left < right)
    {
        int mid = (right + left) / 2;
        cout << left << " " << right << "->" << mid << endl;
        long long k = 0;
        auto temp = nums;
        for (int i = 0; i < temp.size(); i++)
        {
            k += (temp[i] - 1) / mid;
        }
        if (k <= maxOperations)
        {
            right = mid;
        }
        else
        {
            left = mid + 1;
        }
    }
    return left;
}

int main()
{
    char s1[256];
    strcpy(s1, "/data01/gxcj/ob_run/var/stat/wqc_group.wqc_task.stat_10.19.14.34_20220509");
    char s2[256];
    strcpy(s2, "/data01/gxcj/ob_run/bak");
    string strNewFile = s2, strTmp = s1;
    strNewFile += strTmp.substr(strTmp.rfind('/'));
    cout << strNewFile << endl;
}
