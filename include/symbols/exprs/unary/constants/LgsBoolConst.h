#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/primitives/LgsBool.h"

class LgsBoolConst final : public LgsUnaryExpr {
public:
    bool value;

    explicit LgsBoolConst(const bool value) : LgsUnaryExpr(&LGS_BOOL), value(value) {}
    string getValueAsString() const;
    string prettyName() override;
    Value* createIRValue(LgsModule* module) override;
    Value* andIR(LgsModule* module, LgsExpr* other) override;
    Value* eqIR(LgsModule* module, LgsExpr* other) override;
    Value* neIR(LgsModule* module, LgsExpr* other) override;
    Value* ltIR(LgsModule* module, LgsExpr* other) override;
    Value* gtIR(LgsModule* module, LgsExpr* other) override;
    Value* geIR(LgsModule* module, LgsExpr* other) override;
    Value* leIR(LgsModule* module, LgsExpr* other) override;
    Value* orIR(LgsModule* module, LgsExpr* other) override;
    Value* bitAndIR(LgsModule* module, LgsExpr* other) override;
    Value* bitOrIR(LgsModule* module, LgsExpr* other) override;
    Value* bitXorIR(LgsModule* module, LgsExpr* other) override;
    Value* rshiftIR(LgsModule* module, LgsExpr* other) override;
    Value* lshiftIR(LgsModule* module, LgsExpr* other) override;
    ~LgsBoolConst() override = default;
};
