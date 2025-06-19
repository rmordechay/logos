#pragma once
#include "exprs/unary/LgsUnaryExpr.h"

class LgsNullValue final : public LgsUnaryExpr {
public:
    explicit LgsNullValue() : LgsUnaryExpr(nullptr) {
        isNull = true;
    }
    Value* createIRValue(LgsRuntime* runtime) override;
};

inline Value* LgsNullValue::createIRValue(LgsRuntime* runtime) {
    return ConstantPointerNull::get(PointerType::getUnqual(context));
}
