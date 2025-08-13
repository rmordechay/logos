#pragma once
#include "LgsCodeGen.h"

class LgsRuntime {
public:
    void setRuntime(LgsCodeGen* codeGen);
    ~LgsRuntime() = default;
};
