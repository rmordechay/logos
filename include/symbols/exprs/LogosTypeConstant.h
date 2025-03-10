#ifndef LOGOSTYPECONSTANT_H
#define LOGOSTYPECONSTANT_H
#include "LogosUnaryExpr.h"

class LogosTypeConstant final : public LogosUnaryExpr {
public:
    explicit LogosTypeConstant(LogosType* type) : LogosUnaryExpr(type) {}
    string getName() override;
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    ~LogosTypeConstant() override = default;
};



#endif //LOGOSTYPECONSTANT_H
