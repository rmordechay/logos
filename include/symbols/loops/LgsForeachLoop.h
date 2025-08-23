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
    void setArrIterVars(LgsCodeGen& codeGen, LgsDArray* arr) const;
    void setMapIterVars(LgsCodeGen& codeGen, const LgsIterator& iterator) const;
    void setStrIterVars(LgsCodeGen& codeGen, const LgsStr* str) const;
    ~LgsForeachLoop() override;
};


