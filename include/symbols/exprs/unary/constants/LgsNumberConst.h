#pragma once
#include "exprs/unary/LgsUnaryExpr.h"

enum class LgsNumberType {
    I1,
    I8,
    I16,
    I32,
    I64,
};

class LgsNumberConst final : public LgsUnaryExpr {
public:
    uint64_t value;
    LgsNumberType number;

    LgsNumberConst(LgsType* type, const size_t value) : LgsUnaryExpr(type), value(value) {
        isConstant = true;
        if (type->asBool()) {
            number = LgsNumberType::I1;
        } else if (type->asChar()) {
            number = LgsNumberType::I8;
        } else if (type->asShort()) {
            number = LgsNumberType::I16;
        } else if (type->asInt()) {
            number = LgsNumberType::I32;
        } else if (type->asLong()) {
            number = LgsNumberType::I64;
        } else {
            assert(0);
        }
    }
    void createIRValue(LgsCodeGen* codeGen) override;
    std::string pname() override;
};
