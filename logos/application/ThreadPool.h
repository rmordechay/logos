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
    mutex queueMtx;
    mutex vectorMtx;
    condition_variable condition;
    vector<int> shared_vector;
    const size_t threadsNumber = 10;
    bool stop;

    explicit ThreadPool(): stop(false) {}
    void start();
    template <class F>
    void addTask(F&& f);
    void addToVector(const int value);
    vector<int> getVec();
    void waitUntilDone();
    ~ThreadPool();
};

template <class F>
void ThreadPool::addTask(F&& f) {
    {
        unique_lock lock(queueMtx);
        tasks.emplace(std::forward<F>(f));
    }
    condition.notify_one();
}

#endif //THREADPOOL_H
