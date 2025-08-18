#include "Lgs_runtime.h"

extern "C" void Lgs_Vtable_add(void* instancePtr, const char* name, void* ptr) {
    runtime.vtable[instancePtr].emplace(name, ptr);
}

extern "C" void* Lgs_Vtable_get(void* instancePtr, const char* name) {
    return runtime.vtable[instancePtr][name];
}

extern "C" void Lgs_Stack_push() {
    runtime.stack.push();
}

extern "C" void Lgs_Stack_pop() {
    runtime.stack.pop();
}

extern "C" void Lgs_Stack_addDefer(void* funcPtr, void* ctx) {
    runtime.stack.addDefer(funcPtr, ctx);
}

extern "C" void Lgs_Stack_addCoro(void* funcPtr, void* ctx) {
    runtime.stack.addCoro(funcPtr, ctx);
}

extern "C" void Lgs_Stack_callDefers() {
    runtime.stack.callDefers();
}

extern "C" void Lgs_Scheduler_run() {
    runtime.scheduler.run();
}

extern "C" void Lgs_Scheduler_spawn(void (*task)(void*), void* userdata) {
    runtime.scheduler.spawn(task, userdata);
}

extern "C" void Lgs_Scheduler_init(const int hz) {
    runtime.scheduler.init(hz);
}

extern "C" void Lgs_Scheduler_yield() {
    runtime.scheduler.yield();
}

extern "C" void Lgs_Scheduler_shutdown() {
    runtime.scheduler.shutdown();
}
