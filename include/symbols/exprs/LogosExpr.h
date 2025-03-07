#ifndef LOGOSEXPR_H
#define LOGOSEXPR_H
#include "LogosValue.h"
#include <LogosType.h>

class LogosFuncCall;
class LogosVariable;
class LogosConstant;
class LogosInstance;

class LogosExpr: virtual public LogosValue {
public:
    LogosType* type = nullptr;

    explicit LogosExpr(LogosType* type) : type(type) {}

    ~LogosExpr() override = default;
};

#endif //LOGOSEXPR_H

