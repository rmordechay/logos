#ifndef LOGOSUNARYEXPR_H
#define LOGOSUNARYEXPR_H
#include "LogosExpr.h"

#include <string>
#include <types/LogosType.h>

class LogosUnaryExpr: public LogosExpr {
public:
    explicit LogosUnaryExpr() : LogosExpr(nullptr) {}
    explicit LogosUnaryExpr(LogosType* type) : LogosExpr(type) {}
    virtual void setName(string name) = 0;
    virtual string getName() = 0;
    LogosSymbolType getSymbolType() override = 0;
    ~LogosUnaryExpr() override = default;
};

#endif //LOGOSUNARYEXPR_H
