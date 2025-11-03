#include "Lgs_Scheduler.h"
#include <atomic>
#include <csignal>
#include <sys/time.h>
#include <thread>
#include <mutex>
#include <chrono>
#include <iostream>

#define STACK_SIZE 2048
#define QUANTUM 10000

thread_local Lgs_Coroutine* tlsCurrent = nullptr;
Lgs_Context schedulerCtx{};
std::atomic preempt{false};
Lgs_Coroutine* current = nullptr;

static void onTick(int) {
    preempt.store(true, std::memory_order_relaxed);
}

static void initTimer() {
    struct sigaction sa {};
    sa.sa_handler = onTick;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGALRM, &sa, nullptr);

    itimerval it {};
    it.it_interval.tv_sec = 0;
    it.it_interval.tv_usec = QUANTUM;
    it.it_value = it.it_interval;
    setitimer(ITIMER_REAL, &it, nullptr);
}

static void coroutineEntry() {
    if (tlsCurrent == nullptr) return;
    tlsCurrent->fn(tlsCurrent->arg);
    tlsCurrent->finished = true;
    tlsCurrent->ctx.switchContext(schedulerCtx);
}

static Lgs_Coroutine* makeCoroutine(void (*fn)(void*), void* arg) {
    auto* co = new Lgs_Coroutine();
    co->stackSize = STACK_SIZE;
    co->stack = std::malloc(co->stackSize);
    co->fn = fn;
    co->arg = arg;
    co->finished = false;
    auto* top = static_cast<std::byte*>(co->stack) + co->stackSize;
    co->ctx.reset(top, reinterpret_cast<void*>(coroutineEntry));
    return co;
}

void Lgs_Scheduler::start() {
    active = true;
    thread = std::thread([this] { loop(); });
}

void Lgs_Scheduler::loop() {
    initTimer();
    while (active) {
        Lgs_Coroutine* coroutine = nullptr;
        {
            std::lock_guard lk(mtx);
            if (!pending.empty()) {
                coroutine = pending.front();
                pending.pop_front();
                running.push_back(coroutine);
            }
        }
        if (coroutine == nullptr) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            continue;
        }
        tlsCurrent = coroutine;
        current = coroutine;
        schedulerCtx.switchContext(coroutine->ctx);
        tlsCurrent = nullptr;
        current = nullptr;
        if (coroutine->finished) {
            std::free(coroutine->stack);
            delete coroutine;
        } else {
            std::lock_guard lk(mtx);
            pending.push_back(coroutine);
        }
    }
}

void Lgs_Scheduler::spawn(void (*fn)(void*), void* arg) {
    auto* co = makeCoroutine(fn, arg);
    std::lock_guard lk(mtx);
    pending.push_back(co);
}

void yield() {
    if (tlsCurrent == nullptr) return;
    tlsCurrent->ctx.switchContext(schedulerCtx);
}

void Lgs_Scheduler::shutdown() {
    active = false;
    if (thread.joinable()) thread.join();
    constexpr itimerval it{};
    setitimer(ITIMER_REAL, &it, nullptr);
}
