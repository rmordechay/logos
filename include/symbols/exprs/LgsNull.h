#pragma once
#include "exprs/unary/LgsUnaryExpr.h"

class LgsNull final : public LgsUnaryExpr {
public:
    explicit LgsNull() : LgsUnaryExpr(nullptr) {
        isNull = true;
    }

    json::value_ref asJSON() override;
    void createIRValue(LgsCodeGen* codeGen) override;
    std::string pname() override;
};

inline json::value_ref LgsNull::asJSON() {
    return json::value(nullptr);
}

inline void LgsNull::createIRValue(LgsCodeGen* codeGen) {
    IRValue = ConstantPointerNull::get(codeGen->ptrTy());
}

inline std::string LgsNull::pname() {
    return "null";
}
