#ifndef LOGOSUNARYEXPR_H
#define LOGOSUNARYEXPR_H
#include "LogosExpr.h"

#include <string>
#include <types/LogosType.h>

class LogosUnaryExpr: public LogosExpr {
public:
    explicit LogosUnaryExpr() : LogosExpr(nullptr) {}
    explicit LogosUnaryExpr(LogosType* type) : LogosExpr(type) {}
    virtual string getName() = 0;
    virtual ~LogosUnaryExpr() override = default;
    LogosSymbolType getSymbolType() override = 0;
};

#endif //LOGOSUNARYEXPR_H
