#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <queue>
#include <thread>
#include <vector>
#include <condition_variable>
#include <functional>

using namespace std;

class ThreadPool {
public:
    std::mutex mtx;
    vector<thread> workers;
    queue<function<void()>> tasks;
    std::condition_variable condition;
    const size_t threadsNumber = 10;
    bool stop = false;

    void start();
    void runTask(function<void()> task);
    void wait();
    ~ThreadPool() = default;
};

#endif //THREADPOOL_H
