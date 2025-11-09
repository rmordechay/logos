#include "Lgs_Arena.h"
#include "Lgs_DArray.h"
#include "Lgs_Scheduler.h"
#include "Lgs_Stack.h"
#include "Lgs_Types.h"
#include <cassert>
#include <map>
#include "Lgs_Map.h"
#include "Lgs_Helpers.h"
#include <iostream>
#include <string>
#include <unistd.h>

struct Lgs_Runtime {
    Lgs_Stack stack;
    Lgs_Arena arena;
    Lgs_Scheduler scheduler;
    std::map<void*, std::map<std::string, void*>> vtable;
};

static inline Lgs_Runtime runtime;

extern "C" void Lgs_Runtime_init() {
    // runtime.scheduler.start();
}

extern "C" void Lgs_Runtime_close() {
    // runtime.scheduler.shutdown();
}

extern "C" void Lgs_Runtime_addOwner(void* ptr, const Lgs_RTType type) {
    const auto ownerIndex = runtime.stack.frames[runtime.stack.stackIndex].ownersCount++;
    runtime.stack.frames[runtime.stack.stackIndex].owners[ownerIndex] = Lgs_Alloc{ptr, type};
}

extern "C" void Lgs_Runtime_addOrphan(void* ptr, const Lgs_RTType type) {
    const auto ownerIndex = runtime.stack.frames[runtime.stack.stackIndex].orphansCount++;
    runtime.stack.frames[runtime.stack.stackIndex].orphans[ownerIndex] = Lgs_Alloc{ptr, type};
}

extern "C" void Lgs_Runtime_addDefer(void* funcPtr, void* ctx) {
    const auto deferFunc = reinterpret_cast<Thunk>(funcPtr);
    const auto deferIndex = runtime.stack.frames[runtime.stack.stackIndex].defersCount++;
    runtime.stack.frames[runtime.stack.stackIndex].defers[deferIndex] = Lgs_ThunkFunc{deferFunc, ctx};
}

extern "C" void Lgs_Runtime_removeOwner(const void* owner) {
    auto& stackFrame = runtime.stack.frames[runtime.stack.stackIndex];
    for (size_t i = 0; i < stackFrame.ownersCount; i++) {
        if (stackFrame.owners[i].ptr != owner) continue;
        freeRTType(stackFrame.owners[i].ptr, stackFrame.owners[i].type);
        for (size_t j = i; j < stackFrame.ownersCount - 1; j++) {
            stackFrame.owners[j] = stackFrame.owners[j + 1];
        }
        break;
    }
}

extern "C" void Lgs_Runtime_push() {
    runtime.stack.stackIndex++;
}

extern "C" void Lgs_Runtime_pop(const bool cleanup) {
    if (cleanup) funcCleanup(runtime.stack);
    runtime.stack.stackIndex--;
}

extern "C" void Lgs_Runtime_callDefers() {
    const auto& top = runtime.stack.frames[runtime.stack.stackIndex];
    for (size_t i = 0; i < LOCALS_CAPACITY; ++i) {
        const auto [func, ctx] = top.defers[i];
        if (!func) continue;
        func(ctx);
    }
}

extern "C" void Lgs_Runtime_addCoro(void* funcPtr, void* ctx) {
    runtime.scheduler.spawn(reinterpret_cast<Thunk>(funcPtr), ctx);
}

extern "C" void Lgs_Runtime_yield() {
    runtime.scheduler.yield();
}

extern "C" bool Lgs_Runtime_shouldYield() {
    return runtime.scheduler.shouldYield();
}

extern "C" void Lgs_Runtime_addToVTable(void* instancePtr, const char* name, void* ptr) {
    runtime.vtable[instancePtr].emplace(name, ptr);
}

extern "C" void* Lgs_Runtime_getFromVTable(void* instancePtr, const char* name) {
    const auto instance = runtime.vtable.find(instancePtr);
    if (instance == runtime.vtable.end()) assert(0);
    const auto method = instance->second.find(name);
    if (method == instance->second.end()) assert(0);
    return method->second;
}

extern "C" void* Lgs_Runtime_allocate(const size_t size) {
    return runtime.arena.allocate(size);
}

extern "C" void Lgs_rttest(const size_t index) {
    // const auto a = &Lgs_RTTypes[index];
    // for (int i = 0; i < a->fieldCount; ++i) {
    //     const auto v = a->fieldTypes[i];
    //     std::cout << getTypeName(v) << '\n';
    // }
    // assert(0);
}
