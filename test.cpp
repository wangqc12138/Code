#include <pthread.h>

#include <condition_variable>
#include <iostream>
#include <thread>
#include <vector>
using namespace std;

class Foo {
private:
    mutex m1;
    mutex m2;
    unique_lock<mutex> ulock1;
    unique_lock<mutex> ulock2;

public:
    Foo() {
        ulock1 = unique_lock<mutex>(m1, try_to_lock);
        ulock2 = unique_lock<mutex>(m2, try_to_lock);
    }
    void first() {
        cout << "first";
        ulock1.unlock();
    }
    void second() {
        lock_guard<mutex> guard(m1);
        cout << "second";
        ulock2.unlock();
    }
    void third() {
        lock_guard<mutex> guard(m2);
        cout << "third";
    }
};
int main() {
    vector<int> nums = {3, 2, 1};
    Foo f;
    thread a, b, c;
    for (int i = 0; i < nums.size(); i++) {
        int value = nums[i];
        if (value == 1) {
            a = thread(&Foo::first, &f);
        } else if (value == 2) {
            b = thread(&Foo::second, &f);
        } else if (value == 3) {
            c = thread(&Foo::third, &f);
        }
    }
    c.join();
    b.join();
    a.join();
    return 0;
}