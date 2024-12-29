#ifndef LOGOSCONSTANTEXPR_H
#define LOGOSCONSTANTEXPR_H
#include "LogosType.h"
#include "LogosUnaryExpr.h"

class LogosConstantExpr final : public LogosUnaryExpr {
public:
    const std::shared_ptr<LogosType> logosType;
    explicit LogosConstantExpr(const std::shared_ptr<LogosType>& logosType): LogosUnaryExpr(), logosType(logosType) {}
    std::shared_ptr<LogosType> value() const override {return logosType; }
};

#endif //LOGOSCONSTANTEXPR_H
