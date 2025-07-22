#pragma once
#include "LgsUnaryExpr.h"
#include "exprs/LgsExpr.h"
#include "types/LgsDArray.h"
#include "types/LgsSArray.h"

class LgsArrayExpr final : public LgsUnaryExpr {
public:
    vector<LgsExpr*> initialElements;

    LgsArrayExpr() = default;
    explicit LgsArrayExpr(LgsDArray* arrType) : LgsUnaryExpr(arrType) {}
    explicit LgsArrayExpr(LgsSArray* arrType) : LgsUnaryExpr(arrType) {}
    string prettyName() override;
    Value* createIRValue(LgsModule* module) override;
    Value* createConstArray(LgsModule* module) const;
    Value* createDynamicArray(LgsModule* module);
    void free(LgsModule* module) override;
    ~LgsArrayExpr() override = default;
};
