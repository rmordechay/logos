#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/primitives/LgsUInt.h"

class LgsUIntConst final : public LgsUnaryExpr {
public:
    int64_t value;

    explicit LgsUIntConst(const int value) : LgsUnaryExpr(&LGS_UINT), value(value) {}
    std::string pname() override;
    void createIRValue(LgsCodeGen* codeGen) override;
    json::object asJSON() override;
    bool castTo(LgsType* toType) override;
    Value* eqIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* neIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* gtIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* ltIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* geIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* leIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* andIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* orIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* bitAndIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* bitOrIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* bitXorIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* rshiftIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* lshiftIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    LgsExpr* clone() override;
    ~LgsUIntConst() override = default;
};


