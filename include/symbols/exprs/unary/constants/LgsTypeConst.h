#ifndef LOGOSTYPECONST_H
#define LOGOSTYPECONST_H
#include "LgsConst.h"

#include <unary/LogosUnaryExpr.h>

class LgsTypeConst final : public LgsConst {
public:
    explicit LgsTypeConst(LgsType* type) : LgsConst(type) {}
    inline string getName() override;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsTypeConst() override = default;
};

#endif //LOGOSTYPECONST_H
