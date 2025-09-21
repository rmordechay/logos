#pragma once
#include "Lgs_stack.h"
#include "Lgs_types.h"
#include "logos/LgsAppConfigs.h"

typedef void (*Lgs_Defer_Func)(void*);

struct Lgs_Thunk_Func {
    Lgs_Defer_Func func;
    void* ctx;
};

struct Lgs_alloc {
    void* ptr;
    Lgs_RTType type;
};

struct Lgs_stack_frame {
    std::vector<Lgs_alloc> owners;
    std::vector<Lgs_alloc> orphans;
    Lgs_Thunk_Func defers[LOCALS_CAPACITY];
    int defersCount;
};

struct Lgs_stack {
    int stackIndex;
    Lgs_stack_frame frames[STACK_CAPACITY];

    void push();
    void pop();
    void callDefers() const;
    void addDefer(void* funcPtr, void* ctx);
    void addOwner(void* ptr, Lgs_RTType type);
    void addOrphan(void* ptr, Lgs_RTType type);
    void removeOwner(const void* owner) const;
    void funcCleanup() const;
};
