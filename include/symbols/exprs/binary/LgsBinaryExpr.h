#ifndef LOGOSBINARYEXPR_H
#define LOGOSBINARYEXPR_H
#include "LogosExpr.h"
#include "LgsOperator.h"

#include <LogosMetadata.h>
#include <LgsType.h>

class LgsBinaryExpr final : public LogosExpr {
public:
    LogosExpr* left;
    LogosExpr* right;
    LgsOperator op;

    explicit LgsBinaryExpr(LgsType* type, LogosExpr* left, LogosExpr* right, const LgsOperator op) :
        LogosExpr(type),
        left(left),
        right(right),
        op(op) {
    }

    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsBinaryExpr() override = default;
};

#endif //LOGOSBINARYEXPR_H
