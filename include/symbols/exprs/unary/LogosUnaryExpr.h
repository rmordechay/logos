#ifndef LOGOSUNARYEXPR_H
#define LOGOSUNARYEXPR_H
#include "LogosExpr.h"

#include <string>
#include <LogosType.h>

class LogosUnaryExpr: public LogosExpr {
public:
    explicit LogosUnaryExpr() : LogosExpr(nullptr) {}
    explicit LogosUnaryExpr(LogosType* type) : LogosExpr(type) {}
    virtual string getName();
    ~LogosUnaryExpr() override = default;
};

inline string LogosUnaryExpr::getName() { return ""; }

#endif //LOGOSUNARYEXPR_H
