#include <bits/stdc++.h>
using namespace std;
int main() {
    int id = 0;
    auto test = [id]() mutable {
        id++;
    };
    auto cmp = [](int a, int b) {
        return a > b;
    };
    vector<int> v;
    sort(v.begin(), v.end(), cmp);
    set<int, decltype(cmp)> s(cmp);
    return 0;
}