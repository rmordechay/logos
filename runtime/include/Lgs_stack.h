#pragma once
#include "Lgs_stack.h"
#include "Lgs_types.h"
#include "data/LgsConfigs.h"

typedef void (*Lgs_Defer_Func)(void*);

struct Lgs_Thunk_Func {
    Lgs_Defer_Func func;
    void* ctx;
};

struct Lgs_alloc {
    void* ptr;
    Lgs_rttype type;
};

struct Lgs_stack_frame {
    Lgs_alloc owners[LOCALS_CAPACITY];
    Lgs_alloc orphans[LOCALS_CAPACITY];
    Lgs_Thunk_Func defers[LOCALS_CAPACITY];
    size_t defersCount = 0;
    size_t ownersCount = 0;
    size_t orphansCount = 0;
};

struct Lgs_stack {
    int stackIndex;
    Lgs_stack_frame frames[STACK_CAPACITY];

    void push();
    void pop(bool cleanup);
    void callDefers() const;
    void addDefer(void* funcPtr, void* ctx);
    void addOwner(void* ptr, Lgs_rttype type);
    void addOrphan(void* ptr, Lgs_rttype type);
    void removeOwner(const void* owner);
    void funcCleanup();
};
