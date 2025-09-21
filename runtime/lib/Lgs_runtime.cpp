#include "Lgs_darray.h"
#include "Lgs_scheduler.h"
#include "Lgs_stack.h"
#include "Lgs_types.h"
#include <sqlite3.h>

struct Lgs_darray;

struct Lgs_alloc {
    void* ptr;
    Lgs_RTType type;
};

struct Lgs_runtime {
    Lgs_stack stack;
    Lgs_scheduler scheduler;
    std::map<void*, std::map<std::string, void*>> vtable;
    std::vector<Lgs_alloc> owners;
    std::vector<Lgs_alloc> orphans;
    sqlite3* db;
    void init();
    void close();
};

static inline Lgs_runtime runtime;

void freeType(void* ptr, const Lgs_RTType type) {
    std::cout << "Freeing: " << ptr << std::endl;
    switch (type) {
    case RTT_UNKNOWN:
    case RTT_VOID:
    case RTT_BOOL:
    case RTT_CHAR:
    case RTT_FLOAT:
    case RTT_DOUBLE:
    case RTT_INT:
    case RTT_VEC2:
    case RTT_VEC3:
    case RTT_VEC4:
    case RTT_LONG:
    case RTT_SIZE:
    case RTT_STR:
        return;
    case RTT_SARRAY:
    case RTT_TYPE:
        break;
        assert(0);
    case RTT_OBJECT: {
        // std::free(ptr);
        break;
    }
    case RTT_DARRAY: {
        const auto arr = static_cast<Lgs_darray*>(ptr);
        delete arr->data;
        std::free(arr);
        break;
    }
    }
}

extern "C" void Lgs_runtime_init() {
    runtime.init();
}

extern "C" void Lgs_runtime_addOwner(void* ptr, const Lgs_RTType type) {
    std::cout << "malloc: " << ptr << std::endl;
    runtime.owners.push_back(Lgs_alloc{.ptr = ptr, .type = type});
}

extern "C" void Lgs_runtime_addOrphan(void* ptr, const Lgs_RTType type) {
    std::cout << "malloc: " << ptr << std::endl;
    runtime.orphans.push_back(Lgs_alloc{.ptr = ptr, .type = type});
}

extern "C" void Lgs_runtime_removeOwner(const void* owner) {
    for (auto it = runtime.owners.begin(); it != runtime.owners.end(); ) {
        if (it->ptr == owner) {
            freeType(it->ptr, it->type);
            it = runtime.owners.erase(it);
        } else {
            ++it;
        }
    }
}

extern "C" void Lgs_runtime_funcCleanup() {
    std::cout << "Owners:" << std::endl;
    for (const auto [ptr, type] : runtime.owners) {
        freeType(ptr, type);
    }
    std::cout << "Orpahns:" << std::endl;
    for (const auto [ptr, type] : runtime.orphans) {
        freeType(ptr, type);
    }
    runtime.owners.clear();
    runtime.orphans.clear();
}

extern "C" void Lgs_stack_push() {
    runtime.stack.push();
}

extern "C" void Lgs_stack_pop() {
    runtime.stack.pop();
}

extern "C" void Lgs_stack_addDefer(void* funcPtr, void* ctx) {
    runtime.stack.addDefer(funcPtr, ctx);
}

extern "C" void Lgs_stack_addCoro(void* funcPtr, void* ctx) {
    runtime.stack.addCoro(funcPtr, ctx);
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

extern "C" void Lgs_scheduler_shutdown() {
    runtime.scheduler.shutdown();
}

extern "C" void Lgs_vtable_add(void* instancePtr, const char* name, void* ptr) {
    runtime.vtable[instancePtr].emplace(name, ptr);
}

extern "C" void* Lgs_vtable_get(void* instancePtr, const char* name) {
    return runtime.vtable[instancePtr][name];
}

void Lgs_runtime::init() {
    scheduler.run();
    //sqlite3_open(":memory:", &runtime.db);
}

void Lgs_runtime::close() {
    scheduler.shutdown();
    // sqlite3_close(runtime.db);
}