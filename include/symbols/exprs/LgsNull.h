#pragma once
#include "exprs/unary/LgsUnaryExpr.h"

class LgsNull final : public LgsUnaryExpr {
public:
    explicit LgsNull() : LgsUnaryExpr(nullptr) {
        isNull = true;
    }

    void createIRValue(LgsCodeGen* codeGen) override;
    std::string pname() override;
    ~LgsNull() override = default;
};

inline void LgsNull::createIRValue(LgsCodeGen* codeGen) {
    IRValue = ConstantPointerNull::get(codeGen->ptrTy());
}

inline std::string LgsNull::pname() {
    return "null";
}