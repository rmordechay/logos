#pragma once
#include "LgsForLoop.h"
#include <exprs/unary/LgsUnaryExpr.h>

class LgsDArrayType;

class LgsForeachLoop final : public LgsForLoop {
public:
    Value* iterPtr = nullptr;
    LgsUnaryExpr* iterExpr = nullptr;

    explicit LgsForeachLoop(LgsUnaryExpr* iterable) : iterExpr(iterable) {}
    Value* loopStart(LgsLLVM& codeGen) override;
    Value* loopEnd(LgsLLVM& codeGen) override;
    ~LgsForeachLoop() override;
};


