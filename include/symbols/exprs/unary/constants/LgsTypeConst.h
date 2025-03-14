#ifndef LOGOSTYPECONST_H
#define LOGOSTYPECONST_H
#include "LgsConstant.h"

#include <unary/LogosUnaryExpr.h>

class LgsTypeConst final : public LgsConstant {
public:
    explicit LgsTypeConst(LgsType* type) : LgsConstant(type) {}
    inline string getName() override;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsTypeConst() override = default;
};

#endif //LOGOSTYPECONST_H
