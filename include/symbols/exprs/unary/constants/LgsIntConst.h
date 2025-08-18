#pragma once
#include "exprs/unary/LgsUnaryExpr.h"

enum class LgsNumberType {
    I1,
    I8,
    I16,
    I32,
    I64,
};

class LgsIntConst final : public LgsUnaryExpr {
public:
    uint64_t value;
    LgsNumberType numberType;

    LgsIntConst(LgsType* type, const size_t value) : LgsUnaryExpr(type), value(value) {
        isConstant = true;
        setNumberType();
    }
    void setNumberType();
    void createIRValue(LgsCodeGen* codeGen) override;
    std::string pname() override;
    json::object asJSON() override;
};
