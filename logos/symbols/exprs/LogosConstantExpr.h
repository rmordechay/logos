#ifndef LOGOSCONSTANTEXPR_H
#define LOGOSCONSTANTEXPR_H
#include "LogosValue.h"
#include "LogosUnaryExpr.h"

class LogosConstantExpr final : public LogosUnaryExpr {
public:
    explicit LogosConstantExpr(LogosValue* logosType): LogosUnaryExpr(logosType) {}
};

#endif //LOGOSCONSTANTEXPR_H
