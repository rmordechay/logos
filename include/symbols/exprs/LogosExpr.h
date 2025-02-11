#ifndef LOGOSEXPR_H
#define LOGOSEXPR_H
#include "CodeGeneration.h"

class LogosType;

class LogosExpr: public CodeGeneration {
public:
    LogosType* type = nullptr;

    explicit LogosExpr(LogosType* type) : type(type) {}
    ~LogosExpr() override = default;

};

#endif //LOGOSEXPR_H

