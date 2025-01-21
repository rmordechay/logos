#include "ThreadPool.h"

#include <iostream>

void ThreadPool::start() {
    for(size_t i = 0; i < threadsNumber; ++i) {
        workers.emplace_back([this] {
            while(true) {
                function<void()> task;
                {
                    cout << "locking" << endl;
                    unique_lock lock(queueMtx);
                    cout << "waiting" << endl;
                    condition.wait(lock, [this] {
                        return stop || !tasks.empty();
                    });
                    cout << "finised waiting" << endl;
                    if(stop && tasks.empty()) {
                        return;
                    }
                    cout << "poppoing task" << endl;
                    task = std::move(tasks.front());
                    tasks.pop();
                }
                task();
            }
        });
    }
}

void ThreadPool::addToVector(const int value) {
    lock_guard lock(vectorMtx);
    shared_vector.push_back(value);
}

vector<int> ThreadPool::getVec() {
    lock_guard lock(vectorMtx);
    return shared_vector;
}

void ThreadPool::waitUntilDone() {
    unique_lock lock(queueMtx);
    condition.wait(lock, [this] { return tasks.empty(); });
}

ThreadPool::~ThreadPool() {
    {
        unique_lock lock(queueMtx);
        stop = true;
    }
    condition.notify_all();
    for(thread &worker: workers) {
        worker.join();
    }
}
