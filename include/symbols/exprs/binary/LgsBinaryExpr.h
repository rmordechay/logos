#ifndef LOGOSBINARYEXPR_H
#define LOGOSBINARYEXPR_H
#include "LgsExpr.h"
#include "LgsOperator.h"

#include <LogosMetadata.h>
#include <LgsType.h>

class LgsBinaryExpr final : public LgsExpr {
public:
    LgsExpr* left;
    LgsExpr* right;
    LgsOperator op;

    explicit LgsBinaryExpr(LgsType* type, LgsExpr* left, LgsExpr* right, const LgsOperator op) :
        LgsExpr(type),
        left(left),
        right(right),
        op(op) {
    }

    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* operator+(LgsExpr* other) override;
    ~LgsBinaryExpr() override = default;
};

#endif //LOGOSBINARYEXPR_H
