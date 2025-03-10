#ifndef LOGOSTYPECONST_H
#define LOGOSTYPECONST_H
#include <unary/LogosUnaryExpr.h>

class LogosTypeConst final : public LogosUnaryExpr {
public:
    explicit LogosTypeConst(LogosType* type) : LogosUnaryExpr(type) {}
    inline string getName() override;
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    ~LogosTypeConst() override = default;
};

#endif //LOGOSTYPECONST_H
