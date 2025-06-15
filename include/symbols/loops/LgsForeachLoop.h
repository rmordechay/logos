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
    void setArrIterVars(LgsRuntime* runtime, LgsArray* arr) const;
    void setMapIterVars(LgsRuntime* runtime, const LgsIterator& iterator) const;
    void setStrIterVars(LgsRuntime* runtime, LgsStr* str) const;
    void setLoopCondition(LgsRuntime* runtime);
    LoadInst* loadIPtr(LgsRuntime* runtime) const;
    Value* loopStart(LgsRuntime* runtime) override;
    Value* loopEnd(LgsRuntime* runtime) override;
    void initIPtr(LgsRuntime* runtime);
    void initIRLoop(LgsRuntime* runtime) override;
    void exitIRLoop(LgsRuntime* runtime) const override;
    ~LgsForeachLoop() override;
};


