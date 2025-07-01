#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "utils/LgsUtils.h"

class LgsNullValue final : public LgsUnaryExpr {
public:
    explicit LgsNullValue() : LgsUnaryExpr(nullptr) {
        isNull = true;
    }
    Value* createIRValue(LgsModule* runtime) override;
};

inline Value* LgsNullValue::createIRValue(LgsModule* runtime) {
    return ConstantPointerNull::get(ptrTy(runtime->context));
}
