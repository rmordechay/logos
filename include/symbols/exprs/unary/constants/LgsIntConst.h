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
        if (type->asBool()) {
            numberType = LgsNumberType::I1;
        } else if (type->asChar()) {
            numberType = LgsNumberType::I8;
        } else if (type->asShort()) {
            numberType = LgsNumberType::I16;
        } else if (type->asInt()) {
            numberType = LgsNumberType::I32;
        } else if (type->asInt()) {
            numberType = LgsNumberType::I64;
        } else {
            assert(0);
        }
    }
    void createIRValue(LgsCodeGen* codeGen) override;
    json::object asJSON() override;
    std::string pname() override;
};
