#include "Lgs_Scheduler.h"
#include <atomic>
#include <csignal>
#include <sys/time.h>
#include <thread>
#include <mutex>
#include <chrono>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cstring>

#define STACK_INIT_SIZE 4096
#define QUANTUM 10000

Lgs_Context schedulerCtx{};
std::atomic preempt{false};
Lgs_Coroutine* current = nullptr;
thread_local Lgs_Coroutine* tlsCurrent = nullptr;

static void onTick(int) {
    preempt.store(true, std::memory_order_relaxed);
}

void growStack(Lgs_Coroutine* co) {
    const auto newSize = co->stackSize * 2;
    const auto newStack = std::malloc(newSize + STACK_INIT_SIZE);
    std::memcpy(
        static_cast<char*>(newStack) + STACK_INIT_SIZE,
        static_cast<char*>(co->stack) + STACK_INIT_SIZE,
        co->stackSize
        );
    const auto oldBase = reinterpret_cast<uintptr_t>(co->stack) + STACK_INIT_SIZE;
    const auto newBase = reinterpret_cast<uintptr_t>(newStack) + STACK_INIT_SIZE;
    const auto spOffset = reinterpret_cast<uintptr_t>(co->ctx.sp) - oldBase;
    co->ctx.sp = reinterpret_cast<void*>(newBase + spOffset);

    std::free(co->stack);
    co->stack = newStack;
    co->stackSize = newSize;
}

static void handleSig(const int sig, siginfo_t* info, void* ctx) {
    if (sig == SIGSEGV && tlsCurrent != nullptr) {
        const auto addr = reinterpret_cast<uintptr_t>(info->si_addr);
        const auto stackBase = reinterpret_cast<uintptr_t>(tlsCurrent->stack);
        // Check if fault is in guard page
        if (addr >= stackBase && addr < stackBase + STACK_INIT_SIZE) {
            growStack(tlsCurrent);
            return;
        }
    }
    signal(sig, SIG_DFL);
    raise(sig);
}

static void initSigHandler() {
    struct sigaction sa {};
    sa.sa_sigaction = handleSig;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO | SA_ONSTACK;
    sigaction(SIGSEGV, &sa, nullptr);
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
    switchContext(&tlsCurrent->ctx, &schedulerCtx);
}

void Lgs_Scheduler::start() {
    active = true;
    thread = std::thread([this] { loop(); });
}

void Lgs_Scheduler::loop() {
    initTimer();
    initSigHandler();
    while (active) {
        Lgs_Coroutine* coroutine = nullptr;
        {
            std::lock_guard lock(mtx);
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
        switchContext(&schedulerCtx, &coroutine->ctx);
        tlsCurrent = nullptr;
        current = nullptr;
        if (coroutine->finished) {
            std::free(coroutine->stack);
            delete coroutine;
        } else {
            std::lock_guard lock(mtx);
            pending.push_back(coroutine);
        }
    }
}

void Lgs_Scheduler::spawn(void (*fn)(void*), void* arg) {
    const auto co = new Lgs_Coroutine();
    co->stackSize = STACK_INIT_SIZE;
    co->stack = std::malloc(co->stackSize);
    co->fn = fn;
    co->arg = arg;
    co->finished = false;
    const auto top = static_cast<std::byte*>(co->stack) + co->stackSize;
    reset(&co->ctx, top, reinterpret_cast<void*>(coroutineEntry));
    std::lock_guard lk(mtx);
    pending.push_back(co);
}

bool Lgs_Scheduler::shouldYield() {
    return preempt.load(std::memory_order_relaxed);
}

void Lgs_Scheduler::yield() {
    if (tlsCurrent == nullptr) return;
    preempt.store(false, std::memory_order_relaxed);
    switchContext(&tlsCurrent->ctx, &schedulerCtx);
}

void Lgs_Scheduler::shutdown() {
    active = false;
    if (thread.joinable()) thread.join();
    constexpr itimerval it{};
    setitimer(ITIMER_REAL, &it, nullptr);
}
