#pragma once
#include "LgsForLoop.h"
#include <exprs/unary/LgsUnaryExpr.h>

class LgsDArrayType;

class LgsForeachLoop final : public LgsForLoop {
public:
    Value* iterPtr = nullptr;
    LgsUnaryExpr* iterExpr = nullptr;

    explicit LgsForeachLoop(LgsUnaryExpr* iterable) : iterExpr(iterable) {}
    Value* loopStart(LgsLLVMGen& cg) override;
    Value* loopEnd(LgsLLVMGen& cg) override;
    ~LgsForeachLoop() override;
};


