#pragma once
#include "LgsUnaryExpr.h"
#include "exprs/LgsExpr.h"
#include "types/LgsDArray.h"
#include "types/LgsSArray.h"

class LgsArrayExpr final : public LgsUnaryExpr {
public:
    vector<LgsExpr*> initialElements;

    LgsArrayExpr() = default;
    explicit LgsArrayExpr(LgsSArray* arrType) : LgsUnaryExpr(arrType) {}
    explicit LgsArrayExpr(LgsDArray* arrType) : LgsUnaryExpr(arrType) {
        isHeapAlloc = true;
    }
    string prettyName() override;
    Value* createIRValue(LgsCodeGen* codeGen) override;
    Value* createConstArray(LgsCodeGen* codeGen) const;
    Value* createDynamicArray(LgsCodeGen* codeGen);
    void free(LgsCodeGen* codeGen) override;
    ~LgsArrayExpr() override = default;
};
