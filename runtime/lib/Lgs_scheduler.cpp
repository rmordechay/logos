#include "Lgs_scheduler.h"
#include <csignal>
#include <sys/time.h>

using Yield = std::function<void()>;
thread_local Yield tlsYield;
std::atomic preempt{false};

static void initSignals() {
    struct sigaction sa{};
    const auto onTick = [](int) {
        preempt.store(true, std::memory_order_relaxed);
    };
    sa.sa_handler = onTick;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGALRM, &sa, nullptr);

    itimerval it{};
    constexpr auto hz = 1000;
    it.it_interval.tv_sec = 0;
    it.it_interval.tv_usec = 1000000 / hz;
    it.it_value = it.it_interval;
    setitimer(ITIMER_REAL, &it, nullptr);
}

void Lgs_scheduler::run() {
    initSignals();
    while (!queue.empty()) {
        auto c = std::move(queue.front());
        queue.pop_front();
        c = std::move(c).resume();
        if (!c) continue;
        queue.push_back(std::move(c));
    }
}

void Lgs_scheduler::spawn(void (*task)(void*), void* ctx) {
    queue.push_back(boost::context::callcc(
        [task, ctx](continuation&& c) mutable {
            tlsYield = [&c] {
                c = std::move(c).resume();
            };
            task(ctx);
            return std::move(c);
        }
    ));
}

void Lgs_scheduler::yield() {
    if (!tlsYield) return;
    const auto shouldYield = preempt.exchange(false, std::memory_order_relaxed);
    if (shouldYield) {
        tlsYield();
    }
}

void Lgs_scheduler::shutdown() {
    constexpr itimerval it{};
    setitimer(ITIMER_REAL, &it, nullptr);
}
