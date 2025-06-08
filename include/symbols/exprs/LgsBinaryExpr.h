#ifndef LOGOSBINARYEXPR_H
#define LOGOSBINARYEXPR_H
#include "exprs/LgsExpr.h"
#include "exprs/LgsOperator.h"


class LgsBinaryExpr final : public LgsExpr {
public:
    LgsExpr* left;
    LgsExpr* right;
    LgsOperator op;

    explicit LgsBinaryExpr(LgsType* type, LgsExpr* left, LgsExpr* right, const LgsOperator op) : LgsExpr(type), left(left), right(right), op(op) {}
    Value* createIRValue(LgsRuntime* runtime) override;
    Value* addIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* mulIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* subIR(LgsRuntime* runtime, LgsExpr* other) override;
    Value* divIR(LgsRuntime* runtime, LgsExpr* other) override;
    ~LgsBinaryExpr() override = default;
};

#endif //LOGOSBINARYEXPR_H
