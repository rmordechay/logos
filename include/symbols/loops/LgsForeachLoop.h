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
    void setArrIterVars(LgsModule* module, LgsDArray* arr) const;
    void setMapIterVars(LgsModule* module, const LgsIterator& iterator) const;
    void setStrIterVars(LgsModule* module, LgsStr* str) const;
    void setLoopCondition(LgsModule* module);
    LoadInst* loadIPtr(LgsModule* module) const;
    void initIPtr(LgsModule* module);
    Value* loopStart(LgsModule* module) override;
    Value* loopEnd(LgsModule* module) override;
    void initIRLoop(LgsModule* module) override;
    void exitIRLoop(LgsModule* module) const override;
    ~LgsForeachLoop() override;
};


