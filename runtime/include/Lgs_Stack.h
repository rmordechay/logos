#pragma once
#include "Lgs_Stack.h"
#include "Lgs_Types.h"
#include "../../include/logos/LgsConfigs.h"

typedef void (*Thunk)(void*);

struct Lgs_ThunkFunc {
    Thunk func;
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
};
