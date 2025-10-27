#pragma once
#include "Lgs_Stack.h"
#include "Lgs_types.h"
#include "data/LgsConfigs.h"
#include <cstddef>
typedef void (*Lgs_DeferFunc)(void*);

struct Lgs_ThunkFunc {
    Lgs_DeferFunc func;
    void* ctx;
};

struct Lgs_Alloc {
    void* ptr;
    Lgs_rttype type;
};

struct Lgs_StackFrame {
    Lgs_Alloc owners[LOCALS_CAPACITY];
    Lgs_Alloc orphans[LOCALS_CAPACITY];
    Lgs_ThunkFunc defers[LOCALS_CAPACITY];
    size_t defersCount = 0;
    size_t ownersCount = 0;
    size_t orphansCount = 0;
};

struct Lgs_Stack {
    int stackIndex;
    Lgs_StackFrame frames[STACK_CAPACITY];

    void push();
    void pop(bool cleanup);
    void callDefers() const;
    void addDefer(void* funcPtr, void* ctx);
    void addOwner(void* ptr, Lgs_rttype type);
    void addOrphan(void* ptr, Lgs_rttype type);
    void removeOwner(const void* owner);
    void funcCleanup();
};
