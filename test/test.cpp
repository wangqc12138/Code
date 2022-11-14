#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
#define bit(x, i) (((x) >> (i)) & 1)
#define no          \
	{               \
		puts("No"); \
		return;     \
	}
#define yes          \
	{                \
		puts("Yes"); \
		return;      \
	}
using ll = long long;
using pii = pair<int, int>;
void solve()
{
	int n;
	string str;
	cin >> n >> str;
	string ans = "";
	for (int i = n - 1; i >= 0; i--)
	{
		if (str[i] == '0')
		{
			string temp = str.substr(i - 2, 2);
			ans += 'a' + stoi(temp) - 1;
			i -= 2;
		}
		else
		{
			ans += 'a' + str[i] - '0' - 1;
		}
	}
	reverse(ans.begin(), ans.end());
	cout << ans << endl;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	freopen("./test.txt", "r", stdin);
	int tt;
	cin >> tt;
	for (int i = 0; i < tt; i++)
	{
		solve();
	}
	return 0;
}
