#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <queue>
#include <thread>
#include <vector>

using namespace std;

class ThreadPool {
public:
    vector<thread> workers;
    queue<function<void()>> tasks;
    mutex mtx;
    condition_variable condition;
    const size_t threadsNumber = 10;
    bool stop = false;

    explicit ThreadPool() {}
    void start();
    void enqueueTask(function<void()> task);
    void wait();
    ~ThreadPool() = default;
};

#endif //THREADPOOL_H
