#pragma once
#include "Lgs_Stack.h"
#include "Lgs_Types.h"
#include <execinfo.h>
#include <dlfcn.h>
#include <ostream>
#include <stack>

#define STACK_CAPACITY 1024
#define LOCALS_CAPACITY 8

struct Lgs_HashMap;
struct Lgs_SetExpr;
struct Lgs_DArrayExpr;
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
    std::array<Lgs_Alloc, LOCALS_CAPACITY> owners{};
    std::array<Lgs_Alloc, LOCALS_CAPACITY> orphans{};
    std::array<Lgs_ThunkFunc, LOCALS_CAPACITY> coros{};
    std::array<Lgs_ThunkFunc, LOCALS_CAPACITY> defers{};
    size_t ownersCount = 0;
    size_t orphansCount = 0;
    size_t corosCount = 0;
    size_t defersCount = 0;
};

struct Lgs_Stack {
    std::stack<Lgs_StackFrame> stack;

    void addDefer(void* funcPtr, void* ctx);
    void addCoro(void* funcPtr, void* ctx);
    void callDefers() const;
    void addOwner(void* ptr, Lgs_TypeKind type);
    void addOrphan(void* ptr, Lgs_TypeKind type);
    void removeOwner(const void* owner);
    void funcCleanup();
};
