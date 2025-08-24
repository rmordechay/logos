#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/primitives/LgsUInt.h"

class LgsUIntConst final : public LgsUnaryExpr {
public:
    int64_t value;

    explicit LgsUIntConst(const int value) : LgsUnaryExpr(&LGS_UINT), value(value) {}
    std::string pname() override;
    json::value asJSON() override;
    Value* eqIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* neIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* gtIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* ltIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* geIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* leIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* andIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* orIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* bitAndIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* bitOrIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* bitXorIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* rshiftIR(LgsLLVM& codeGen, LgsExpr* other) override;
    Value* lshiftIR(LgsLLVM& codeGen, LgsExpr* other) override;
    ~LgsUIntConst() override = default;
};


