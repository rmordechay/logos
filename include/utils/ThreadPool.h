#pragma once
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool {
public:
    std::mutex mtx;
    bool stop = false;
    size_t active = 0;
    std::vector<std::thread> workers;
    std::condition_variable cvTask;
    std::condition_variable cvIdle;
    std::queue<std::function<void()>> tasks;

    ThreadPool();
    void runTask(std::function<void()> task);
    void wait();
    void worker();
    ~ThreadPool();
};
