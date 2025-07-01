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
    void setArrIterVars(LgsModule* runtime, LgsArray* arr) const;
    void setMapIterVars(LgsModule* runtime, const LgsIterator& iterator) const;
    void setStrIterVars(LgsModule* runtime, LgsStr* str) const;
    void setLoopCondition(LgsModule* runtime);
    LoadInst* loadIPtr(LgsModule* runtime) const;
    Value* loopStart(LgsModule* runtime) override;
    Value* loopEnd(LgsModule* runtime) override;
    void initIPtr(LgsModule* runtime);
    void initIRLoop(LgsModule* runtime) override;
    void exitIRLoop(LgsModule* runtime) const override;
    ~LgsForeachLoop() override;
};


