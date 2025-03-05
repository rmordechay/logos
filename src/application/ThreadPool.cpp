#include "ThreadPool.h"

ThreadPool::ThreadPool() {
    for(size_t i = 0; i < threadsNumber; ++i) {
        workers.emplace_back([this] {
            while(true) {
                function<void()> task;
                {
                    unique_lock lock(mtx);
                    condition.wait(lock, [this] {
                        return stop || !tasks.empty();
                    });
                    if(tasks.empty()) {
                        return;
                    }
                    task = std::move(tasks.front());
                    tasks.pop();
                }
                task();
            }
        });
    }
}

void ThreadPool::runTask(function<void()> task) {
    {
        lock_guard lock(mtx);
        tasks.push(std::move(task));
    }
    condition.notify_one();
}

void ThreadPool::wait() {
    {
        unique_lock lock(mtx);
        stop = true;
    }
    condition.notify_all();
    for(auto& worker: workers) {
        worker.join();
    }
}
