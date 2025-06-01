#ifndef LGSVEC4_H
#define LGSVEC4_H
#include "exprs/unary/LgsUnaryExpr.h"

class LgsVec4 final : public LgsUnaryExpr {
public:
    LgsExpr* x;
    LgsExpr* y;
    LgsExpr* z;
    LgsExpr* w;

    Value* createIRValue(CodegenMetadata* metadata) override;
    ~LgsVec4() override = default;
};

#endif //LGSVEC4_H
