#pragma once

class ThreadPool {
public:
    std::mutex mtx;
    vector<thread> workers;
    queue<function<void()>> tasks;
    std::condition_variable condition;
    bool stop = false;

    ThreadPool();
    void runTask(function<void()> task);
    void wait();
    ~ThreadPool() = default;
};


