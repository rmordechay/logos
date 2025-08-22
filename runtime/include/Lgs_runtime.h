#pragma once
#include "Lgs_scheduler.h"
#include "Lgs_stack.h"
#include <sqlite3.h>

struct Lgs_runtime {
    Lgs_Stack stack;
    Lgs_Scheduler scheduler;
    std::map<void*, std::map<std::string, void*>> vtable;
    sqlite3* db;

    void init();
    void initDB();
};
