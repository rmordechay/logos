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
        setNumberType();
    }
    void setNumberType();
    bool castTo(LgsType* toType) override;
    void createIRValue(LgsCodeGen* codeGen) override;
    std::string pname() override;
    json::value_ref asJSON() override;
};
