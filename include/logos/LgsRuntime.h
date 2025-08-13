#pragma once
#include "LgsCodeGen.h"

class LgsRuntime {
public:
    GlobalVariable* runtimePtr = nullptr;
    ~LgsRuntime() = default;
    void setRuntime(LgsCodeGen* codeGen);
};
