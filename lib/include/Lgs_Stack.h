#pragma once
#include "Lgs_Stack.h"
#include "Lgs_Types.h"
#include <execinfo.h>
#include <dlfcn.h>
#include <ostream>

#define STACK_CAPACITY 1024
#define LOCALS_CAPACITY 8

struct Lgs_Map;
struct Lgs_Set;
struct Lgs_DArray;
typedef void (*ThunkFunc)(void*);

struct Lgs_ThunkFunc {
    ThunkFunc func;
    void* ctx;
};

struct Lgs_Alloc {
    void* ptr;
    Lgs_TypeKind type;
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
    void addDefer(void* funcPtr, void* ctx);
    void callDefers() const;
    void addOwner(void* ptr, Lgs_TypeKind type);
    void addOrphan(void* ptr, Lgs_TypeKind type);
    void removeOwner(const void* owner);
    void funcCleanup();
};
