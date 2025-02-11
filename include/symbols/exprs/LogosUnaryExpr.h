#ifndef LOGOSUNARYEXPR_H
#define LOGOSUNARYEXPR_H
#include "LogosExpr.h"


class LogosUnaryExpr: public LogosExpr {
public:
    explicit LogosUnaryExpr() : LogosExpr(nullptr) {}
    explicit LogosUnaryExpr(LogosType* type) : LogosExpr(type) {}
    ~LogosUnaryExpr() override = default;
    string getName();
};

#endif //LOGOSUNARYEXPR_H
