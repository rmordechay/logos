#pragma once
#include "exprs/unary/LgsUnaryExpr.h"

class LgsNull final : public LgsUnaryExpr {
public:
    explicit LgsNull() : LgsUnaryExpr(nullptr) {
        isNull = true;
    }
    Value* createIRValue(LgsCodeGen* codeGen) override;
    std::string prettyName() override;
    ~LgsNull() override = default;
};

inline Value* LgsNull::createIRValue(LgsCodeGen* codeGen) {
    return ConstantPointerNull::get(codeGen->ptrTy());
}

inline std::string LgsNull::prettyName() {
    return "null";
}