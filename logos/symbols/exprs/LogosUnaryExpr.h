#ifndef LOGOSUNARYEXPR_H
#define LOGOSUNARYEXPR_H
#include "LogosExpr.h"
#include "LogosType.h"

class LogosUnaryExpr : public LogosExpr {
public:
    virtual std::shared_ptr<LogosType> value() const = 0;
};

#endif //LOGOSUNARYEXPR_H
