#ifndef LOGOSUNARYEXPR_H
#define LOGOSUNARYEXPR_H
#include "LogosExpr.h"

#include <string>
#include <LgsType.h>

class LgsUnaryExpr: public LogosExpr {
public:
    explicit LgsUnaryExpr() : LogosExpr(nullptr) {}
    explicit LgsUnaryExpr(LgsType* type) : LogosExpr(type) {}
    virtual string getName();
    ~LgsUnaryExpr() override = default;
};

inline string LgsUnaryExpr::getName() { return ""; }

#endif //LOGOSUNARYEXPR_H
