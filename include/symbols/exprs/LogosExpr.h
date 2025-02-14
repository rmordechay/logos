#ifndef LOGOSEXPR_H
#define LOGOSEXPR_H
#include "CodeGeneration.h"
#include "types/LogosType.h"


class LogosExpr: virtual public CodeGeneration {
public:
    LogosType* type = nullptr;

    explicit LogosExpr(LogosType* type) : type(type) {}
    ~LogosExpr() override = default;
};


#endif //LOGOSEXPR_H

