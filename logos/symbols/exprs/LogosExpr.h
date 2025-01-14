#ifndef LOGOSEXPR_H
#define LOGOSEXPR_H
#include "types/LogosType.h"


class LogosExpr {
public:
    const LogosType& type;

    explicit LogosExpr(const LogosType& type) : type(type) {}
    virtual ~LogosExpr() {}
};

#endif //LOGOSEXPR_H
