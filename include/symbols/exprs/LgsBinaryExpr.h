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
    Value* createIRValue(CodegenMetadata* metadata) override;
    Value* addIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* mulIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* subIR(CodegenMetadata* metadata, LgsExpr* other) override;
    Value* divIR(CodegenMetadata* metadata, LgsExpr* other) override;
    ~LgsBinaryExpr() override = default;
};

#endif //LOGOSBINARYEXPR_H
