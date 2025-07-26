#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "utils/LgsIRUtils.h"

class LgsNullValue final : public LgsUnaryExpr {
public:
    explicit LgsNullValue() : LgsUnaryExpr(nullptr) {
        isNull = true;
    }
    Value* createIRValue(LgsModule* module) override;
    string prettyName() override;
    ~LgsNullValue() override = default;
};

inline Value* LgsNullValue::createIRValue(LgsModule* module) {
    return ConstantPointerNull::get(ptrTy(module));
}

inline string LgsNullValue::prettyName() {
    return "null";
}