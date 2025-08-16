#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/primitives/LgsBool.h"

class LgsBoolConst final : public LgsUnaryExpr {
public:
    bool value;

    explicit LgsBoolConst(const bool value) : LgsUnaryExpr(&LGS_BOOL), value(value) {}
    std::string getValueAsString() const;
    std::string pname() override;
    void createIRValue(LgsCodeGen* codeGen) override;
    Value* andIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    Value* orIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    ~LgsBoolConst() override = default;
};
