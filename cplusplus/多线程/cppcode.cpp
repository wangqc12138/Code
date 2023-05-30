#include <condition_variable>
#include <future>
#include <mutex>

#include "head.h"
// 互斥锁
/*
mutex 和 pthread_mutex_t
lock_guard
unique_lock
 */
// 条件变量
// 信号量
// 原子操作

/*
给你一个类：

public class Foo {
  public void first() { print("first"); }
  public void second() { print("second"); }
  public void third() { print("third"); }
}

三个不同的线程 A、B、C 将会共用一个 Foo 实例。

    线程 A 将会调用 first() 方法
    线程 B 将会调用 second() 方法
    线程 C 将会调用 third() 方法

请设计修改程序，以确保 second() 方法在 first() 方法之后被执行，third() 方法在 second() 方法之后被执行。

提示：

    尽管输入中的数字似乎暗示了顺序，但是我们并不保证线程在操作系统中的调度顺序。
    你看到的输入格式主要是为了确保测试的全面性。
T1114
 */
// 由同一个线程来对一个 mutex 对象进行 lock 和 unlock 操作
class Foo {
public:
    Foo() {
        m1.lock();
        m2.lock();
    }

    void first(function<void()> printFirst) {
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        m1.unlock();
    }

    void second(function<void()> printSecond) {
        m1.lock();
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        m1.unlock();
        m2.unlock();
    }

    void third(function<void()> printThird) {
        m2.lock();
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
        m2.unlock();
    }

private:
    mutex m1, m2;
};
// 构造函数初始化列表的顺序是声明顺序！！
class Foo {
public:
    Foo() {
        ul1 = unique_lock<mutex>(mx1, try_to_lock);
        ul2 = unique_lock<mutex>(mx2, try_to_lock);
    }

    void first(function<void()> printFirst) {
        printFirst();
        ul1.unlock();
    }

    void second(function<void()> printSecond) {
        unique_lock<mutex> t(mx1);
        printSecond();
        ul2.unlock();
    }

    void third(function<void()> printThird) {
        unique_lock<mutex> t(mx2);
        printThird();
    }

private:
    unique_lock<mutex> ul1, ul2;
    mutex mx1, mx2;
};

class Foo {
public:
    Foo() {
    }

    void first(function<void()> printFirst) {
        unique_lock<mutex> t(mx);
        printFirst();
        k = 1;
        cv.notify_all();
    }

    void second(function<void()> printSecond) {
        unique_lock<mutex> t(mx);
        cv.wait(t, [&]() { return k == 1; });
        printSecond();
        k = 2;
        cv.notify_one();
    }

    void third(function<void()> printThird) {
        unique_lock<mutex> t(mx);
        cv.wait(t, [&]() { return k == 2; });
        printThird();
    }

private:
    mutex mx;
    condition_variable cv;
    int k = 0;
};
#include <semaphore.h>
class Foo {
public:
    Foo() {
        sem_init(&sec, 0, 0);
        sem_init(&thr, 0, 0);
    }

    void first(function<void()> printFirst) {
        printFirst();
        sem_post(&sec);
    }

    void second(function<void()> printSecond) {
        sem_wait(&sec);
        printSecond();
        sem_post(&thr);
    }

    void third(function<void()> printThird) {
        sem_wait(&thr);
        printThird();
    }

private:
    sem_t sec, thr;
};
class Foo {
public:
    Foo() {
    }

    void first(function<void()> printFirst) {
        printFirst();
        p1.set_value();
    }

    void second(function<void()> printSecond) {
        p1.get_future().wait();
        printSecond();
        p2.set_value();
    }

    void third(function<void()> printThird) {
        p2.get_future().wait();
        printThird();
    }

private:
    future<void> f1, f2;
    promise<void> p1, p2;
};
class Foo {
public:
    Foo() : p1([]() {}), p2([]() {}) {
    }

    void first(function<void()> printFirst) {
        printFirst();
        p1();
    }

    void second(function<void()> printSecond) {
        p1.get_future().wait();
        printSecond();
        p2();
    }

    void third(function<void()> printThird) {
        p2.get_future().wait();
        printThird();
    }

private:
    packaged_task<void()> p1, p2;
};
/*
实现一个拥有如下方法的线程安全有限阻塞队列：

    BoundedBlockingQueue(int capacity) 构造方法初始化队列，其中capacity代表队列长度上限。
    void enqueue(int element) 在队首增加一个element. 如果队列满，调用线程被阻塞直到队列非满。
    int dequeue() 返回队尾元素并从队列中将其删除. 如果队列为空，调用线程被阻塞直到队列非空。
    int size() 返回当前队列元素个数。

你的实现将会被多线程同时访问进行测试。每一个线程要么是一个只调用enqueue方法的生产者线程，要么是一个只调用dequeue方法的消费者线程。
size方法将会在每一个测试用例之后进行调用。

请不要使用内置的有限阻塞队列实现，否则面试将不会通过。
T1188
 */
#include <semaphore.h>
class BoundedBlockingQueue {
public:
    BoundedBlockingQueue(int capacity) : capacity(capacity), len(0) {
        sem_init(&p, 0, capacity);
        sem_init(&c, 0, 0);
    }

    void enqueue(int element) {
        sem_wait(&p);
        if (len < capacity) {
            mq.emplace(element);
            len++;
        }
        sem_post(&c);
    }

    int dequeue() {
        sem_wait(&c);
        int re;
        if (len > 0) {
            re = mq.front();
            mq.pop();
            len--;
        }
        sem_post(&p);
        return re;
    }

    int size() {
        return len;
    }

private:
    sem_t p, c;
    int capacity, len;
    queue<int> mq;
};
class BoundedBlockingQueue {
public:
    BoundedBlockingQueue(int capacity) : capacity(capacity) {
    }

    void enqueue(int element) {
        unique_lock<mutex> mx1;
        cv2.wait(mx1, [&]() { return mq.size() < capacity; });
        mq.emplace(element);
        cv1.notify_one();
    }

    int dequeue() {
        unique_lock<mutex> mx2;
        cv1.wait(mx2, [&]() { return mq.size() > 0; });
        int re = mq.front();
        mq.pop();
        cv2.notify_one();
        return re;
    }

    int size() {
        return mq.size();
    }

private:
    mutex mx1, mx2;
    condition_variable cv1, cv2;
    queue<int> mq;
    int capacity;
};
/*
现在有两种线程，氧 oxygen 和氢 hydrogen，你的目标是组织这两种线程来产生水分子。

存在一个屏障（barrier）使得每个线程必须等候直到一个完整水分子能够被产生出来。

氢和氧线程会被分别给予 releaseHydrogen 和 releaseOxygen 方法来允许它们突破屏障。

这些线程应该三三成组突破屏障并能立即组合产生一个水分子。

你必须保证产生一个水分子所需线程的结合必须发生在下一个水分子产生之前。

换句话说:

    如果一个氧线程到达屏障时没有氢线程到达，它必须等候直到两个氢线程到达。
    如果一个氢线程到达屏障时没有其它线程到达，它必须等候直到一个氧线程和另一个氢线程到达。

书写满足这些限制条件的氢、氧线程同步代码。
T1117
 */
#include <semaphore.h>
class H2O {
public:
    H2O() {
        sem_init(&s1, 0, 2);
        sem_init(&s2, 0, 0);
    }

    void hydrogen(function<void()> releaseHydrogen) {
        sem_wait(&s1);
        releaseHydrogen();
        sem_post(&s2);
    }

    void oxygen(function<void()> releaseOxygen) {
        sem_wait(&s2);
        releaseOxygen();
        sem_post(&s1);
        sem_post(&s1);
    }

private:
    sem_t s1, s2;
};

class H2O {
public:
    H2O() {
    }

    void hydrogen(function<void()> releaseHydrogen) {
        releaseHydrogen();
    }

    void oxygen(function<void()> releaseOxygen) {
        releaseOxygen();
    }

private:
};

/*
给你一个类：

class FooBar {
  public void foo() {
    for (int i = 0; i < n; i++) {
      print("foo");
    }
  }

  public void bar() {
    for (int i = 0; i < n; i++) {
      print("bar");
    }
  }
}

两个不同的线程将会共用一个 FooBar 实例：

    线程 A 将会调用 foo() 方法，而
    线程 B 将会调用 bar() 方法

请设计修改程序，以确保 "foobar" 被输出 n 次。
T1115
 */
#include <semaphore.h>
class FooBar {
private:
    int n;

public:
    FooBar(int n) {
        this->n = n;
        sem_init(&s1, 0, 1);
        sem_init(&s2, 0, 0);
    }

    void foo(function<void()> printFoo) {
        for (int i = 0; i < n; i++) {
            sem_wait(&s1);
            // printFoo() outputs "foo". Do not change or remove this line.
            printFoo();
            sem_post(&s2);
        }
    }

    void bar(function<void()> printBar) {
        for (int i = 0; i < n; i++) {
            sem_wait(&s2);
            // printBar() outputs "bar". Do not change or remove this line.
            printBar();
            sem_post(&s1);
        }
    }

private:
    sem_t s1, s2;
};
/*
现有函数 printNumber 可以用一个整数参数调用，并输出该整数到控制台。

    例如，调用 printNumber(7) 将会输出 7 到控制台。

给你类 ZeroEvenOdd 的一个实例，该类中有三个函数：zero、even 和 odd 。ZeroEvenOdd 的相同实例将会传递给三个不同线程：

    线程 A：调用 zero() ，只输出 0
    线程 B：调用 even() ，只输出偶数
    线程 C：调用 odd() ，只输出奇数

修改给出的类，以输出序列 "010203040506..." ，其中序列的长度必须为 2n 。

实现 ZeroEvenOdd 类：

    ZeroEvenOdd(int n) 用数字 n 初始化对象，表示需要输出的数。
    void zero(printNumber) 调用 printNumber 以输出一个 0 。
    void even(printNumber) 调用printNumber 以输出偶数。
    void odd(printNumber) 调用 printNumber 以输出奇数。

T1116
 */
#include <semaphore.h>
class ZeroEvenOdd {
private:
    int n;
    int stat;
    sem_t s1, s2, s3;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
        stat = 1;
        sem_init(&s1, 0, 1);
        sem_init(&s2, 0, 0);
        sem_init(&s3, 0, 0);
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        while (stat <= n) {
            sem_wait(&s1);
            printNumber(0);
            if (stat % 2) {
                sem_post(&s2);
            } else {
                sem_post(&s3);
            }
        }
    }

    void even(function<void(int)> printNumber) {
        while (stat <= n) {
            if (stat % 2 == 0) {
                sem_wait(&s3);
                printNumber(stat);
                stat++;
                sem_post(&s1);
            }
        }
    }

    void odd(function<void(int)> printNumber) {
        while (stat <= n) {
            if (stat % 2 == 1) {
                sem_wait(&s2);
                printNumber(stat);
                stat++;
                sem_post(&s1);
            }
        }
    }
};
/*
 */