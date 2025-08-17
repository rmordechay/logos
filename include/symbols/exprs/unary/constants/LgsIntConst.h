#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/primitives/LgsInt.h"

class LgsNumber final : public LgsUnaryExpr {
public:
    size_t value;

    void createIRValue(LgsCodeGen* codeGen) override;
    std::string pname() override;
};

class LgsIntConst final : public LgsUnaryExpr {
public:
    uint32_t value;

    explicit LgsIntConst(const int value) : LgsUnaryExpr(&LGS_INT), value(value) {
        isConstant = true;
    }
    std::string pname() override;
    void createIRValue(LgsCodeGen* codeGen) override;
    LgsExpr* castTo(LgsType* toType) override;
    LgsExpr* clone() override;
};
