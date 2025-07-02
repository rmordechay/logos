#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/primitives/LgsUInt.h"

class LgsUIntConst final : public LgsUnaryExpr {
public:
    int value;

    explicit LgsUIntConst(const int value) : LgsUnaryExpr(&LGS_UINT), value(value) {}
    string prettyName() override;
    Value* createIRValue(LgsModule* module) override;
    LgsExpr* convertExpr(LgsType* toType) override;
    Value* eqIR(LgsModule* module, LgsExpr* other) override;
    Value* neIR(LgsModule* module, LgsExpr* other) override;
    Value* gtIR(LgsModule* module, LgsExpr* other) override;
    Value* ltIR(LgsModule* module, LgsExpr* other) override;
    Value* geIR(LgsModule* module, LgsExpr* other) override;
    Value* leIR(LgsModule* module, LgsExpr* other) override;
    Value* andIR(LgsModule* module, LgsExpr* other) override;
    Value* orIR(LgsModule* module, LgsExpr* other) override;
    Value* bitAndIR(LgsModule* module, LgsExpr* other) override;
    Value* bitOrIR(LgsModule* module, LgsExpr* other) override;
    Value* bitXorIR(LgsModule* module, LgsExpr* other) override;
    Value* rshiftIR(LgsModule* module, LgsExpr* other) override;
    Value* lshiftIR(LgsModule* module, LgsExpr* other) override;
    LgsExpr* clone() override;
    ~LgsUIntConst() override = default;
};


