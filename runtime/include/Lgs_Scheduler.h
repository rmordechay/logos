#pragma once
#include "Lgs_Context.h"
#include <deque>
#include <thread>
#include <vector>

struct Lgs_Coroutine {
    Lgs_Context ctx;
    void* stack;
    size_t stackSize;
    void (*fn)(void*);
    void* arg;
    bool finished;
};

struct Lgs_Scheduler {
    std::mutex mtx;
    std::thread thread;
    std::atomic<bool> active;
    std::deque<Lgs_Coroutine*> pending;
    std::deque<Lgs_Coroutine*> running;
    void start();
    void loop();
    void spawn(void (*fn)(void*), void* arg);
    void shutdown();
};
