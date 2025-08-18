#pragma once
#include <deque>
#include <boost/context/continuation.hpp>

using continuation = boost::context::continuation;

struct Lgs_Scheduler {
    std::deque<continuation> queue;

    void run();
    void spawn(void (*task)(void*), void* userdata);
    static void init(int hz);
    static void yield();
    static void shutdown();
};
