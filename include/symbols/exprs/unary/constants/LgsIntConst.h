#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/primitives/LgsInt.h"

class LgsIntConst final : public LgsUnaryExpr {
public:
    uint32_t value;

    explicit LgsIntConst(const int value) : LgsUnaryExpr(&LGS_INT), value(value) {
        isConstant = true;
    }
    std::string prettyName() override;
    void createIRValue(LgsCodeGen* codeGen) override;
    LgsExpr* castTo(LgsType* toType) override;
    Value* andIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* orIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* bitAndIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* bitOrIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* bitXorIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* rshiftIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* lshiftIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    LgsExpr* clone() override;
    ~LgsIntConst() override = default;
};


