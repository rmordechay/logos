#ifndef LGSVEC2_H
#define LGSVEC2_H
#include "exprs/unary/LgsUnaryExpr.h"

class LgsVec2 final : public LgsUnaryExpr {
public:
    LgsExpr* x;
    LgsExpr* y;

    LgsVec2(LgsExpr* x, LgsExpr* y) : LgsUnaryExpr(type), x(x), y(y) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsVec2() override = default;
};

#endif //LGSVEC2_H
