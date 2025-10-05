#include "Lgs_scheduler.h"
#include "Lgs_stack.h"
#include "Lgs_types.h"
#include <sqlite3.h>

struct Lgs_darray;

struct Lgs_runtime {
    Lgs_stack stack;
    Lgs_scheduler scheduler;
    std::map<void*, std::map<std::string, void*>> vtable;
    sqlite3* db;
};

static inline Lgs_runtime runtime;

extern "C" void Lgs_runtime_init() {
    // runtime.scheduler.start();
    //sqlite3_open(":memory:", &runtime.db);
}

extern "C" void Lgs_runtime_close() {
    // runtime.scheduler.shutdown();
    // sqlite3_close(runtime.db);
}

extern "C" void Lgs_stack_addOwner(void* ptr, const Lgs_RTType type) {
    runtime.stack.addOwner(ptr, type);
}

extern "C" void Lgs_stack_addOrphan(void* ptr, const Lgs_RTType type) {
    runtime.stack.addOrphan(ptr, type);
}

extern "C" void Lgs_stack_removeOwner(const void* owner) {
    runtime.stack.removeOwner(owner);
}

extern "C" void Lgs_stack_push() {
    runtime.stack.push();
}

extern "C" void Lgs_stack_pop(const bool cleanup) {
    runtime.stack.pop(cleanup);
}

extern "C" void Lgs_stack_addDefer(void* funcPtr, void* ctx) {
    runtime.stack.addDefer(funcPtr, ctx);
}

extern "C" void Lgs_stack_addCoro(void* funcPtr, void* ctx) {
    const auto thunk = reinterpret_cast<Lgs_Defer_Func>(funcPtr);
    runtime.scheduler.spawn(thunk, ctx);
}

extern "C" void Lgs_stack_callDefers() {
    runtime.stack.callDefers();
}

extern "C" void Lgs_scheduler_spawn(void (*task)(void*), void* ctx) {
    runtime.scheduler.spawn(task, ctx);
}

extern "C" void Lgs_scheduler_yield() {
    runtime.scheduler.yield();
}

extern "C" bool Lgs_scheduler_shouldYield() {
    return runtime.scheduler.shouldYield();
}

extern "C" void Lgs_scheduler_shutdown() {
    runtime.scheduler.shutdown();
}

extern "C" void Lgs_vtable_add(void* instancePtr, const char* name, void* ptr) {
    std::cout << "inserting " << instancePtr << '\n';
    runtime.vtable[instancePtr].emplace(name, ptr);
}

extern "C" void* Lgs_vtable_get(void* instancePtr, const char* name) {
    const auto instance = runtime.vtable.find(instancePtr);
    if (instance == runtime.vtable.end()) assert(0);
    const auto method = instance->second.find(name);
    if (method == instance->second.end()) assert(0);
    return method->second;
}
