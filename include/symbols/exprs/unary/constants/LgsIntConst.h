#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/primitives/LgsInt.h"

class LgsIntConst final : public LgsUnaryExpr {
public:
    int value;

    explicit LgsIntConst(const int value) : LgsUnaryExpr(&LGS_INT), value(value) {
        isStatic = true;
    }
    string prettyName() override;
    Value* createIRValue(LgsModule* module) override;
    LgsExpr* convertExpr(LgsType* toType) override;
    Value* andIR(LgsModule* module, LgsExpr* other) override;
    Value* orIR(LgsModule* module, LgsExpr* other) override;
    Value* bitAndIR(LgsModule* module, LgsExpr* other) override;
    Value* bitOrIR(LgsModule* module, LgsExpr* other) override;
    Value* bitXorIR(LgsModule* module, LgsExpr* other) override;
    Value* rshiftIR(LgsModule* module, LgsExpr* other) override;
    Value* lshiftIR(LgsModule* module, LgsExpr* other) override;
    LgsExpr* clone() override;
    ~LgsIntConst() override = default;
};


