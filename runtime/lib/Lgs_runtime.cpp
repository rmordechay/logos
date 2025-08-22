#include "Lgs_runtime.h"

static inline Lgs_runtime runtime;

extern "C" void Lgs_Runtime_init() {
    runtime.init();
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

extern "C" void Lgs_Scheduler_spawn(void (*task)(void*), void* ctx) {
    runtime.scheduler.spawn(task, ctx);
}

extern "C" void Lgs_Scheduler_yield() {
    runtime.scheduler.yield();
}

extern "C" void Lgs_Scheduler_shutdown() {
    runtime.scheduler.shutdown();
}

extern "C" void Lgs_Vtable_add(void* instancePtr, const char* name, void* ptr) {
    runtime.vtable[instancePtr].emplace(name, ptr);
}

extern "C" void* Lgs_Vtable_get(void* instancePtr, const char* name) {
    return runtime.vtable[instancePtr][name];
}

extern "C" void initDB() {
    sqlite3_open(":memory:", &runtime.db);
}

extern "C" void closeDB() {
    sqlite3_close(runtime.db);
}

void Lgs_runtime::init() {
    scheduler.run();
}