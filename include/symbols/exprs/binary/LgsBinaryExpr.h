#ifndef LOGOSBINARYEXPR_H
#define LOGOSBINARYEXPR_H
#include "exprs/LgsExpr.h"
#include "LgsOperator.h"
#include <types/LgsType.h>

class LgsBinaryExpr final : public LgsExpr {
public:
    LgsExpr* left;
    LgsExpr* right;
    LgsOperator op;

    explicit LgsBinaryExpr(LgsType* type, LgsExpr* left, LgsExpr* right, const LgsOperator op) : LgsExpr(type), left(left), right(right), op(op) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* addIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* mulIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* subIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    Value* divIR(CodeGenMetadata* metadata, LgsExpr* other) override;
    ~LgsBinaryExpr() override = default;
};

#endif //LOGOSBINARYEXPR_H
