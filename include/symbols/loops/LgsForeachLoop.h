#pragma once
#include "LgsForLoop.h"
#include <exprs/unary/LgsUnaryExpr.h>

class LgsDArrayType;

class LgsForeachLoop final : public LgsForLoop {
public:
    Value* iterPtr = nullptr;
    bool withIndex = false;
    LgsUnaryExpr* iterExpr = nullptr;

    explicit LgsForeachLoop(LgsUnaryExpr* iterable) : iterExpr(iterable) {}
    void setIterVars(LgsRuntime* runtime, LgsStr* str) const;
    void setIterVars(LgsRuntime* runtime, LgsArray* arr) const;
    void setIterVars(LgsRuntime* runtime, LgsMap* map) const;
    Value* loopStart(LgsRuntime* runtime) override;
    Value* loopEnd(LgsRuntime* runtime) override;
    void initIRLoop(LgsRuntime* runtime) override;
    void exitIRLoop(LgsRuntime* runtime) const override;
    ~LgsForeachLoop() override;
};


