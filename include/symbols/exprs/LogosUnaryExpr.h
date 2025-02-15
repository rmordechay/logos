#ifndef LOGOSUNARYEXPR_H
#define LOGOSUNARYEXPR_H
#include "LogosExpr.h"

#include <string>


class LogosUnaryExpr: public LogosExpr {
public:
    explicit LogosUnaryExpr() : LogosExpr(nullptr) {}
    explicit LogosUnaryExpr(LogosType* type) : LogosExpr(type) {}
    string getName();
    ~LogosUnaryExpr() override = default;
};

#endif //LOGOSUNARYEXPR_H
