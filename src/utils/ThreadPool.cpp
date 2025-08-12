#include "utils/ThreadPool.h"

ThreadPool::ThreadPool() {
    const auto n = std::max(1u, std::thread::hardware_concurrency());
    workers.reserve(n);
    for (unsigned i = 0; i < n; ++i) {
        workers.emplace_back([this]{ worker(); });
    }
}

void ThreadPool::runTask(std::function<void()> task) {
    {
        std::lock_guard lock(mtx);
        tasks.push(std::move(task));
    }
    cvTask.notify_one();
}

void ThreadPool::wait() {
    std::unique_lock lock(mtx);
    cvIdle.wait(lock, [this]{
        return tasks.empty() && active == 0;
    });
}

void ThreadPool::worker() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock lock(mtx);
            cvTask.wait(lock, [this]{
                return stop || !tasks.empty();
            });
            if (stop && tasks.empty()) return;
            task = std::move(tasks.front());
            tasks.pop();
            ++active;
        }
        try { task(); } catch (...) {}
        {
            std::lock_guard lock(mtx);
            --active;
            if (tasks.empty() && active == 0) {
                cvIdle.notify_all();
            }
        }
    }
}

ThreadPool::~ThreadPool() {
    {
        std::lock_guard lock(mtx);
        stop = true;
    }
    cvTask.notify_all();
    for (auto& w : workers) {
        w.join();
    }
}