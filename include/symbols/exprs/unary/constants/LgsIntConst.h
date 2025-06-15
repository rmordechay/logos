#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/primitives/LgsInt.h"

class LgsConstNumber : public LgsUnaryExpr {
public:
    explicit LgsConstNumber(LgsType* type) : LgsUnaryExpr(type) {}
};


class LgsIntConst final : public LgsUnaryExpr {
public:
    int value;

    explicit LgsIntConst(const int value) : LgsUnaryExpr(&LGS_INT), value(value) {
        type->isStatic = true;
    }
    string pName() override;
    Value* createIRValue(LgsRuntime* runtime) override;
    LgsExpr* convertExpr(LgsType* toType) override;
    Value* eqIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* neIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* gtIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* ltIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* geIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* leIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* andIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* orIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* bitAndIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* bitOrIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* bitXorIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* rshiftIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* lshiftIR(LgsRuntime* runtime, LgsExpr* other) override;
    LgsExpr* clone() override;
    ~LgsIntConst() override = default;
};


