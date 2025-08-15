#include "Lgs_scheduler.h"
#include <boost/context/continuation.hpp>
#include <deque>
#include <atomic>
#include <csignal>
#include <iostream>
#include <sys/time.h>

using continuation = boost::context::continuation;
using Yield = std::function<void()>;

static std::atomic preempt_requested{false};

extern "C" void onTick(int) {
    preempt_requested.store(true, std::memory_order_relaxed);
}

static void startPreemptionTimer(const int hz) {
    struct sigaction sa{};
    sa.sa_handler = onTick;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGALRM, &sa, nullptr);

    itimerval it{};
    it.it_interval.tv_sec = 0;
    it.it_interval.tv_usec = 1000000 / (hz > 0 ? hz : 1000);
    it.it_value = it.it_interval;
    setitimer(ITIMER_REAL, &it, nullptr);
}

static void stopPreemptionTimer() {
    constexpr itimerval it{};
    setitimer(ITIMER_REAL, &it, nullptr);
}

static void safepointYield(const Yield& yield) {
    if (preempt_requested.exchange(false, std::memory_order_relaxed)) {
        yield();
    }
}

struct Scheduler {
    std::deque<continuation> queue;

    void spawn(std::function<void(Yield)> fn) {
        queue.push_back(makeTask(std::move(fn)));
    }

    void run() {
        while (!queue.empty()) {
            auto c = std::move(queue.front());
            queue.pop_front();
            c = std::move(c).resume();
            if (c) queue.push_back(std::move(c));
        }
    }

    static continuation makeTask(std::function<void(Yield)> fn) {
        return boost::context::callcc(
            [fn = std::move(fn)](continuation&& scheduler) mutable {
                auto back = std::move(scheduler);
                const Yield y = [&back] {
                    back = std::move(back).resume();
                };
                fn(y);
                return std::move(back);
            }
        );
    }
};

static Scheduler scheduler;
static thread_local Yield tlsYield;

extern "C" void LgsScheduler_init(const int hz) {
    startPreemptionTimer(hz);
}

extern "C" void LgsScheduler_shutdown() {
    stopPreemptionTimer();
}

extern "C" void LgsScheduler_spawn(void (*task)(void*), void* userdata) {
    scheduler.spawn([=](const Yield& yield) {
        tlsYield = yield;
        task(userdata);
    });
}

extern "C" void LgsScheduler_run() {
    scheduler.run();
}

extern "C" void LgsScheduler_yield() {
    if (tlsYield) {
        safepointYield(tlsYield);
    }
}

void example() {
    Scheduler S;
    startPreemptionTimer(1000);
    S.spawn([](const Yield& yield) {
        for (int i = 0; i < 3; ++i) {
            for (volatile int k = 0; k < 200000; ++k) {
                safepointYield(yield);
            }
            std::cout << "[Task 1] Step " << i << "\n";
            yield();
        }
    });
    S.spawn([](const Yield& yield) {
        for (int i = 0; i < 3; ++i) {
            for (volatile int k = 0; k < 100000; ++k) {
                safepointYield(yield);
            }
            std::cout << "[Task 2] Step " << i << "\n";
            yield();
        }
    });
    S.run();
    stopPreemptionTimer();
}
