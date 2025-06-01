#ifndef LGSVEC3_H
#define LGSVEC3_H
#include "exprs/unary/LgsUnaryExpr.h"

class LgsVec3 final : public LgsUnaryExpr {
public:
    LgsExpr* x;
    LgsExpr* y;
    LgsExpr* z;

    Value* createIRValue(Module* module) override;
    ~LgsVec3() override = default;
};

#endif //LGSVEC3_H
