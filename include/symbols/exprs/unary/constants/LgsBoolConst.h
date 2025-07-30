#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/primitives/LgsBool.h"

class LgsBoolConst final : public LgsUnaryExpr {
public:
    bool value;

    explicit LgsBoolConst(const bool value) : LgsUnaryExpr(&LGS_BOOL), value(value) {}
    string getValueAsString() const;
    string prettyName() override;
    Value* createIRValue(LgsCodeGen* codeGen) override;
    Value* andIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* eqIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* neIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* ltIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* gtIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* geIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* leIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* orIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* bitAndIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* bitOrIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* bitXorIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* rshiftIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* lshiftIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    ~LgsBoolConst() override = default;
};
