#ifndef LOGOSBINARYEXPR_H
#define LOGOSBINARYEXPR_H
#include "exprs/LgsExpr.h"
#include "exprs/LgsOperator.h"
#include <types/LgsType.h>

class LgsBinaryExpr final : public LgsExpr {
public:
    LgsExpr* left;
    LgsExpr* right;
    LgsOperator op;

    explicit LgsBinaryExpr(LgsType* type, LgsExpr* left, LgsExpr* right, const LgsOperator op) : LgsExpr(type), left(left), right(right), op(op) {}
    Value* createIRValue(Module* module) override;
    Value* addIR(Module* module, LgsExpr* other) override;
    Value* mulIR(Module* module, LgsExpr* other) override;
    Value* subIR(Module* module, LgsExpr* other) override;
    Value* divIR(Module* module, LgsExpr* other) override;
    ~LgsBinaryExpr() override = default;
};

#endif //LOGOSBINARYEXPR_H
