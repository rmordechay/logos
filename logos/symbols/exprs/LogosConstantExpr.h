#ifndef LOGOSCONSTANTEXPR_H
#define LOGOSCONSTANTEXPR_H
#include "LogosType.h"
#include "LogosUnaryExpr.h"

class LogosConstantExpr final : public LogosUnaryExpr {
public:
    explicit LogosConstantExpr(const LogosType* logosType): LogosUnaryExpr(logosType) {}
};

#endif //LOGOSCONSTANTEXPR_H
