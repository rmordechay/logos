#pragma once
#include "Lgs_Stack.h"
#include "Lgs_Types.h"
#include "data/LgsConfigs.h"

typedef void (*Func)(void*);
struct Lgs_ThunkFunc {
    Func func;
    void* ctx;
};

struct Lgs_Alloc {
    void* ptr;
    Lgs_RTType type;
};

struct Lgs_StackFrame {
    Lgs_Alloc owners[LOCALS_CAPACITY];
    Lgs_Alloc orphans[LOCALS_CAPACITY];
    Lgs_ThunkFunc coros[LOCALS_CAPACITY];
    Lgs_ThunkFunc defers[LOCALS_CAPACITY];
    size_t ownersCount = 0;
    size_t orphansCount = 0;
    size_t corosCount = 0;
    size_t defersCount = 0;
};

struct Lgs_Stack {
    int stackIndex;
    Lgs_StackFrame frames[STACK_CAPACITY];

    void push();
    void pop(bool cleanup);
    void callDefers() const;
    void addCoro(void* funcPtr, void* ctx);
    void addDefer(void* funcPtr, void* ctx);
    void addOwner(void* ptr, Lgs_RTType type);
    void addOrphan(void* ptr, Lgs_RTType type);
    void removeOwner(const void* owner);
    void funcCleanup();
};
