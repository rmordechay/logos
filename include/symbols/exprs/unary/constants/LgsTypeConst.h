#ifndef LOGOSTYPECONST_H
#define LOGOSTYPECONST_H
#include <unary/LogosUnaryExpr.h>

class LgsTypeConst final : public LgsUnaryExpr {
public:
    explicit LgsTypeConst(LgsType* type) : LgsUnaryExpr(type) {}
    inline string getName() override;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsTypeConst() override = default;
};

#endif //LOGOSTYPECONST_H
