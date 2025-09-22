#pragma once
#include <deque>
#include <thread>
#include <mutex>
#include <atomic>
#include <boost/context/continuation.hpp>

using continuation = boost::context::continuation;

struct TaskInfo {
    void (*task)(void*);
    void* ctx;
};

struct Lgs_scheduler {
    std::deque<continuation> activeTasks;
    std::deque<TaskInfo> pendingTasks;
    std::atomic<bool> running{false};
    std::thread schedulerThread;
    std::mutex mtx;

    void start();
    void run();
    void spawn(void (*task)(void*), void* ctx);
    static bool shouldYield();
    static void yield();
    void shutdown();
};