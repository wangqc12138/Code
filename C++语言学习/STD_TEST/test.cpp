#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
namespace T1 {
class A {
public:
    A(int a) : a(a){};
    bool operator==(const A& node) const {
        return true;
        // return this->a == node.a;
    }
    int getValue() const {
        return a;
    }

private:
    int a;
};
ostream& operator<<(ostream& os, const A& node) {
    os << node.getValue();
    return os;
}
ostream& operator<<(ostream& os, const vector<int>& vec) {
    for (auto i : vec) {
        os << i << " ";
    }
    return os;
}
void test() {
    // std::adjacent_find
    //  判断一个容器里面有没有相邻的两个相同的元素，或者自定义的判断函数
    //  传入头尾（比较函数）
    //  传出找到的第一个合法的元素，没找到就是传出尾
    vector<int> v1 = {6, 7, 6, 7, 8, 3, 3, 0, 0, 1, 1};
    cout << *adjacent_find(v1.begin(), v1.end()) << endl;
    vector<int> v2 = {6, 7, 6, 7};
    cout << *adjacent_find(v2.begin(), v2.end()) << endl;
    vector<A> vecA;
    for (int i = 1; i <= 5; i++) {
        vecA.emplace_back(A(i));
    }
    cout << *adjacent_find(vecA.begin(), vecA.begin() + 3) << endl;
    vecA.emplace_back(A(5));
    vecA.emplace_back(A(6));
    cout << *adjacent_find(vecA.begin(), vecA.begin() + 5) << endl;
    vector<vector<int>> v3 = {{0, 1, 1}, {2, 1, 2}, {2, 1, 2}};
    cout << *adjacent_find(v3.begin(), v3.end()) << endl;
    cout << *adjacent_find(v2.begin(), v2.end(), [&](int a, int b) { return a == b + 1; }) << endl;
}
}  // namespace T1
namespace T2 {
// 有问题的
// ostream& operator<<(ostream& os, bool b) {
//     if (b) {
//         os << "True";
//     } else {
//         os << "False";
//     }
//     return os;
// }
void test() {
    // std::all_of
    // 判断整个容器的元素是否都满足条件
    // 传入头尾，判断函数
    // 空或者满足条件就返回true，反之返回false
    vector<int> v1 = {1, 2, 4, 5, 6, 2, 4, 5};
    vector<int> v2 = {111, 222, 333, 444, 555};
    // true
    cout << all_of(v1.begin(), v1.end(), [&](int i) { return i < 100; }) << endl;
    // false
    cout << all_of(v2.begin(), v2.end(), [&](int i) { return i < 100; }) << endl;
    // true
    cout << all_of(v2.begin(), v2.begin() + 2, [&](int i) { return i < 400; }) << endl;
}
}  // namespace T2
namespace T3 {
void test() {
    // std::any_of
    // 判断整个容器是否有一个满足条件
    // 传入头尾，判断函数
    // 空或者满足条件就返回true，反之返回false
    vector<int> v1 = {1, 2, 4, 5, 6, 2, 4, 5};
    vector<int> v2 = {111, 222, 333, 444, 555};
    // true
    cout << any_of(v1.begin(), v1.end(), [&](int i) { return i < 100; }) << endl;
    // false
    cout << any_of(v2.begin(), v2.end(), [&](int i) { return i < 100; }) << endl;
    // true
    cout << any_of(v2.begin(), v2.end(), [&](int i) { return i < 200; }) << endl;
}
}  // namespace T3
namespace T4 {
class A {
private:
    int a;

public:
    A(int a) : a(a){};
    bool operator<(const A& a) const {
        return this->a < a.a;
    }
};

void test() {
    // std::binary_search
    // 查找一个容器中 是否存在某个元素
    // 必须排好序，底层是二分
    // 如果是class的查找，需要重载小于
    vector<A> vecA;
    for (int i = 1; i <= 5; i++) {
        vecA.emplace_back(A(i));
    }
    // true
    cout << binary_search(vecA.begin(), vecA.end(), A(3)) << endl;
    // false
    cout << binary_search(vecA.begin(), vecA.end(), A(0)) << endl;
}
}  // namespace T4
namespace T5 {
ostream& operator<<(ostream& os, const vector<int>& vec) {
    for (auto i : vec) {
        os << i << " ";
    }
    return os;
}
void test() {
    // std::copy
    // 将一个容器的元素复制到另一个容器中，如果不是同个class，=重载后应该也可以
    vector<int> src = {0, 1, 2, 3, 4, 5, 6};
    vector<int> target = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
    auto res = copy(src.begin(), src.end(), target.begin());
    cout << *res << endl;
    cout << target << endl;
    target = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
    res = copy(src.begin(), src.end(), target.begin() + 1);
    cout << *res << endl;
    cout << target << endl;
    target = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
    res = copy(src.begin(), src.end(), target.end() - 1);
    cout << *res << endl;
    cout << target << endl;
}
}  // namespace T5
namespace T6 {
void test() {
    // std::copy_backward
    // 从后往前复制
    vector<int> v1 = {1, 2, 3, 4, 5};
    vector<int> v2 = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
    copy_backward(v1.begin(), v1.end(), v2.end());
    for (auto i : v2) {
        cout << i << " ";
    }
}
}  // namespace T6
namespace T7 {
void test() {
    // copy_if
    // 满足条件就拷贝
    vector<int> v1 = {1, 2, 3, 4, 5};
    vector<int> v2 = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
    copy_if(v1.begin(), v1.end(), v2.begin(), [&](int n) { return n % 2; });
    for (auto i : v2) {
        cout << i << " ";
    }
    cout << endl;
}
}  // namespace T7
namespace T8 {
void test() {
    // copy_n
    // 拷贝n个元素
    // n不能超过v1的范围，不然会有不干净的元素
    vector<int> v1 = {1, 2, 3, 4, 5};
    vector<int> v2 = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
    copy_n(v1.begin(), 1, v2.begin());
    for (auto i : v2) {
        cout << i << " ";
    }
    cout << endl;
    copy_n(v1.begin(), 9, v2.begin());

    for (auto i : v2) {
        cout << i << " ";
    }
    cout << endl;
}
}  // namespace T8
namespace T9 {
void test() {
    // count
    // 对容器内的某个元素计数
    vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 1, 2, 3};
    cout << count(v1.begin(), v1.end(), 1);
}
}  // namespace T9
namespace T10 {
void test() {
    // count_if
    // 对容器内的满足条件的元素计数
    vector<int> v1 = {1, 2, 3, 4, 5, 6, 7};
    cout << count_if(v1.begin(), v1.end(), [](int n) { return n % 2; }) << endl;
}
}  // namespace T10
namespace T11 {
void test() {
    // equal
    // 判断两个容器是否相同
    vector<int> v1 = {1, 2, 3};
    vector<int> v2 = {1, 2, 3, 5, 67};
    string s1 = "111";
    string s2 = "123111234";
    // true
    cout << equal(v1.begin(), v1.end(), v2.begin()) << endl;
    // false
    cout << equal(s1.begin(), s1.end(), s2.begin()) << endl;
    // true
    cout << equal(s1.begin(), s1.end(), s2.begin() + 3) << endl;
}
}  // namespace T11
namespace T12 {
void test() {
    // equal_range
    // 查找容器内某个元素的范围
    // 需要排好序
    vector<int> v1 = {1, 2, 3, 3, 3, 4, 5, 5, 6};
    vector<int> v2 = {1, 2, 2, 1, 1, 5, 4, 3, 2};
    auto p1 = equal_range(v1.begin(), v1.end(), 3);
    for (auto itr = p1.first; itr != p1.second; itr++) {
        cout << *itr << " ";
    }
    cout << endl;
    auto p2 = equal_range(v1.begin(), v1.end(), 7);
    for (auto itr = p2.first; itr != p2.second; itr++) {
        cout << *itr << " ";
    }
    cout << endl;
    // auto p3 = equal_range(v2.begin(), v2.end(), 2);
    // for (auto itr = p3.first; itr != p3.second; itr++) {
    //     cout << *itr << " ";
    // }
    // cout << endl;
}
}  // namespace T12
namespace T13 {
void test() {
    // fill
    // 用某个元素填满容器
    string s;
    int arr[10];
    // empty
    fill(s.begin(), s.begin() + 10, '0');
    fill(arr, arr + 10, 111);
    cout << s << endl;
    for (auto i : arr) {
        cout << i << " ";
    }
    cout << endl;
}
}  // namespace T13
namespace T14 {
void test() {
    // fill_n
    // 用某个元素填n个坑
    string s = "123--123";
    fill_n(s.begin() + 2, 10, '1');
    cout << s << endl;
    fill_n(s.begin() + 2, 2, '0');
    cout << s << endl;
}
}  // namespace T14
namespace T15 {
void test() {
    // find
    // 查找容器中传入开始迭代器后的第一个匹配的元素
    string s = "212345671";
    cout << *find(s.begin(), s.end(), '1') << endl;
    cout << *find(s.begin() + 2, s.end() - 2, '1') << endl;
    cout << *(find(s.begin() + 2, s.end(), '1') - 1) << endl;
}
}  // namespace T15
namespace T16 {
void test() {
    // find_end
    // 查找最后一段匹配的内容
    string s1 = "123451236712389";
    string s2 = "1235";
    auto itr = find_end(s1.begin(), s1.end(), s2.begin(), s2.end());
    for (; itr != s1.end(); itr++) {
        cout << *itr << " ";
    }
    cout << endl;
}
}  // namespace T16
namespace T17 {
void test() {
    // find_first_of()
    // 在容器1中找第一个能和容器2中的元素匹配上的元素
    // 可以传函数
    string s1 = "12345678";
    string s2 = "777333";
    // 7
    cout << *find_first_of(s1.begin(), s1.end(), s2.begin(), s2.begin() + 3) << endl;
    // 3
    cout << *find_first_of(s1.begin(), s1.end(), s2.begin(), s2.end()) << endl;
    // 2
    cout << *find_first_of(s1.begin(), s1.end(), s2.begin(), s2.end(), [](char c1, char c2) { return c1 + 1 == c2; }) << endl;
}
}  // namespace T17
namespace T18 {
void test() {
    // find_if
    // 返回满足函数的第一个元素
    string s = "0001000001";
    cout << *find_if(s.begin(), s.end(), [](char c) { return c == '1'; }) << endl;
    // find_if_not
    // 返回不满足函数的第一个元素
    cout << *find_if_not(s.begin(), s.end(), [](char c) { return c == '1'; }) << endl;
}
}  // namespace T18
namespace T19 {
void test() {
    // for_each
    // 对容器里的元素挨个做func的处理
    vector<int> vec(10, 0);
    int k = 0;
    for_each(vec.begin(), vec.end(), [&](int i) { i = k++; });
    for (auto i : vec) {
        cout << i << " ";
    }
    cout << endl;
    for_each(vec.begin(), vec.end(), [&](int& i) { i = k--; });
    for (auto i : vec) {
        cout << i << " ";
    }
    cout << endl;
}
}  // namespace T19

int main() {
    // std::adjacent_find
    // T1::test();
    // std::all_of
    // T2::test();
    // std::any_of
    // T3::test();
    // std::binary_search
    // T4::test();
    // std::copy
    // T5::test();
    // std::copy_backward
    // T6::test();
    T19::test();
    return 0;
}