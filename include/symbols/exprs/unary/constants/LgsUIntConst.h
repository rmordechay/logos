#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/primitives/LgsUInt.h"

class LgsUIntConst final : public LgsUnaryExpr {
public:
    int value;

    explicit LgsUIntConst(const int value) : LgsUnaryExpr(&LGS_UINT), value(value) {}
    string prettyName() override;
    Value* createIRValue(LgsModule* runtime) override;
    LgsExpr* convertExpr(LgsType* toType) override;
    Value* eqIR(LgsModule* runtime, LgsExpr* other) override;
    Value* neIR(LgsModule* runtime, LgsExpr* other) override;
    Value* gtIR(LgsModule* runtime, LgsExpr* other) override;
    Value* ltIR(LgsModule* runtime, LgsExpr* other) override;
    Value* geIR(LgsModule* runtime, LgsExpr* other) override;
    Value* leIR(LgsModule* runtime, LgsExpr* other) override;
    Value* andIR(LgsModule* runtime, LgsExpr* other) override;
    Value* orIR(LgsModule* runtime, LgsExpr* other) override;
    Value* bitAndIR(LgsModule* runtime, LgsExpr* other) override;
    Value* bitOrIR(LgsModule* runtime, LgsExpr* other) override;
    Value* bitXorIR(LgsModule* runtime, LgsExpr* other) override;
    Value* rshiftIR(LgsModule* runtime, LgsExpr* other) override;
    Value* lshiftIR(LgsModule* runtime, LgsExpr* other) override;
    LgsExpr* clone() override;
    ~LgsUIntConst() override = default;
};


