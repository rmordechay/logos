#pragma once
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool {
public:
    mutex mtx;
    bool stop = false;
    size_t active = 0;
    vector<thread> workers;
    condition_variable cvTask;
    condition_variable cvIdle;
    queue<function<void()>> tasks;

    ThreadPool();
    void runTask(function<void()> task);
    void wait();
    void worker();
    ~ThreadPool();
};
