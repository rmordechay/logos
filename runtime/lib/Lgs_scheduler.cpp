#include "Lgs_scheduler.h"
#include <csignal>
#include <sys/time.h>
#include <chrono>

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
    constexpr auto hz = 1000;  // 1ms intervals
    it.it_interval.tv_sec = 0;
    it.it_interval.tv_usec = 1000000 / hz;
    it.it_value = it.it_interval;
    setitimer(ITIMER_REAL, &it, nullptr);
}

void Lgs_scheduler::start() {
    running = true;
    schedulerThread = std::thread([this] {
        this->run();
    });
}

void Lgs_scheduler::run() {
    initSignals();
    while (running) {
        {
            std::lock_guard lock(mtx);
            while (!pendingTasks.empty()) {
                auto taskInfo = pendingTasks.front();
                pendingTasks.pop_front();
                auto c = boost::context::callcc(
                    [taskInfo](continuation&& scheduler_cont) mutable {
                        tlsYield = [&scheduler_cont]() mutable {
                            scheduler_cont = std::move(scheduler_cont).resume();
                        };
                        // Run the task
                        taskInfo.task(taskInfo.ctx);
                        // Return to scheduler
                        return std::move(scheduler_cont);
                    }
                );
                // If task didn't complete immediately, add to active tasks
                if (c) {
                    activeTasks.push_back(std::move(c));
                }
            }
        }

        // Process one active task
        continuation currentTask;
        bool hasTask = false;
        {
            std::lock_guard lock(mtx);
            if (!activeTasks.empty()) {
                currentTask = std::move(activeTasks.front());
                activeTasks.pop_front();
                hasTask = true;
            }
        }

        if (hasTask) {
            // Resume task without holding lock
            currentTask = std::move(currentTask).resume();
            // Put incomplete task back in queue
            if (currentTask) {
                std::lock_guard lock(mtx);
                activeTasks.push_back(std::move(currentTask));
            }
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
}

void Lgs_scheduler::spawn(void (*task)(void*), void* ctx) {
    std::lock_guard lock(mtx);
    pendingTasks.push_back({task, ctx});
}

bool Lgs_scheduler::shouldYield() {
    return preempt.load(std::memory_order_relaxed);
}

void Lgs_scheduler::yield() {
    if (preempt.exchange(false, std::memory_order_relaxed)) {
        if (tlsYield) {
            tlsYield();
        }
    }
}

void Lgs_scheduler::shutdown() {
    constexpr itimerval it{};
    setitimer(ITIMER_REAL, &it, nullptr);
    running = false;
    if (schedulerThread.joinable()) {
        schedulerThread.join();
    }
}