#include "Lgs_scheduler.h"
#include <csignal>
#include <sys/time.h>

using Yield = std::function<void()>;
thread_local Yield tlsYield;
std::atomic preempt_requested{false};

void Lgs_Scheduler::run() {
    while (!queue.empty()) {
        auto c = std::move(queue.front());
        queue.pop_front();
        c = std::move(c).resume();
        if (c) queue.push_back(std::move(c));
    }
}

void Lgs_Scheduler::spawn(void (*task)(void*), void* userdata) {
    const auto fn = [task, userdata](const Yield& yield) {
        tlsYield = yield;
        task(userdata);
    };
    queue.push_back(boost::context::callcc(
        [fn = std::move(fn)](continuation&& scheduler) mutable {
            auto back = std::move(scheduler);
            const Yield y = [&back] {
                back = std::move(back).resume();
            };
            fn(y);
            return std::move(back);
        }
    ));
}

void Lgs_Scheduler::init(const int hz) {
    struct sigaction sa{};
    const auto onTick = [](int) {
        preempt_requested.store(true, std::memory_order_relaxed);
    };
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


void Lgs_Scheduler::yield() {
    if (!tlsYield) return;
    const auto safePointYield = [](const Yield& yield) {
        if (preempt_requested.exchange(false, std::memory_order_relaxed)) {
            yield();
        }
    };
    safePointYield(tlsYield);
}

void Lgs_Scheduler::shutdown() {
    constexpr itimerval it{};
    setitimer(ITIMER_REAL, &it, nullptr);
}
