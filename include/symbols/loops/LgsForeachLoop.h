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
    void setArrIterVars(LgsCodeGen* codeGen, LgsDArray* arr) const;
    void setMapIterVars(LgsCodeGen* codeGen, const LgsIterator& iterator) const;
    void setStrIterVars(LgsCodeGen* codeGen, LgsStr* str) const;
    LoadInst* loadIPtr(LgsCodeGen* codeGen) const;
    void initIPtr(LgsCodeGen* codeGen);
    Value* loopStart(LgsCodeGen* codeGen) override;
    Value* loopEnd(LgsCodeGen* codeGen) override;
    void initIRLoop(LgsCodeGen* codeGen) override;
    void IRLoopPrologue(LgsCodeGen* codeGen) const override;
    ~LgsForeachLoop() override;
};


