#pragma once
#include "exprs/unary/LgsUnaryExpr.h"

class LgsNull final : public LgsUnaryExpr {
public:
    explicit LgsNull() : LgsUnaryExpr(nullptr) {
        isNull = true;
    }
    Value* createIRValue(LgsRuntime* runtime) override;
};

inline Value* LgsNull::createIRValue(LgsRuntime* runtime) {
    return ConstantPointerNull::get(runtime->builder.getPtrTy());
}


