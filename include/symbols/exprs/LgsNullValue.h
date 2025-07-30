#pragma once
#include "exprs/unary/LgsUnaryExpr.h"


class LgsNullValue final : public LgsUnaryExpr {
public:
    explicit LgsNullValue() : LgsUnaryExpr(nullptr) {
        isNull = true;
    }
    Value* createIRValue(LgsCodeGen* codeGen) override;
    string prettyName() override;
    ~LgsNullValue() override = default;
};

inline Value* LgsNullValue::createIRValue(LgsCodeGen* codeGen) {
    return ConstantPointerNull::get(codeGen->ptrTy());
}

inline string LgsNullValue::prettyName() {
    return "null";
}