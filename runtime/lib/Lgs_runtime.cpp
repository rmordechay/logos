#include "Lgs_scheduler.h"
#include "Lgs_stack.h"
#include "Lgs_types.h"

#include <sqlite3.h>

struct Lgs_Alloc {
    void* ptr;
    Lgs_RTType type;
};

struct Lgs_runtime {
    Lgs_Stack stack;
    Lgs_Scheduler scheduler;
    std::map<void*, std::map<std::string, void*>> vtable;
    std::vector<Lgs_Alloc> owners;
    std::vector<Lgs_Alloc> orphans;
    sqlite3* db;
    void init();
    void close();
};

static inline Lgs_runtime runtime;

extern "C" void Lgs_Runtime_init() {
    runtime.init();
}

extern "C" void Lgs_Runtime_addOwner(void* ptr, const Lgs_RTType type) {
    runtime.owners.push_back(Lgs_Alloc{.ptr = ptr, .type = type});
}

extern "C" void Lgs_Runtime_addOrphan(void* ptr, const Lgs_RTType type) {
    runtime.orphans.push_back(Lgs_Alloc{.ptr = ptr, .type = type});
}

extern "C" void Lgs_Runtime_removeOwner(const void* owner) {
    for (auto it = runtime.owners.begin(); it != runtime.owners.end(); ) {
        if (it->ptr == owner) {
            it = runtime.owners.erase(it);
        } else {
            ++it;
        }
    }
}

extern "C" void Lgs_Runtime_funcCleanup() {
    for (const auto [ptr, type] : runtime.owners) {
        std::cout << ptr << std::endl;
        std::cout << type << std::endl;
    }
    for (const auto [ptr, type] : runtime.orphans) {
        std::cout << ptr << std::endl;
        std::cout << type << std::endl;
    }
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

void Lgs_runtime::init() {
    // scheduler.run();
    //sqlite3_open(":memory:", &runtime.db);
}

void Lgs_runtime::close() {
    // scheduler.shutdown();
    // sqlite3_close(runtime.db);
}