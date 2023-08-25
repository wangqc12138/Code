#include <bits/stdc++.h>
using namespace std;
int main() {
    char a[20] = "123";
    char b[20] = "";
    cout << bool(string(a) == "") << endl;
    cout << bool(string(b) == "") << endl;
}
class sequence {
private:
    /* data */
    int step;
    int start_value;
    int min_value;
    int max_value;
    bool cycle;
    int m;
    // mp1 当前序列 mp2 最大缓存序列

    map<long long,int> mp1,mp2;

public:
    sequence(/* args */);
    ~sequence();
    int getnext();
};
int sequence::getnext(){
    auto tid = pthread_self();
    if(mp1.count(tid)){
        // 判断当前序列号+步长是否大于预设最大值
            // 大于的话需要修改最大缓存序列和当前序列
        // 不大于
            // 修改当前序列
        // 返回序列
    }else{
        // 初始化最大缓存序列和当前序列
        // 返回序列
    }
}
// 修改最大序列需要线程安全
void modif_m(){
    // 上锁
    // 修改当前最大值
    // 解锁
}
sequence::sequence(/* args */) {
}

sequence::~sequence() {
}

