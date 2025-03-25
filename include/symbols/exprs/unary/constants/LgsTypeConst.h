#ifndef LOGOSTYPECONST_H
#define LOGOSTYPECONST_H
#include "LgsConstExpr.h"

#include <exprs/unary/LgsUnaryExpr.h>

class LgsTypeConst final : public LgsConstExpr {
public:
    explicit LgsTypeConst(LgsType* type) : LgsConstExpr(type) {}
    inline string getName() override;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    json asJson() override;
    ~LgsTypeConst() override = default;
};

#endif //LOGOSTYPECONST_H
