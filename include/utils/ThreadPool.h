#pragma once

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


