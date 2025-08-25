#pragma once
#include "exprs/LgsExpr.h"

class LgsAssignable {
public:
    virtual void assign(LgsLLVM& codeGen, LgsExpr* expr) = 0;
    virtual ~LgsAssignable() = default;
};
