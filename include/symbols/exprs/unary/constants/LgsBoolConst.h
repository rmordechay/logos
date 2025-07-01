#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/primitives/LgsBool.h"

class LgsBoolConst final : public LgsUnaryExpr {
public:
    bool value;

    explicit LgsBoolConst(const bool value) : LgsUnaryExpr(&LGS_BOOL), value(value) {}
    string getValueAsString() const;
    Value* createIRValue(LgsModule* runtime) override;
    Value* andIR(LgsModule* runtime, LgsExpr* other) override;
    Value* eqIR(LgsModule* runtime, LgsExpr* other) override;
    Value* neIR(LgsModule* runtime, LgsExpr* other) override;
    Value* ltIR(LgsModule* runtime, LgsExpr* other) override;
    Value* gtIR(LgsModule* runtime, LgsExpr* other) override;
    Value* geIR(LgsModule* runtime, LgsExpr* other) override;
    Value* leIR(LgsModule* runtime, LgsExpr* other) override;
    Value* orIR(LgsModule* runtime, LgsExpr* other) override;
    Value* bitAndIR(LgsModule* runtime, LgsExpr* other) override;
    Value* bitOrIR(LgsModule* runtime, LgsExpr* other) override;
    Value* bitXorIR(LgsModule* runtime, LgsExpr* other) override;
    Value* rshiftIR(LgsModule* runtime, LgsExpr* other) override;
    Value* lshiftIR(LgsModule* runtime, LgsExpr* other) override;
    ~LgsBoolConst() override = default;
};
