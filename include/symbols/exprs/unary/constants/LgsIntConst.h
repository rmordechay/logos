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
    Value* createIRValue(LgsModule* runtime) override;
    LgsExpr* convertExpr(LgsType* toType) override;
    Value* andIR(LgsModule* runtime, LgsExpr* other) override;
    Value* orIR(LgsModule* runtime, LgsExpr* other) override;
    Value* bitAndIR(LgsModule* runtime, LgsExpr* other) override;
    Value* bitOrIR(LgsModule* runtime, LgsExpr* other) override;
    Value* bitXorIR(LgsModule* runtime, LgsExpr* other) override;
    Value* rshiftIR(LgsModule* runtime, LgsExpr* other) override;
    Value* lshiftIR(LgsModule* runtime, LgsExpr* other) override;
    LgsExpr* clone() override;
    ~LgsIntConst() override = default;
};


