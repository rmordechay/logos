#pragma once
#include "exprs/unary/LgsUnaryExpr.h"

class LgsNull final : public LgsUnaryExpr {
public:
    explicit LgsNull() : LgsUnaryExpr(nullptr) {
        isNull = true;
    }

    json::object asJSON() override;
    void createIRValue(LgsCodeGen* codeGen) override;
    std::string pname() override;
    ~LgsNull() override = default;
};

inline json::object LgsNull::asJSON() {
    json::object obj;
    return obj;
}

inline void LgsNull::createIRValue(LgsCodeGen* codeGen) {
    IRValue = ConstantPointerNull::get(codeGen->ptrTy());
}

inline std::string LgsNull::pname() {
    return "null";
}
