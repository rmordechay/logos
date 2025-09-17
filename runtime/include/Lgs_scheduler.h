#pragma once
#include <deque>
#include <boost/context/continuation.hpp>

using continuation = boost::context::continuation;

struct Lgs_scheduler {
    std::deque<continuation> queue;

    void run();
    void spawn(void (*task)(void*), void* ctx);
    static void yield();
    static void shutdown();
};
