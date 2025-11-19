#pragma once
#include <thread>
#include <mutex>
#include <queue>
#include <atomic>
#include <condition_variable>

class ThreadPool {
public:
    std::mutex mtx;
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::condition_variable cvTask, cvIdle;
    std::atomic<size_t> active = 0;
    bool stop = false;

    explicit ThreadPool(size_t n = std::thread::hardware_concurrency()) {
        n = std::max<size_t>(1, n);
        workers.reserve(n);
        for (size_t i = 0; i < n; ++i) {
            workers.emplace_back([this] { worker(); });
        }
        workers.shrink_to_fit();
    }

    template<typename F>
    void runTask(F&& task) {
        {
            std::lock_guard lock(mtx);
            tasks.emplace(std::forward<F>(task));
        }
        cvTask.notify_one();
    }

    void wait() {
        std::unique_lock lock(mtx);
        cvIdle.wait(lock, [this] {
            return tasks.empty() && active.load(std::memory_order_relaxed) == 0;
        });
    }

    void worker() {
        while (true) {
            std::function<void()> task;
            {
                std::unique_lock lock(mtx);
                cvTask.wait(lock, [this] {
                    return stop || !tasks.empty();
                });
                if (stop && tasks.empty()) return;
                task = std::move(tasks.front());
                tasks.pop();
                active.fetch_add(1, std::memory_order_relaxed);
            }

            try { task(); } catch (...) {}
            {
                std::lock_guard lock(mtx);
                active.fetch_sub(1, std::memory_order_relaxed);
                if (tasks.empty() && active.load(std::memory_order_relaxed) == 0) {
                    cvIdle.notify_all();
                }
            }
        }
    }

    ~ThreadPool() {
        {
            std::lock_guard lock(mtx);
            stop = true;
        }
        cvTask.notify_all();
        for (auto& w : workers) {
            w.join();
        }
    }
};
