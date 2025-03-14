#ifndef LOGOSEXPR_H
#define LOGOSEXPR_H
#include "LgsValue.h"
#include <LgsType.h>

class LogosFuncCall;
class LogosVariable;
class LgsConstant;
class LogosInstance;

class LogosExpr: virtual public LgsValue {
public:
    LgsType* type = nullptr;

    explicit LogosExpr(LgsType* type) : type(type) {}

    ~LogosExpr() override = default;
};

#endif //LOGOSEXPR_H

